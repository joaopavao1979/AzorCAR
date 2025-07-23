# 📁 03_software_arduino

## 📌 Descrição
Esta pasta contém todos os códigos-fonte (`.ino`) desenvolvidos para o **Arduino UNO R4 WiFi**, que controla os motores, interpreta sensores (como a **HuskyLens**) e permite comunicação sem fios via **Wi-Fi**.

Inicialmente planeado como projeto de exploração do **ROS 2**, o **AzorCAR** evoluiu a partir da experiência prática adquirida com o **HuskyCar**, reaproveitando testes com seguimento de cor, UART, e controlo proporcional. Esta nova abordagem visa resultados rápidos, robustos e funcionais com integração futura com ROS 2.

---

## 📂 Estrutura de subpastas

```txt
03_software_arduino/
├── 00_utils/                  # Funções auxiliares, debug, piscar LEDs
├── 01_wifi_tests/             # Testes de WebServer, modo AP, sockets
├── 02_huskylens_tests/        # Leitura via UART, reconhecimento de cor/objetos
├── 03_motor_tests/            # Testes com o driver L298P e simulações com LEDs
├── 04_integration_tests/      # Integração de Wi-Fi + HuskyLens + motores
├── 05_ros2_future/            # Experimentos iniciais para interface com ROS 2
└── README.md                  # Este ficheiro

📦 Exemplos de ficheiros
01_wifi_tests/wifi_webserver_basic.ino
Servidor HTTP simples para controlo remoto via browser.

02_huskylens_tests/huskylens_uart_read_id.ino
Leitura de ID de objeto ou cor via UART com a HuskyLens.

03_motor_tests/motor_control_led_simulation.ino
Simulação do controlo de motores com LEDs (sem hardware físico ligado).

04_integration_tests/full_control_simulation.ino
Código completo de teste: recebe comando por Wi-Fi, interpreta leitura da HuskyLens e acende LEDs simulando o comportamento dos motores.

💡 Notas Técnicas
A placa principal é o Arduino UNO R4 WiFi, com co-processador ESP32-S3.

A comunicação Wi-Fi usa a biblioteca WiFiS3.h, via WebServer HTTP ou sockets.

A HuskyLens é ligada por UART via SoftwareSerial nos pinos D8 (RX) e D9 (TX).

O controlo de motores será feito através do driver L298P, mas pode ser simulado com LEDs em testes iniciais.

Em breve será explorada a comunicação Arduino ↔ Raspberry Pi 5 via UART ou sockets como preparação para ROS 2.

🎯 Objetivo pedagógico
Construir uma base sólida de testes modulares com sensores e atuadores.

Experimentar comunicação sem fios e interfaces remotas simples.

Utilizar visão computacional embarcada com HuskyLens para decisões autónomas.

Facilitar a transição para projetos ROS 2 com experiência prática consolidada.

🧪 Dica prática: os testes são organizados por funcionalidade para facilitar a depuração e a evolução incremental. Usa primeiro LEDs para simulação e só depois liga os motores reais.