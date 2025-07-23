// ===============================================================
// 🔵 PROJETO: AzorCAR – Seguidor de Linha Inteligente
// 🤖 Desafio Azoresbot – Versão com HuskyLens + OLED SH1106
// 🧠 Controle proporcional com avanço/pausa para estabilidade
// 📡 Comunicação UART com a HuskyLens (SoftwareSerial)
// 📺 Visualização de estado e diagnóstico no display OLED I2C
// ===============================================================

#include <SoftwareSerial.h>
#include "HUSKYLENS.h"
#include <Wire.h>
#include <U8x8lib.h>

// === Comunicação com HuskyLens via UART ===
SoftwareSerial huskySerial(8, 9); 
// RX: 8, TX: 9
// Pino 9 (TX Arduino) → RX da HuskyLens → fio azul
// Pino 8 (RX Arduino) → TX da HuskyLens → fio verde
HUSKYLENS huskylens;

// === OLED SH1106 ===
U8X8_SH1106_128X64_NONAME_HW_I2C oled(U8X8_PIN_NONE);

// === Pinos do driver L298P ===
const int E1 = 10;  // PWM direita
const int M1 = 12;  // DIR direita
const int E2 = 11;  // PWM esquerda
const int M2 = 13;  // DIR esquerda

// === Parâmetros de controle ===
const float Kp = 0.5;              // Ganho proporcional (ajustar conforme necessário)
const int velocidade_base = 120;    // Velocidade base dos motores (0-255)
const int advanceTime = 200;       // Tempo de avanço (ms)
const int stopTime = 150;          // Tempo de parada (ms)
const int centerLine = 160;        // Centro da imagem da HuskyLens (320x240)
const int tolerance = 20;          // Tolerância para considerar a linha centrada


void setup() {
  Serial.begin(9600);
  huskySerial.begin(9600);
  huskylens.begin(huskySerial);
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);

  oled.begin();
  oled.setFont(u8x8_font_chroma48medium8_r);
  oled.drawString(0, 0, "AzorCAR Iniciado");

  pinMode(E1, OUTPUT); pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT); pinMode(M2, OUTPUT);

  // Para os motores inicialmente
  parar();
}

void loop() {
  // Lê dados da HuskyLens
  if (!huskylens.request()) {
    oled.clear();
    oled.drawString(0, 0, "Erro HuskyLens");
    parar();
    delay(stopTime);
    return;
  }

  HUSKYLENSResult result = huskylens.read();
  if (result.command == COMMAND_RETURN_ARROW) {
    int erro = result.xTarget - centerLine; // Erro: desvio do centro

    // Controle proporcional
    float correcao = Kp * erro;
    int vel_esq = constrain(velocidade_base + correcao, 0, 255);
    int vel_dir = constrain(velocidade_base - correcao, 0, 255);

    // Atualiza o display OLED
    oled.clear();
    oled.drawString(0, 0, "Linha OK");
    oled.setCursor(0, 1);
    oled.print("Erro: ");
    oled.print(erro);
    oled.setCursor(0, 2);
    oled.print("Esq:");
    oled.print(vel_esq);
    oled.print(" Dir:");
    oled.print(vel_dir);

    // Avança apenas se a linha estiver dentro da tolerância
    if (abs(erro) < tolerance) {
      andarFrente(velocidade_base, velocidade_base); // Segue reto
      oled.drawString(0, 3, "Reto");
    } else {
      andarFrente(vel_esq, vel_dir); // Corrige direção
      oled.drawString(0, 3, "Corrige");
    }

    // Avança por advanceTime ms
    delay(advanceTime);

    // Para para estabilizar e ler novamente
    parar();
    oled.clearLine(3);
    oled.drawString(0, 3, "Parado");
    delay(stopTime);
  } else {
    oled.clear();
    oled.drawString(0, 0, "Sem Linha");
    parar();
    delay(stopTime);
  }
}

void andarFrente(int vel_esq, int vel_dir) {
  digitalWrite(M1, LOW);  // Frente direita
  digitalWrite(M2, LOW);  // Frente esquerda
  analogWrite(E1, vel_dir);
  analogWrite(E2, vel_esq);
}

void parar() {
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}