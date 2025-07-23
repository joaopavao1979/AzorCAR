#include <SoftwareSerial.h>
#include "HUSKYLENS.h"
#include <Wire.h>
#include <U8x8lib.h>  // OLED modo leve

// === Comunicação com HuskyLens via UART (pinos 8 RX, 9 TX) ===
SoftwareSerial huskySerial(8, 9);
HUSKYLENS huskylens;

// === OLED SH1106 com U8x8 (baixo consumo de memória) ===
U8X8_SH1106_128X64_NONAME_HW_I2C oled(U8X8_PIN_NONE);

// === Pinos do driver L298P ===
const int E1 = 10;  // PWM direita
const int M1 = 12;  // DIR direita
const int E2 = 11;  // PWM esquerda
const int M2 = 13;  // DIR esquerda

// === Parâmetros ===
int velocidade_base = 110;   // valor seguro para garantir movimento
int velocidade_lenta = 90;   // usada para curva (um dos lados)
int zona_centro_min = 110;   // limites das zonas
int zona_centro_max = 210;

void setup() {
  Serial.begin(9600);
  huskySerial.begin(9600);
  huskylens.begin(huskySerial);
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);  // modo "Line Tracking"

  oled.begin();
  oled.setFont(u8x8_font_chroma48medium8_r); // fonte pequena

  pinMode(E1, OUTPUT); pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT); pinMode(M2, OUTPUT);
}

void loop() {
  if (huskylens.request()) {
    HUSKYLENSResult result = huskylens.read();

    if (result.command == COMMAND_RETURN_ARROW) {
      int x = result.xTarget;

      if (x < zona_centro_min) {
        virarEsquerda();
        oled.drawString(0, 0, "Linha: Esquerda");
      } 
      else if (x > zona_centro_max) {
        virarDireita();
        oled.drawString(0, 0, "Linha: Direita");
      } 
      else {
        andarFrente(velocidade_base, velocidade_base);
        oled.drawString(0, 0, "Linha: Centro");
      }

    } else {
      parar();
      oled.drawString(0, 0, "Sem deteccao");
    }
  } else {
    parar();
    oled.drawString(0, 0, "Erro HuskyLens");
  }

  delay(30);  // curto para deteção fluida
}

// === Funções de movimento ===

void andarFrente(int vel_esq, int vel_dir) {
  digitalWrite(M1, LOW);  // direita frente
  digitalWrite(M2, LOW);  // esquerda frente
  analogWrite(E1, vel_dir);
  analogWrite(E2, vel_esq);
}

void virarEsquerda() {
  digitalWrite(M1, LOW);  // direita frente
  digitalWrite(M2, LOW);  // esquerda frente
  analogWrite(E1, velocidade_base);    // direita normal
  analogWrite(E2, velocidade_lenta);   // esquerda lenta
}

void virarDireita() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, velocidade_lenta);  // direita lenta
  analogWrite(E2, velocidade_base);   // esquerda normal
}

void parar() {
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}
