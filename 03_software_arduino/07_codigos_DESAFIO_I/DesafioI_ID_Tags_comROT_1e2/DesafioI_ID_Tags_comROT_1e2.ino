
// ==========================================================================
// 🤖 AzorCAR – Desafio I : Pausa 10s após TAG1 + Procura de TAG2
// 📷 HuskyLens – Tag Recognition
// 🚗 Protótipo 1 com controlo de sequência ID1 → ID2
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

// === IDs das TAGs
const int ID1 = 1;
const int ID2 = 2;
int ID_ATUAL = ID1;  // começa por procurar ID1

// === Calibração por ID (usamos os mesmos valores para simplificar)
const int W_MIN = 75;
const int W_MAX = 120;
const int H_MIN = 75;
const int H_MAX = 116;
const int LIMIAR_X = 15;

// === Movimento
const int VEL_ROTACAO = 140;
const int TEMPO_ROTACAO = 200;
const int PAUSA_ROTACAO = 500;
const int PASSOS_INICIAIS = 18;

const int VEL_AVANCO = 140;
const int TEMPO_AVANCO = 150;
const int VEL_RECUO  = 130;
const int TEMPO_RECUO = 150;
const int VEL_CORRIGIR = 100;
const int TEMPO_CORRIGIR = 100;

// === Estados
bool rotacaoInicialFeita = false;
bool tag1Concluida = false;

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

  Serial.println("🔁 ROTAÇÃO INICIAL SEM DETEÇÃO");
  for (int i = 0; i < PASSOS_INICIAIS; i++) {
    girar_direita(VEL_ROTACAO, TEMPO_ROTACAO);
    delay(PAUSA_ROTACAO);
  }
  rotacaoInicialFeita = true;
}

// === LOOP PRINCIPAL ===

void loop() {
  // Etapa 1 ou 2: girar até encontrar o ID_ATUAL
  while (true) {
    girar_direita(VEL_ROTACAO, TEMPO_ROTACAO);
    delay(PAUSA_ROTACAO);

    if (!huskylens.request() || !huskylens.available()) {
      Serial.println("🔍 Sem deteção – continuar a girar");
      continue;
    }

    HUSKYLENSResult r = huskylens.read();
    if (r.ID == ID_ATUAL) {
      Serial.print("🎯 TAG com ID ");
      Serial.print(ID_ATUAL);
      Serial.println(" DETETADA – parar rotação");
      break;
    } else {
      Serial.print("ID detetado: ");
      Serial.print(r.ID);
      Serial.println(" – ignorado");
    }
  }

  // Aproximação ao ID_ATUAL
  while (true) {
    if (!huskylens.request() || !huskylens.available()) {
      Serial.println("🔍 TAG perdida – PARAR");
      parar();
      delay(200);
      continue;
    }

    HUSKYLENSResult r = huskylens.read();

    if (r.ID != ID_ATUAL) {
      Serial.print("⚠️ Outro ID: ");
      Serial.println(r.ID);
      parar();
      delay(200);
      continue;
    }

    int x = r.xCenter - 160;
    int w = r.width;
    int h = r.height;

    Serial.print("🎯 ID ");
    Serial.print(ID_ATUAL);
    Serial.print(" – X: "); Serial.print(x);
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

        if (ID_ATUAL == ID1) {
          Serial.println("⏱️ Esperar 10 segundos...");
          delay(10000);  // pausa após ID1
          ID_ATUAL = ID2;
          Serial.println("➡️ Procurar TAG ID2...");
          break;
        } else if (ID_ATUAL == ID2) {
          Serial.println("✅ ID2 atingido – Fim do desafio");
          while (true) {
            parar(); // mantém parado
          }
        }
      }
    }

    delay(200);
  }
}
