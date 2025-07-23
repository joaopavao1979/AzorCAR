#include <SoftwareSerial.h>
#include <HUSKYLENS.h>
#include <Wire.h>
#include <U8g2lib.h>

// === Comunicação com a HuskyLens via UART (pinos 8 e 9) ===
SoftwareSerial huskySerial(8, 9); 
HUSKYLENS huskylens;

// === OLED 1.3” SH1106 via I2C ===
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// === Mapeamento de IDs para nomes de cores aprendidas ===
String corPorID(int id) {
  switch (id) {
    case 1: return "Verde";
    case 2: return "Amarelo";
    case 3: return "Magenta";
    case 4: return "Azul";
    default: return "Desconhecida";
  }
}

// === Desenha um padrão gráfico diferente para cada cor reconhecida ===
void desenharBarra(int id) {
  switch (id) {
    case 1: // Verde → barra superior
      u8g2.drawBox(0, 0, 128, 8);
      break;
    case 2: // Amarelo → pontos na base
      for (int i = 0; i < 128; i += 4)
        u8g2.drawPixel(i, 60);
      break;
    case 3: // Magenta → bloco central
      u8g2.drawBox(50, 25, 30, 10);
      break;
    case 4: // Azul → moldura
      u8g2.drawFrame(5, 5, 118, 54);
      break;
    default:
      // Sem gráfico
      break;
  }
}

void setup() {
  // Inicializa comunicações
  Serial.begin(9600);
  huskySerial.begin(9600);
  u8g2.begin();

  // Verifica a HuskyLens
  if (!huskylens.begin(huskySerial)) {
    Serial.println("HuskyLens não encontrada!");
    while (true); // bloqueia
  }

  Serial.println("Sistema iniciado – Color Recognition com múltiplas cores.");
}

void loop() {
  // Solicita deteção à HuskyLens
  if (huskylens.request()) {
    if (huskylens.available()) {

      // === Preparar array para IDs únicos (até 4) ===
      int ids[4] = {0, 0, 0, 0};
      int total = 0;

      // === Ler todos os blocos visíveis na imagem ===
      while (huskylens.available()) {
        HUSKYLENSResult result = huskylens.read();
        int id = result.ID;

        // Verifica se é um ID novo
        bool novo = true;
        for (int i = 0; i < total; i++) {
          if (ids[i] == id) {
            novo = false;
            break;
          }
        }

        // Se for novo, guarda-o (máx. 4)
        if (novo && total < 4) {
          ids[total++] = id;
        }
      }

      // === Mostrar todos os IDs no Monitor Serial ===
      Serial.print("Cores detectadas: ");
      for (int i = 0; i < total; i++) {
        Serial.print("ID ");
        Serial.print(ids[i]);
        Serial.print(" (");
        Serial.print(corPorID(ids[i]));
        Serial.print(")  ");
      }
      Serial.println();

      // === OLED: mostrar apenas a 1ª cor detetada (mais próxima) ===
      u8g2.clearBuffer();
      if (total > 0) {
        int id = ids[0];
        desenharBarra(id); // Desenho visual

        u8g2.setFont(u8g2_font_ncenB08_tr);
        u8g2.drawStr(10, 35, "Cor principal:");
        u8g2.setFont(u8g2_font_fub14_tr);
        u8g2.drawStr(10, 55, corPorID(id).c_str());
      }
      u8g2.sendBuffer();
    }

    else {
      // === Nenhuma deteção — limpa OLED e informa via Serial ===
      Serial.println("Nenhuma cor detectada.");

      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(30, 35, "Sem deteccao");
      u8g2.sendBuffer();
    }
  }

  delay(300); // Intervalo entre frames
}
