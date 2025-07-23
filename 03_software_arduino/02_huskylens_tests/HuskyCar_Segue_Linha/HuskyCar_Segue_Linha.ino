// ===============================================================
// 🔵 PROJETO: AzorCAR – Seguidor de Linha Inteligente
// 🤖 Desafio Azoresbot – Versão com HuskyLens + OLED SH1106
// 🧠 Controlo proporcional (P) com feedback visual no ecrã OLED
// 📡 Comunicação UART com a HuskyLens (SoftwareSerial)
// 📺 Visualização de estado e diagnóstico no display OLED I2C
// ===============================================================

#include <SoftwareSerial.h>
#include "HUSKYLENS.h"
#include <Wire.h>
#include <U8x8lib.h>  // Modo leve (sem framebuffer)

// === Comunicação com HuskyLens via UART (pinos 8 RX, 9 TX) ===
// Pino 9 (TX Arduino) → RX da HuskyLens → fio azul
// Pino 8 (RX Arduino) → TX da HuskyLens → fio verde
SoftwareSerial huskySerial(8, 9);
HUSKYLENS huskylens;

// === OLED SH1106 com driver leve (U8x8) ===
U8X8_SH1106_128X64_NONAME_HW_I2C oled(U8X8_PIN_NONE);

// === Pinos do driver L298P ===
const int E1 = 10;  // PWM direita
const int M1 = 12;  // DIR direita
const int E2 = 11;  // PWM esquerda
const int M2 = 13;  // DIR esquerda

// === Parâmetros ===
int velocidade_base = 85;
float Kp = 0.2;
int erro = 0;

void setup() {
  Serial.begin(9600);
  huskySerial.begin(9600);
  huskylens.begin(huskySerial);
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);

  oled.begin();
  oled.setFont(u8x8_font_chroma48medium8_r); // Fonte pequena, legível

  pinMode(E1, OUTPUT); pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT); pinMode(M2, OUTPUT);
}

void loop() {
  if (huskylens.request()) {
    HUSKYLENSResult result = huskylens.read();

    if (result.command == COMMAND_RETURN_ARROW) {
      erro = result.xTarget - 160;
      int correcao = Kp * erro;

      int vel_esq = constrain(velocidade_base + correcao, 0, 255);
      int vel_dir = constrain(velocidade_base - correcao, 0, 255);

      andarFrente(vel_esq, vel_dir);
      oled.drawString(0, 0, "Segue linha");

    } else {
      parar();
      oled.drawString(0, 0, "Sem deteccao");
    }
  } else {
    parar();
    oled.drawString(0, 0, "Erro HuskyLens");
  }

  delay(50);
}

void andarFrente(int vel_esq, int vel_dir) {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, vel_dir);
  analogWrite(E2, vel_esq);
}

void parar() {
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}
