#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial huskySerial(8, 9); // RX = D8, TX = D9

// Dimensões da imagem da HuskyLens (resolução padrão)
const int IMG_WIDTH  = 320;
const int IMG_HEIGHT = 240;

// Ponto central como (0, 0), estilo cartesiano
const int X_CENTER = IMG_WIDTH  / 2;
const int Y_CENTER = IMG_HEIGHT / 2;

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("🔍 A iniciar HuskyLens (modo Object Tracking)...");

  huskySerial.begin(9600);
  if (!huskylens.begin(huskySerial)) {
    Serial.println("❌ ERRO: HuskyLens não detetada!");
    while (true); // trava o programa
  }

  Serial.println("✅ HuskyLens pronta. A ler objetos...");
}

void loop() {
  if (huskylens.request()) {
    if (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();

      // Posição bruta (X,Y) da HuskyLens
      int x_raw = result.xCenter;
      int y_raw = result.yCenter;

      // Conversão para referencial cartesiano centrado
      int x_cart = x_raw - X_CENTER;         // Esquerda (-) / Direita (+)
      int y_cart = -(y_raw - Y_CENTER);      // Cima (+) / Baixo (-)

      // Impressão dos valores
      Serial.print("🎯 Objeto detetado | ");
      Serial.print("Centro (X, Y): ");
      Serial.print(x_raw);
      Serial.print(", ");
      Serial.print(y_raw);
      Serial.print("  ➤  Referencial: ");
      Serial.print(x_cart);
      Serial.print(", ");
      Serial.println(y_cart);
    } else {
      Serial.println("⚠️ Nenhum objeto detetado.");
    }
  } else {
    Serial.println("❌ ERRO: HuskyLens não comunicável!");
  }

  delay(300); // tempo entre leituras
}
