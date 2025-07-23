#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

// Define pinos de comunicação com a HuskyLens
SoftwareSerial huskySerial(8, 9); // RX = D8, TX = D9
HUSKYLENS huskylens;

void setup() {
  Serial.begin(9600);
  Serial.println("🔄 Iniciar sistema...");

  // Inicia comunicação com HuskyLens
  huskySerial.begin(9600);
  Serial.print("🔍 A testar comunicação com HuskyLens...");

  if (huskylens.begin(huskySerial)) {
    Serial.println(" ✅ Comunicação OK");
  } else {
    Serial.println("❌ ERRO: HuskyLens não detetada!");
    while (1); // Para o programa aqui se não detetar
  }
}

void loop() {
  if (huskylens.request()) {
    if (huskylens.available()) {
      HUSKYLENSResult r = huskylens.read();

      Serial.println("✅ Objeto detetado:");
      Serial.print("🔹 ID: "); Serial.println(r.ID);
      Serial.print("🔹 X : "); Serial.println(r.xCenter);
      Serial.print("🔹 Y : "); Serial.println(r.yCenter);
      Serial.println("--------------------------");
    } else {
      Serial.println("⚠️ Nenhum objeto detetado.");
    }
  } else {
    Serial.println("❌ ERRO ao comunicar com HuskyLens.");
  }

  delay(300);
}
