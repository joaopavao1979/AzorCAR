#include <SoftwareSerial.h>
#include <HUSKYLENS.h>
#include <Wire.h>
#include <U8g2lib.h>

// Comunicação com a HuskyLens (pinos 8 e 9)
SoftwareSerial huskySerial(8, 9);
HUSKYLENS huskylens;

// OLED SH1106 1.3” via I2C
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// Mapeamento de ID para cor aprendida
String corPorID(int id) {
  switch (id) {
    case 1: return "Verde";
    case 2: return "Amarelo";
    case 3: return "Magenta";
    case 4: return "Azul";
    default: return "Desconhecida";
  }
}

void setup() {
  Serial.begin(115200);        // Serial rápida para feedback fluido
  huskySerial.begin(9600);     // Comunicação com HuskyLens
  u8g2.begin();                // Inicializa OLED

  if (!huskylens.begin(huskySerial)) {
    Serial.println("Erro: HuskyLens não encontrada.");
    while (1); // trava o programa
  }

  Serial.println("Sistema pronto – mostra ID + cor no OLED e dados no Serial.");
}

void loop() {
  if (huskylens.request()) {
    if (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();

      int id = result.ID;
      String cor = corPorID(id);

      // Coordenadas relativas ao centro
      int xRel = result.xCenter - 160;
      int yRel = 120 - result.yCenter;

      // Tamanho da caixa
      int largura = result.width;
      int altura = result.height;

      // === SERIAL ===
      Serial.print("ID: ");
      Serial.print(id);
      Serial.print(" | Cor: ");
      Serial.print(cor);
      Serial.print(" | X,Y: ");
      Serial.print(xRel);
      Serial.print(",");
      Serial.print(yRel);
      Serial.print(" | W,H: ");
      Serial.print(largura);
      Serial.print("x");
      Serial.println(altura);

      // === OLED: apenas ID + nome da cor ===
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_fub14_tr);
      
      char linha[32];
      sprintf(linha, "ID %d: %s", id, cor.c_str());
      u8g2.drawStr(5, 40, linha);

      u8g2.sendBuffer();
    }
    else {
      // Sem deteção
      Serial.println("Nenhuma cor detectada.");
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(25, 35, "Sem deteccao");
      u8g2.sendBuffer();
    }
  }

  delay(300);
}
