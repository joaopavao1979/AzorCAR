
// ============================================================================
// 🤖 AzorCAR – Etapa 5: Controlo dos motores com base na HuskyLens
// ----------------------------------------------------------------------------
// Modo recomendado: "Object Tracking" ou "Color Recognition"
// IDs:
//   → ID 1 → virar à ESQUERDA (ambos os motores giram para esquerda)
//   → ID 2 → virar à DIREITA (ambos os motores giram para direita)
//   → ID 3 → PARAR
// ----------------------------------------------------------------------------
// Substituímos os LEDs por controlo real dos motores (via driver L298P)
// Arduino UNO R4 WiFi + HuskyLens via SoftwareSerial (pinos 8 e 9)
// ============================================================================

#include "HUSKYLENS.h"         // Biblioteca oficial da HuskyLens
#include "SoftwareSerial.h"    // Comunicação UART com a câmara

// 📡 Comunicação serial com a HuskyLens
SoftwareSerial huskySerial(8, 9); // RX = D8, TX = D9
HUSKYLENS huskylens;

// ----------------------------
// Pinos do driver L298P
// ----------------------------
const int E1 = 10; // PWM motor A (direita)
const int M1 = 12; // Direção motor A
const int E2 = 11; // PWM motor B (esquerda)
const int M2 = 13; // Direção motor B

int velocidade = 200; // Velocidade padrão dos motores (PWM: 0 a 255)

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("🔄 Início do sistema AzorCAR – Etapa 5");

  // Inicializa os pinos dos motores
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  parar(); // Por segurança, começa parado

  // Inicia a comunicação com a HuskyLens
  huskySerial.begin(9600);
  delay(300);
  if (!huskylens.begin(huskySerial)) {
    Serial.println("❌ ERRO: HuskyLens não detetada!");
    while (1); // Bloqueia o programa
  } else {
    Serial.println("✅ HuskyLens pronta.");
  }
}

void loop() {
  // Solicita deteções da HuskyLens
  if (huskylens.request()) {
    if (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      int id = result.ID;

      Serial.print("🎯 ID Detetado: ");
      Serial.println(id);

      // Ações com base no ID detetado
      switch (id) {
        case 1:
          Serial.println("↪️ Comando: virar à ESQUERDA");
          virarEsquerda();
          break;

        case 2:
          Serial.println("↩️ Comando: virar à DIREITA");
          virarDireita();
          break;

        case 3:
          Serial.println("⛔ Comando: PARAR");
          parar();
          break;

        default:
          Serial.println("⚠️ ID desconhecido – manter estado anterior.");
          break;
      }
    } else {
      Serial.println("🚫 Nenhum objeto visível – parar por segurança.");
      parar();
    }
  } else {
    Serial.println("❌ ERRO: Falha na comunicação com a HuskyLens.");
    parar();
  }

  delay(200); // Tempo de resposta controlado
}

// ------------------------
// Funções de movimento
// ------------------------
void virarEsquerda() {
  digitalWrite(M1, LOW);   // Motor A → trás
  digitalWrite(M2, HIGH);  // Motor B → frente
  analogWrite(E1, velocidade);
  analogWrite(E2, velocidade);
}

void virarDireita() {
  digitalWrite(M1, HIGH);  // Motor A → frente
  digitalWrite(M2, LOW);   // Motor B → trás
  analogWrite(E1, velocidade);
  analogWrite(E2, velocidade);
}

void parar() {
  analogWrite(E1, 0);
  analogWrite(E2, 0);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
}
