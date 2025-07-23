// ==========================================================================
// 🤖 AzorCAR – Aproximação automática baseada em HuskyLens (Desafio I)
// ==========================================================================
// ✅ Deteta uma cor de cada vez com a HuskyLens (modo Color Recognition)
// ✅ Mede o tamanho da caixa detetada (largura e altura)
// ✅ Decide automaticamente se deve andar para a frente, para trás ou parar
// ✅ Movimenta-se por pequenos passos (300 ms) e reavalia continuamente
// ✅ Totalmente comentado para facilitar calibração e adaptação
// ==========================================================================

#include <SoftwareSerial.h>
#include <HUSKYLENS.h>
#include <Wire.h>
#include <U8g2lib.h>

// -------------------- HuskyLens via UART --------------------
SoftwareSerial huskySerial(8, 9);  // RX, TX para ligação à HuskyLens
HUSKYLENS huskylens;

// -------------------- OLED SH1106 1.3” via I2C --------------------
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// -------------------- Driver de motores L298P --------------------
const int E1 = 10;  // PWM motor direito
const int M1 = 12;  // Sentido motor direito
const int E2 = 11;  // PWM motor esquerdo
const int M2 = 13;  // Sentido motor esquerdo

// -------------------- Configurações de movimento --------------------
const int VELOCIDADE = 100;      // 🔧 Velocidade dos motores (0–255)
const int DURACAO_PASSO = 300;   // 🔧 Tempo de cada passo de movimento (em ms)

// -------------------- Calibração dos limites de aproximação --------------------
// Estes limites definem a zona "ideal" de distância ao alvo (ex: entre 20–40 cm)
// Os valores são obtidos observando a largura e altura da caixa detetada

const int W_MIN = 50;   // 🔧 Se largura < W_MIN → está longe → anda para frente
const int W_MAX = 90;   // 🔧 Se largura > W_MAX → está muito perto → anda para trás

const int H_MIN = 45;   // 🔧 Se altura < H_MIN → longe
const int H_MAX = 85;   // 🔧 Se altura > H_MAX → muito perto

// -------------------- Identificação das cores treinadas --------------------
String corPorID(int id) {
  switch (id) {
    case 1: return "Verde";
    case 2: return "Amarelo";  // ← usarás esta na prova
    case 3: return "Magenta";
    case 4: return "Azul";
    default: return "Desconhecida";
  }
}

// -------------------- Funções de controlo dos motores --------------------
void andarFrente(int vel, int tempo) {
  digitalWrite(M1, 1);
  digitalWrite(M2, 1);
  analogWrite(E1, vel);
  analogWrite(E2, vel);
  delay(tempo);
  parar();
}

void andarTras(int vel, int tempo) {
  digitalWrite(M1, 0);
  digitalWrite(M2, 0);
  analogWrite(E1, vel);
  analogWrite(E2, vel);
  delay(tempo);
  parar();
}

void parar() {
  analogWrite(E1, 0);
  analogWrite(E2, 0);
  digitalWrite(M1, 0);
  digitalWrite(M2, 0);
}

// -------------------- Setup --------------------
void setup() {
  Serial.begin(115200);       // Comunicação Serial para calibração
  huskySerial.begin(9600);    // Comunicação com HuskyLens
  u8g2.begin();               // Inicia OLED

  // Pinos dos motores
  pinMode(E1, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(M2, OUTPUT);
  parar();  // Garante paragem ao ligar

  // Verifica HuskyLens
  if (!huskylens.begin(huskySerial)) {
    Serial.println("❌ HuskyLens não encontrada!");
    while (true);
  }

  Serial.println("✅ AzorCAR pronto – Aproximação automática passo-a-passo.");
  Serial.println("Observa W/H no Serial para ajustar os limites.");
}

// -------------------- Loop principal --------------------
void loop() {
  // Solicita deteção à HuskyLens
  if (huskylens.request()) {
    if (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();

      // Extrai dados
      int id = result.ID;
      int largura = result.width;
      int altura = result.height;
      String cor = corPorID(id);

      // -------------------- Decisão baseada em W e H --------------------
      String acao;

      if (largura < W_MIN || altura < H_MIN) {
        acao = "FRENTE";
        andarFrente(VELOCIDADE, DURACAO_PASSO);
      }
      else if (largura > W_MAX || altura > H_MAX) {
        acao = "TRAS";
        andarTras(VELOCIDADE, DURACAO_PASSO);
      }
      else {
        acao = "PARAR";
        parar();
      }

      // -------------------- Saída no Serial Monitor --------------------
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

      // -------------------- OLED (ID, W/H e ação) --------------------
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
      // Nada detetado → parar motores + feedback
      Serial.println("Nenhuma cor detectada.");
      parar();

      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(25, 35, "Sem deteccao");
      u8g2.sendBuffer();
    }
  }

  delay(300); // Aguarda antes da próxima leitura
}
