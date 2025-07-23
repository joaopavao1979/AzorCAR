# 📷 Descrição do Código – `huskylens_uart_read_id.ino`

Este código estabelece a comunicação UART entre o **Arduino UNO R4 WiFi** e a **câmara HuskyLens**, usando a biblioteca oficial `HUSKYLENS.h` e a classe `SoftwareSerial`.

O objetivo é **verificar a ligação física e a receção de dados UART**, imprimindo no **Serial Monitor** o **ID** do objeto/cor detetado, juntamente com as coordenadas do centro do objeto (X/Y).

---

## 🔁 Funcionamento passo-a-passo

### 🔹 1. Inicialização (`setup()`)

- Inicia o monitor serial (`Serial.begin(9600)`).
- Inicializa a porta UART secundária (`SoftwareSerial`) nos pinos `D8` (RX) e `D9` (TX).
- Associa a HuskyLens à porta criada.
- Verifica se a ligação com a HuskyLens foi bem-sucedida:
  - Se sim, imprime "HuskyLens ligada com sucesso".
  - Se não, imprime mensagem de erro no Serial.

---

### 🔹 2. Loop principal (`loop()`)

- A cada ciclo, o Arduino pede um novo frame à HuskyLens.
- Se houver deteção:
  - Lê todos os objetos detetados.
  - Imprime no Serial:
    - ID do objeto
    - Coordenadas X e Y do centro
- Se **nada for detetado**, imprime "⛔ Nada detetado."
- Se **falhar a comunicação**, imprime "⚠️ Falha na comunicação com a HuskyLens."

---

## 🔌 Ligações entre HuskyLens e Arduino UNO R4 WiFi

| HuskyLens | Arduino UNO R4 WiFi |
|-----------|---------------------|
| **TX**    | `D8` (RX do Arduino) |
| **RX**    | `D9` (TX do Arduino) |
| **GND**   | GND                  |
| **VCC**   | *Não ligado* (a câmara está alimentada por powerbank USB) |

⚠️ **Importante:** o GND da HuskyLens **deve estar ligado ao GND do Arduino**, mesmo com alimentação externa. Isso garante referência comum de sinal para comunicação UART.

---

## 📋 Modo da HuskyLens

Este teste funciona com qualquer modo que forneça **ID** e **posição**, incluindo:

- 🎨 Color Recognition
- 📦 Object Recognition
- 🔖 Tag Recognition

Certifica-te de que o modo está treinado e ativo antes de iniciar o teste.

---

## 📘 Resumo técnico

- Comunicação via `SoftwareSerial` (D8, D9)
- Biblioteca oficial `HUSKYLENS.h`
- Leitura de objetos com `huskylens.request()` + `huskylens.read()`
- Saída informativa no Serial Monitor
- Base para lógica condicional ou controlo autónomo com base em visão

---

> 💡 Este é o primeiro passo para usar a HuskyLens como sensor de entrada inteligente para o robô AzorCAR.
