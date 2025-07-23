// ==========================================================================
// 🤖 AzorCAR – Controlo com TAGs HuskyLens e motores com L298P
// ==========================================================================
// - Usa o modo TAG RECOGNITION da HuskyLens
// - Controla o robô com base nas TAGs detetadas (IDs 1 a 8)
// - Driver L298P (pinos E1, E2, M1, M2)
// ==========================================================================

#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

// ------------------ HuskyLens + UART ------------------
SoftwareSerial huskySerial(8, 9); // RX (D8), TX (D9)
HUSKYLENS huskylens;

// ------------------ Motores ------------------
const int E1 = 10;  // PWM motor A (direita)
const int M1 = 12;  // Direção motor A
const int E2 = 11;  // PWM motor B (esquerda)
const int M2 = 13;  // Direção motor B

int velocidade = 150;          // Velocidade inicial (0–255)
const int duracao = 1000;      // Tempo de movimento (ms)

void setup() {
  Serial.begin(9600);
  huskySerial.begin(9600);

  // Iniciar comunicação com HuskyLens
  if (huskylens.begin(huskySerial)) {
    Serial.println("✅ HuskyLens conectada.");
  } else {
    Serial.println("❌ Erro: HuskyLens não conectada!");
    while (1);
  }

  // Pinos do motor
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);

  parar(); // Começa parado
}

void loop() {
  if (huskylens.request()) {
    if (huskylens.available()) {
      HUSKYLENSResult resultado = huskylens.read();
      int tagID = resultado.ID;

      Serial.print("📷 TAG detetada: ID = ");
      Serial.println(tagID);

      // Executa ação baseada na TAG
      switch (tagID) {
        case 1:
          andarFrente();
          break;
        case 2:
          parar();
          break;
        case 3:
          virarEsquerda();
          break;
        case 4:
          virarDireita();
          break;
        case 5:
          andarTras();
          break;
        case 6:
          velocidade += 20;
          if (velocidade > 255) velocidade = 255;
          Serial.print("⚡ Velocidade aumentada para: ");
          Serial.println(velocidade);
          break;
        case 7:
          velocidade -= 20;
          if (velocidade < 0) velocidade = 0;
          Serial.print("🐢 Velocidade reduzida para: ");
          Serial.println(velocidade);
          break;
        case 8:
          parar();
          velocidade = 150;
          Serial.println("🔄 Reset: parou e velocidade reiniciada.");
          break;
        default:
          Serial.println("❓ TAG não reconhecida.");
          break;
      }
    }
  }

  delay(200); // Evita leituras excessivas
}

// ------------------ Funções de movimento ------------------

void andarFrente() {
  Serial.println("⬆️ Frente");
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  analogWrite(E1, velocidade);
  analogWrite(E2, velocidade);
  delay(duracao);
  parar();
}

void andarTras() {
  Serial.println("⬇️ Trás");
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E1, velocidade);
  analogWrite(E2, velocidade);
  delay(duracao);
  parar();
}

void virarEsquerda() {
  Serial.println("↪️ Virar esquerda");
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, velocidade);
  analogWrite(E2, velocidade);
  delay(duracao);
  parar();
}

void virarDireita() {
  Serial.println("↩️ Virar direita");
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, velocidade);
  analogWrite(E2, velocidade);
  delay(duracao);
  parar();
}

void parar() {
  Serial.println("🛑 Parado");
  analogWrite(E1, 0);
  analogWrite(E2, 0);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
}

