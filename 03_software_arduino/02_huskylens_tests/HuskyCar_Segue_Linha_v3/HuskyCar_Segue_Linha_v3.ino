// ===============================================================
// 🔵 PROJETO: AzorCAR – Seguidor de Linha Inteligente
// 🤖 Desafio Azoresbot – Versão com HuskyLens + OLED SH1106
// 🧠 Controlo proporcional (P) com feedback visual no ecrã OLED
// 📡 Comunicação UART com a HuskyLens (SoftwareSerial)
// 📺 Visualização de estado e diagnóstico no display OLED I2C
// ===============================================================
// ===============================================================
// 🔵 PROJETO: AzorCAR – Seguidor de Linha Inteligente com PID
// 🤖 HuskyLens + OLED SH1106 | Controlo PID + Diagnóstico Visual
// ===============================================================

#include <SoftwareSerial.h>
#include "HUSKYLENS.h"
#include <Wire.h>
#include <U8x8lib.h>

// === Comunicação com HuskyLens via UART ===
// Pino 9 (TX Arduino) → RX da HuskyLens → fio azul
// Pino 8 (RX Arduino) → TX da HuskyLens → fio verde
SoftwareSerial huskySerial(8, 9);
HUSKYLENS huskylens;

// === OLED SH1106 ===
U8X8_SH1106_128X64_NONAME_HW_I2C oled(U8X8_PIN_NONE);

// === Pinos do driver L298P ===
const int E1 = 10;  // PWM direita
const int M1 = 12;  // DIR direita
const int E2 = 11;  // PWM esquerda
const int M2 = 13;  // DIR esquerda

// === Parâmetros PID ===
float Kp = 0.2;
float Ki = 0.05;
float Kd = 0.25;

int velocidade_base = 90;  // ajustável conforme os motores

int erro = 0;
int erro_anterior = 0;
float erro_integral = 0;

unsigned long tempo_anterior = 0;

void setup() {
  Serial.begin(9600);
  huskySerial.begin(9600);
  huskylens.begin(huskySerial);
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);

  oled.begin();
  oled.setFont(u8x8_font_chroma48medium8_r);
  
  pinMode(E1, OUTPUT); pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT); pinMode(M2, OUTPUT);
}

void loop() {
  if (huskylens.request()) {
    HUSKYLENSResult result = huskylens.read();

    if (result.command == COMMAND_RETURN_ARROW) {
      erro = result.xTarget - 160;  // Centro da imagem (320x240)

      unsigned long tempo_atual = millis();
      float dt = (tempo_atual - tempo_anterior) / 1000.0;  // segundos
      tempo_anterior = tempo_atual;

      erro_integral += erro * dt;
      float erro_derivada = (erro - erro_anterior) / dt;
      erro_anterior = erro;

      float correcao = Kp * erro + Ki * erro_integral + Kd * erro_derivada;

      int vel_esq = constrain(velocidade_base + correcao, 0, 255);
      int vel_dir = constrain(velocidade_base - correcao, 0, 255);

      andarFrente(vel_esq, vel_dir);

      oled.clearLine(0);
      oled.drawString(0, 0, "PID Ativo");
      oled.setCursor(0, 1);
      oled.print("Erro:");
      oled.print(erro);
    } else {
      parar();
      oled.clearLine(0);
      oled.drawString(0, 0, "Sem linha");
    }
  } else {
    parar();
    oled.clearLine(0);
    oled.drawString(0, 0, "Erro HuskyLens");
  }

  delay(40);  // resposta mais suave que 50ms
}

void andarFrente(int vel_esq, int vel_dir) {
  digitalWrite(M1, LOW);  // Frente
  digitalWrite(M2, LOW);  // Frente
  analogWrite(E1, vel_dir);
  analogWrite(E2, vel_esq);
}

void parar() {
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}
