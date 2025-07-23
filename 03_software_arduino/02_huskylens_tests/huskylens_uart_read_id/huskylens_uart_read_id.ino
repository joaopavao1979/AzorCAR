// =======================================
// 📷 AzorCAR – Teste de comunicação com HuskyLens
// Leitura de ID de objeto via UART (SoftwareSerial)
// ---------------------------------------
// Pinos:
// TX da HuskyLens → D8 (RX do Arduino)
// RX da HuskyLens ← D9 (TX do Arduino)
// GND em comum entre HuskyLens e Arduino
// =======================================

#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

// Pinos para comunicação UART com a HuskyLens
SoftwareSerial mySerial(8, 9);  // RX, TX
HUSKYLENS huskylens;

void setup() {
  Serial.begin(9600);           // Monitor Serial
  mySerial.begin(9600);         // Comunicação com a HuskyLens
  while (!Serial);

  Serial.println("🔍 Iniciando comunicação com HuskyLens...");

  // Inicializa a HuskyLens usando a porta definida
  if (!huskylens.begin(mySerial)) {
    Serial.println("❌ Erro: HuskyLens não detectada.");
  } else {
    Serial.println("✅ HuskyLens ligada com sucesso!");
  }
}

void loop() {
  // Tenta obter os dados do frame atual
  if (huskylens.request()) {
    if (huskylens.available()) {
      Serial.println("📦 Deteção ativa:");

      while (huskylens.available()) {
        HUSKYLENSResult result = huskylens.read();

        // Mostra o ID e coordenadas
        Serial.print("🔹 ID: ");
        Serial.print(result.ID);
        Serial.print(" | X: ");
        Serial.print(result.xCenter);
        Serial.print(" | Y: ");
        Serial.println(result.yCenter);
      }
    } else {
      Serial.println("⛔ Nada detetado.");
    }
  } else {
    Serial.println("⚠️ Falha na comunicação com a HuskyLens.");
  }

  delay(500);  // Pausa entre ciclos
}
