#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "MPU6050.h"

// =========================
//  OBJETOS/SENSORES
// =========================
MPU6050 mpu;
WiFiClient espClient;
PubSubClient client(espClient);

// =========================
//  PINOS
// =========================
const int BUZZER_PIN = 13;

// =========================
//  WI-FI (Wokwi)
// =========================
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// =========================
//  MQTT HiveMQ
// =========================
const char* mqtt_server = "broker.hivemq.com";
const char* topic_queda = "beatriz/queda";

// Controle
bool sistemaPronto = false;
unsigned long lastMsg = 0;

// ===================================================
//  WiFi
// ===================================================
void setup_wifi() {
  Serial.println("\n=== CONFIG WiFi ===");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(800);

  WiFi.begin(ssid, password);
  Serial.println("Conectando...");

  int tent = 0;
  while (WiFi.status() != WL_CONNECTED && tent < 25) {
    delay(400);
    Serial.print(".");
    tent++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi OK!");
    sistemaPronto = true;
  } else {
    Serial.println("\nFalha no WiFi");
    sistemaPronto = false;
  }
}

// ===================================================
//  CALLBACK MQTT
//  Mede tempo entre envio e recebimento do comando
// ===================================================
void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("\n📨 Mensagem recebida [");
  Serial.print(topic);
  Serial.print("]: ");

  String msg = "";
  for (int i = 0; i < length; i++) msg += (char)payload[i];
  Serial.println(msg);

  unsigned long now = millis();

  // Se a mensagem tiver timestamp (ex: CMD|T=1234567)
  if (msg.indexOf("T=") >= 0) {
    int pos = msg.indexOf("T=") + 2;
    unsigned long t_envio = msg.substring(pos).toInt();
    unsigned long atraso = now - t_envio;

    Serial.printf("⏱ Tempo entre envio e recebimento (CMD): %lu ms\n", atraso);
  }
}

// ===================================================
//  Reconectar MQTT
// ===================================================
void reconnectMQTT() {
  if (!sistemaPronto) return;

  Serial.print("Conectando ao MQTT...");
  if (client.connect("ESP32-Queda")) {
    Serial.println("OK!");
    client.subscribe(topic_queda);
  } else {
    Serial.println("FALHA");
  }
}

// ===================================================
//  SETUP
// ===================================================
void setup() {
  Serial.begin(115200);
  delay(1500);

  pinMode(BUZZER_PIN, OUTPUT);

  Wire.begin();
  mpu.initialize();
  delay(500);

  if (!mpu.testConnection()) {
    Serial.println("Erro ao conectar ao MPU6050!");
  } else {
    Serial.println("MPU6050 OK!");
  }

  setup_wifi();

  if (sistemaPronto) {
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    reconnectMQTT();
  }

  Serial.println("Sistema iniciado.\n");
}

// ===================================================
//  Função de detecção de queda
// ===================================================
bool detectarQueda(float ax, float ay, float az) {
  float A = sqrt(ax * ax + ay * ay + az * az);
  return (A < 0.4 || A > 2.5);
}

// ===================================================
//  LOOP PRINCIPAL
// ===================================================
void loop() {
  if (sistemaPronto && !client.connected()) reconnectMQTT();
  if (sistemaPronto) client.loop();

  if (millis() - lastMsg > 300) {
    lastMsg = millis();

    // Marca início do ciclo
    unsigned long t_sensor_inicio = millis();

    int16_t ax_raw, ay_raw, az_raw;
    mpu.getAcceleration(&ax_raw, &ay_raw, &az_raw);

    float ax = ax_raw / 16384.0;
    float ay = ay_raw / 16384.0;
    float az = az_raw / 16384.0;

    bool queda = detectarQueda(ax, ay, az);

    // Marca fim da leitura e do processamento
    unsigned long t_sensor_fim = millis();
    unsigned long tempo_sensor = t_sensor_fim - t_sensor_inicio;

    Serial.printf("⏱ Tempo leitura + processamento do sensor: %lu ms\n", tempo_sensor);

    if (queda) {
      Serial.println("\n🚨 QUEDA DETECTADA!");

      // Marca momento da detecção
      unsigned long t_detect = millis();

      digitalWrite(BUZZER_PIN, HIGH);
      delay(400);
      digitalWrite(BUZZER_PIN, LOW);

      // Marca momento que o atuador terminou
      unsigned long t_atuador = millis();
      unsigned long tempo_atuador = t_atuador - t_detect;

      Serial.printf("⏱ Tempo entre detecção e buzzer: %lu ms\n", tempo_atuador);

      if (client.connected()) {
        client.publish(topic_queda, "QUEDA DETECTADA");
      }
    }
    else {
      if (client.connected()) client.publish(topic_queda, "0");
    }
  }
}
