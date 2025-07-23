#include <SoftwareSerial.h>
#include <HUSKYLENS.h>
#include <Wire.h>
#include <U8g2lib.h>

// === Comunicação com HuskyLens ===
SoftwareSerial huskySerial(8, 9);
HUSKYLENS huskylens;

// === OLED SH1106 via I2C ===
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// === Limiares de largura (W) e altura (H) ===
// Estes valores podem ser iguais ou diferentes
const int W_MIN = 50;   // abaixo → longe
const int W_MAX = 90;   // acima → muito perto
const int H_MIN = 45;   // idem
const int H_MAX = 85;

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
  Serial.begin(115200);
  huskySerial.begin(9600);
  u8g2.begin();

  if (!huskylens.begin(huskySerial)) {
    Serial.println("HuskyLens não encontrada.");
    while (1);
  }

  Serial.println("Sistema iniciado – Calibração separada de W e H.");
  Serial.println("--------------------------------------------------");
  Serial.println("Formato: ID | W,H | Ação (baseada em ambos)");
}

void loop() {
  if (huskylens.request()) {
    if (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();

      int id = result.ID;
      int largura = result.width;
      int altura = result.height;
      String cor = corPorID(id);

      // === Lógica de decisão com base em W e H separadamente ===
      String acao;

      if (largura < W_MIN || altura < H_MIN) {
        acao = "ANDA FRENTE";
      } else if (largura > W_MAX || altura > H_MAX) {
        acao = "ANDA TRAS";
      } else {
        acao = "PARAR";
      }

      // === Serial Monitor ===
      Serial.print("ID ");
      Serial.print(id);
      Serial.print(" (");
      Serial.print(cor);
      Serial.print(") | W,H: ");
      Serial.print(largura);
      Serial.print("x");
      Serial.print(altura);
      Serial.print(" | Ação: ");
      Serial.println(acao);

      // === OLED: W, H e ação (opcional) ===
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_ncenB08_tr);
      
      char linha1[30];
      sprintf(linha1, "ID %d: %s", id, cor.c_str());
      u8g2.drawStr(0, 15, linha1);

      char linha2[30];
      sprintf(linha2, "W:%d  H:%d", largura, altura);
      u8g2.drawStr(0, 35, linha2);

      u8g2.setFont(u8g2_font_fub14_tr);
      u8g2.drawStr(0, 60, acao.c_str());

      u8g2.sendBuffer();
    }
    else {
      // Nenhuma deteção
      Serial.println("Nenhuma cor detectada.");
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(25, 35, "Sem deteccao");
      u8g2.sendBuffer();
    }
  }

  delay(300); // tempo entre leituras
}
