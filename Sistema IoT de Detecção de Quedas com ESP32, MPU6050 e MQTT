📝 Descrição Geral do Projeto

Este projeto implementa um sistema IoT de detecção de quedas para idosos, utilizando um ESP32, o sensor MPU6050 (acelerômetro + giroscópio), um buzzer piezoelétrico e comunicação MQTT.
O sistema identifica padrões de movimento característicos de queda e aciona imediatamente:

Um alerta sonoro local, através do buzzer.

Um alerta remoto, enviado para um broker MQTT.

Todo o desenvolvimento foi realizado em simulação utilizando o Wokwi, permitindo que qualquer usuário reproduza o protótipo sem necessidade de hardware físico.

▶ Como Reproduzir o Projeto

Acesse o simulador Wokwi (https://wokwi.com
).

Abra um novo projeto e selecione ESP32.

Adicione:

Sensor MPU6050

Buzzer

Copie e cole o código presente neste repositório.

Configure o tópico MQTT no HiveMQ Websocket Client ou MQTT Explorer.

Execute a simulação e monitore:

O console serial do Wokwi

Os tópicos MQTT para visualizar mensagens de alerta

O sistema enviará mensagens como:

"QUEDA DETECTADA"

"0" (sem queda)

🧠 Funcionamento do Sistema

O protótipo realiza continuamente:

Leitura dos valores brutos de aceleração do MPU6050

Cálculo da magnitude total do vetor aceleração

Verificação de limites críticos (forte impacto ou ausência brusca de movimento)

Acionamento imediato do buzzer em caso de queda

Envio do alerta ao broker MQTT

Registro dos tempos de processamento (sensor, buzzer, MQTT)

Fluxograma simplificado:

flowchart TD
A[Início] --> B[Ler aceleração do MPU6050]
B --> C{Queda detectada?}
C -- Não --> B
C -- Sim --> D[Acionar buzzer]
D --> E[Enviar alerta via MQTT]
E --> B

💻 Software Desenvolvido

O sistema foi desenvolvido em C/C++ utilizando a IDE Arduino, com as bibliotecas:

Wire.h – comunicação I2C

WiFi.h – conexão Wi-Fi (simulada no Wokwi)

PubSubClient.h – comunicação MQTT

MPU6050.h – leitura de sensores

🧾 Código-Fonte Completo

O código está na pasta /src deste repositório e contém:

Função de configuração do Wi-Fi

Função de reconexão MQTT

Rotina de callback MQTT

Função detectarQueda()

Laço principal com medição de tempos

Inclui também documentação comentada de cada trecho do código para facilitar a reprodução.

⚙ Descrição do Hardware Utilizado

Como o projeto foi desenvolvido inteiramente no Wokwi, o hardware é completamente simulado. O sistema físico equivalente conteria:

🔹 Placa de Desenvolvimento

ESP32 DevKit V1

Wi-Fi + Bluetooth integrado

240 MHz

Operação em 3.3V

Suporte a MQTT nativo via TCP/IP

🔹 Sensor de Movimento

MPU6050

Acelerômetro 3 eixos

Giroscópio 3 eixos

Comunicação I2C (pinos SDA / SCL)

🔹 Atuador

Buzzer piezoelétrico passivo

Operação em 3.3V

Ligado ao pino GPIO 13

🔹 Conectividade

Broker MQTT HiveMQ Cloud / broker.hivemq.com

Tópico utilizado: beatriz/queda

🔹 Caixa ou Suporte (Opcional)

Caso o projeto seja montado fisicamente, recomenda-se:

Impressão 3D de caixa com 70 × 50 × 30 mm

Abertura lateral para entrada USB

Respiro acústico para o buzzer

Espaço interno para fitas ou pulseiras de fixação

🌐 Documentação das Interfaces, Protocolos e Comunicação
📡 1. Comunicação I2C (MPU6050 ↔ ESP32)

Protocolo: I2C

Barramento: SDA, SCL

Endereço padrão: 0x68

Frequência: 400 kHz

Dados lidos:

ax_raw, ay_raw, az_raw

Conversão:

ax = ax_raw / 16384.0;

📶 2. Comunicação Wi-Fi

Rede: Wokwi-GUEST (sem senha)

Modo: WIFI_STA

Conexão automática no setup

📨 3. Protocolo MQTT

Broker: broker.hivemq.com

Porta: 1883

Tópico de publicação:

beatriz/queda

Mensagens enviadas:

QUEDA DETECTADA

0 (movimento normal)

🔄 4. Callback e Recepção de Mensagens

Exemplo de mensagem recebida via MQTT:

Mensagem recebida [beatriz/queda]: QUEDA DETECTADA


Esse retorno confirma:

Latência MQTT

Funcionamento do protocolo

Sincronização entre envio e recebimento

📊 Resultados Obtidos

O projeto apresentou os seguintes tempos médios:

Leitura + processamento do sensor: 1–2 ms

Tempo entre detecção e acionamento do buzzer: ~399 ms

Latência MQTT (envio → recebimento): baixa, < 20 ms em ambiente simulado

O sistema funcionou de forma estável, detectando quedas simuladas corretamente e publicando alertas em tempo real.

📚 Documentação Oficial — Hardware, Software e Protocolos
🟦 ESP32

Espressif — Documentação Oficial do ESP32
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/

Arduino Core para ESP32 (GitHub oficial)
https://github.com/espressif/arduino-esp32

Referência das funções WiFi do ESP32
https://arduino-esp32.readthedocs.io/en/latest/esp32_wifi/

🟫 MPU6050 (Acelerômetro/Giroscópio)

Datasheet do MPU6050 (Invensense)
https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf

Registro e Guia de Programação (Register Map)
https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf

Biblioteca recomendada da comunidade (Jeff Rowberg)
https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050

🟧 MQTT

Especificação oficial MQTT 3.1.1
https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html

HiveMQ — Guia MQTT para iniciantes (excelente)
https://www.hivemq.com/mqtt-essentials/

Broker público HiveMQ Websocket Client
https://www.hivemq.com/demos/websocket-client/

Documentação PubSubClient (biblioteca do Arduino)
https://pubsubclient.knolleary.net/

🟪 Wokwi (Simulador)

Wokwi — Documentação oficial
https://docs.wokwi.com/

Wokwi — Simulação do ESP32
https://docs.wokwi.com/parts/wokwi-esp32-devkit

Pinagem e diagramas do ESP32 no Wokwi
https://docs.wokwi.com/parts/wokwi-esp32-devkit#pin-configuration

🟨 Arduino / Linguagem C++

Referência oficial da linguagem Arduino (C++)
https://www.arduino.cc/reference/en/

Funções padrão do Arduino (digitalWrite, pinMode etc.)
https://www.arduino.cc/reference/en/language/functions/

Biblioteca Wire (I2C) — documentação oficial
https://www.arduino.cc/en/reference/wire

🟩 Internet das Coisas (IoT) — Guia geral

Microsoft Guide — IoT Fundamentals
https://learn.microsoft.com/en-us/azure/iot-fundamentals/

Google Cloud — IoT Concepts Basics
https://cloud.google.com/learn/what-is-iot  
