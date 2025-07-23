# 🤖 AzorCAR – Etapa 3 FINAL: Controlo Web + HuskyLens + Modo Offline

Este sketch permite controlar o estado do robô **AzorCAR** remotamente via Wi-Fi (quando disponível), e utilizar a **câmara HuskyLens** para reconhecimento de cores e tomada de decisões locais com **simulação visual por LEDs**. O sistema funciona mesmo **sem acesso à Internet**, tornando-o ideal para testes e apresentações em qualquer lugar.

---

## 📦 Funcionalidades principais

- Interface Web simples acessível por browser (quando Wi-Fi está disponível)
- Controlo do estado do sistema (`/start`, `/stop`, `/status`)
- Reconhecimento de **cores com HuskyLens** (modo Color Recognition)
- Acionamento de LEDs para simular comportamentos do robô
- Modo **offline automático** se não for possível ligar ao Wi-Fi

---

## 🧱 Requisitos

- Arduino UNO R4 WiFi (ESP32-S3)
- Câmara HuskyLens ligada via `SoftwareSerial` (pinos 8 e 9)
- LEDs conectados aos pinos:
  - `D2` → LED VERDE (sistema ON)
  - `D4` → LED VERMELHO (parar)
  - `D5` → LED AMARELO (motor ESQUERDO)
  - `D6` → LED AZUL (motor DIREITO)
- Resistor de 220Ω para cada LED
- Fonte externa para a HuskyLens (ex: powerbank via cabo USB)
- Biblioteca [HUSKYLENS by DFRobot](https://github.com/HuskyLens/HUSKYLENSArduino)

---

## 🔁 Funcionamento passo a passo

### 1. Inicialização

- Tenta ligar-se à rede Wi-Fi definida (`ssid`, `pass`) por até **10 segundos**
- Se conseguir, imprime o IP no Serial Monitor e ativa o servidor web
- Se falhar, entra em **modo offline** (a lógica de visão continua a funcionar)

### 2. Interface Web (caso ligada ao Wi-Fi)

- `/start` → ativa o modo de visão
- `/stop` → desativa o modo de visão
- `/status` → mostra o estado atual
- Cada comando pode ser enviado a partir dos botões no browser

### 3. Modo de visão com HuskyLens

Quando o modo estiver ativo:

- `ID: 1` → virar à esquerda → acende LED AMARELO
- `ID: 2` → virar à direita → acende LED AZUL
- `ID: 3` → parar → acende LED VERMELHO
- Estado normal → LED VERDE aceso (sistema ligado)

---

## 🧪 Testes sugeridos

- Testar o acesso à interface Web via browser no telemóvel (na mesma rede local)
- Verificar deteção de cores na HuskyLens com IDs atribuídos manualmente
- Simular cada ação movendo objetos coloridos à frente da câmara
- Utilizar o monitor serial para acompanhar mensagens e debug

---

## 📘 Notas técnicas

- A HuskyLens deve estar em modo **Color Recognition**
- A taxa de transmissão serial entre a HuskyLens e o Arduino deve ser **9600 baud**
- Recomenda-se definir as cores diretamente na HuskyLens e testar a sua consistência antes de ligar ao Arduino

---

## 📂 Estrutura sugerida

Este código deve ser colocado na pasta:

