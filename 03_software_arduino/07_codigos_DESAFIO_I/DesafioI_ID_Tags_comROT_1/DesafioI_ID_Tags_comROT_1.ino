
// ==========================================================================
// 🤖 AzorCAR – Desafio I – V6: Rotação Inicial + Deteção + Aproximação Suave
// 📷 HuskyLens – Tag Recognition
// 🚗 Protótipo 1 com parâmetros testados
// ==========================================================================

#include <SoftwareSerial.h>
#include "HUSKYLENS.h"
#include <Wire.h>

SoftwareSerial huskySerial(8, 9);
HUSKYLENS huskylens;

// === Pinos motores
const int E1 = 10;
const int M1 = 12;
const int E2 = 11;
const int M2 = 13;

// === Parâmetros da TAG1
const int ID1 = 1;
const int W_MIN = 75;
const int W_MAX = 120;
const int H_MIN = 75;
const int H_MAX = 116;
const int LIMIAR_X = 15;

// === Parâmetros de movimento
const int VEL_ROTACAO = 140;
const int TEMPO_ROTACAO = 150;
const int PAUSA_ROTACAO = 450;
const int PASSOS_INICIAIS = 18;

const int VEL_AVANCO = 140;
const int TEMPO_AVANCO = 150;
const int VEL_RECUO  = 130;
const int TEMPO_RECUO = 150;
const int VEL_CORRIGIR = 100;
const int TEMPO_CORRIGIR = 100;

// === Funções de movimento ===

void parar() {
  analogWrite(E1, 0); analogWrite(E2, 0);
  digitalWrite(M1, LOW); digitalWrite(M2, LOW);
}

void frente(int vel, int tempo) {
  digitalWrite(M1, 1); digitalWrite(M2, 1);
  analogWrite(E1, vel); analogWrite(E2, vel);
  delay(tempo);
  parar();
}

void tras(int vel, int tempo) {
  digitalWrite(M1, 0); digitalWrite(M2, 0);
  analogWrite(E1, vel); analogWrite(E2, vel);
  delay(tempo);
  parar();
}

void girar_direita(int vel, int tempo) {
  digitalWrite(M1, 0); digitalWrite(M2, 1);
  analogWrite(E1, vel); analogWrite(E2, vel);
  delay(tempo);
  parar();
}

void girar_esquerda(int vel, int tempo) {
  digitalWrite(M1, 1); digitalWrite(M2, 0);
  analogWrite(E1, vel); analogWrite(E2, vel);
  delay(tempo);
  parar();
}

// === Setup ===

void setup() {
  Serial.begin(9600);
  huskySerial.begin(9600);
  huskylens.begin(huskySerial);

  pinMode(E1, OUTPUT); pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT); pinMode(M2, OUTPUT);
  parar();

  Serial.println(F("🔁 ROTAÇÃO COMPLETA INICIAL (sem deteção)"));
  for (int i = 0; i < PASSOS_INICIAIS; i++) {
    girar_direita(VEL_ROTACAO, TEMPO_ROTACAO);
    delay(PAUSA_ROTACAO);
  }

  Serial.println(F("🔄 ROTAÇÃO CONTINUA COM DETEÇÃO ATIVA"));
  while (true) {
    girar_direita(VEL_ROTACAO, TEMPO_ROTACAO);
    delay(PAUSA_ROTACAO);

    if (!huskylens.request() || !huskylens.available()) {
      Serial.println("🔎 Sem deteção – continuar a girar");
      continue;
    }

    HUSKYLENSResult r = huskylens.read();
    if (r.ID == ID1) {
      Serial.println("🎯 TAG1 DETETADA – PARAR ROTAÇÃO");
      break;
    } else {
      Serial.print("ID detetado: ");
      Serial.print(r.ID);
      Serial.println(" – ignorado");
    }
  }
}

// === Loop principal – Aproximação ===

void loop() {
  if (!huskylens.request() || !huskylens.available()) {
    Serial.println("🔍 Sem TAG visível – PARAR");
    parar();
    delay(200);
    return;
  }

  HUSKYLENSResult r = huskylens.read();

  if (r.ID != ID1) {
    Serial.print("⚠️ Outro ID: ");
    Serial.println(r.ID);
    parar();
    delay(200);
    return;
  }

  int x = r.xCenter - 160;
  int w = r.width;
  int h = r.height;

  Serial.print("🎯 TAG1 – X: "); Serial.print(x);
  Serial.print(" | W: "); Serial.print(w);
  Serial.print(" | H: "); Serial.println(h);

  if (x < -LIMIAR_X) {
    Serial.println("↪️ Corrigir ESQUERDA");
    girar_esquerda(VEL_CORRIGIR, TEMPO_CORRIGIR);
  }
  else if (x > LIMIAR_X) {
    Serial.println("↩️ Corrigir DIREITA");
    girar_direita(VEL_CORRIGIR, TEMPO_CORRIGIR);
  }
  else {
    if (w < W_MIN || h < H_MIN) {
      Serial.println("⬆️ Aproximar (frente)");
      frente(VEL_AVANCO, TEMPO_AVANCO);
    }
    else if (w > W_MAX || h > H_MAX) {
      Serial.println("⬇️ Recuar (trás)");
      tras(VEL_RECUO, TEMPO_RECUO);
    }
    else {
      Serial.println("🟢 Zona ideal – PARAR");
      parar();
    }
  }

  delay(200);
}
