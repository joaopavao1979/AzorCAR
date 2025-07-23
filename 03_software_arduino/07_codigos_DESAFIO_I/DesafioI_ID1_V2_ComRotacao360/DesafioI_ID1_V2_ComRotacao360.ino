// =================================================================================
// 🤖 HuskyCar Challenge – Desafio I – V1.4: Controlo de Movimento com Rotação Inicial
// =================================================================================

#include <SoftwareSerial.h>
#include <HUSKYLENS.h>
#include <U8x8lib.h>

SoftwareSerial huskySerial(8, 9); // RX, TX (UART para HuskyLens)
HUSKYLENS huskylens;
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8;

// ---------------------- Configuração de motores ---------------------------
const int E1 = 10;  // PWM Motor Direito
const int M1 = 12;  // Direção Motor Direito
const int E2 = 11;  // PWM Motor Esquerdo
const int M2 = 13;  // Direção Motor Esquerdo

// ---------------------- Parâmetros de Calibração da HuskyLens --------------
const int ID1 = 1;            // ID a detetar
const int W_MIN = 75;
const int W_MAX = 120;
const int H_MIN = 75;
const int H_MAX = 116;
const int LIMIAR_X = 15;

// ---------------------- Parâmetros de Movimento ---------------------------
const int VEL_AVANCO = 140;
const int TEMPO_AVANCO = 150;
const int VEL_ROTACAO = 110;
const int TEMPO_ROTACAO = 100;

// --- Rotação inicial (360° até encontrar ID1) ---
int velocidadeRotacao = 110;
int tempoDeRotacao = 4000;
bool rotacaoFeita = false;

// ---------------------- Setup --------------------------
void setup() {
  Serial.begin(9600);
  huskySerial.begin(9600);
  u8x8.begin();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);

  pinMode(E1, OUTPUT); pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT); pinMode(M2, OUTPUT);
  parar();

  if (!huskylens.begin(huskySerial)) {
    Serial.println("HuskyLens nao encontrada!");
    u8x8.drawString(0, 1, "Sem HuskyLens");
    while (1);
  }

  Serial.println("Sistema iniciado.");
  u8x8.drawString(0, 1, "A iniciar busca...");
}

// ---------------------- Função de rotação até encontrar ID1 --------------------------
void rotacao360_ate_ID1() {
  Serial.println("Rotacao inicial (360 graus)...");
  u8x8.drawString(0, 1, "Rotacao inicial");

  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  analogWrite(E1, velocidadeRotacao);
  analogWrite(E2, velocidadeRotacao);
  delay(tempoDeRotacao);

  Serial.println("A iniciar procura de ID1...");
  u8x8.drawString(0, 1, "Procurando ID1...");

  while (true) {
    digitalWrite(M1, LOW);
    digitalWrite(M2, HIGH);
    analogWrite(E1, velocidadeRotacao);
    analogWrite(E2, velocidadeRotacao);

    if (huskylens.request() && huskylens.available()) {
      HUSKYLENSResult r = huskylens.read();
      if (r.ID == ID1) {
        parar();
        Serial.println("ID1 encontrado!");
        u8x8.drawString(0, 1, "ID1 encontrado!");
        delay(1000);
        break;
      }
    }
  }
}

// ---------------------- Loop principal --------------------------
void loop() {
  if (!rotacaoFeita) {
    rotacao360_ate_ID1();
    rotacaoFeita = true;
  }

  if (!huskylens.request() || !huskylens.available()) {
    Serial.println("Nenhuma deteccao.");
    u8x8.drawString(0, 3, "Sem deteccao     ");
    parar();
    delay(200);
    return;
  }

  HUSKYLENSResult r = huskylens.read();
  if (r.ID != ID1) {
    Serial.println("ID nao corresponde.");
    u8x8.drawString(0, 3, "Outro ID         ");
    parar();
    delay(200);
    return;
  }

  int x = r.xCenter - 160;
  int w = r.width;
  int h = r.height;

  Serial.print("ID1 | X: "); Serial.print(x);
  Serial.print(" | W: "); Serial.print(w);
  Serial.print(" | H: "); Serial.println(h);

  if (x < -LIMIAR_X) {
    Serial.println(" → Virar ESQUERDA");
    u8x8.drawString(0, 3, "Corrigir: ESQ    ");
    virarEsquerda(VEL_ROTACAO, TEMPO_ROTACAO);
  }
  else if (x > LIMIAR_X) {
    Serial.println(" → Virar DIREITA");
    u8x8.drawString(0, 3, "Corrigir: DIR    ");
    virarDireita(VEL_ROTACAO, TEMPO_ROTACAO);
  }
  else {
    if (w < W_MIN || h < H_MIN) {
      Serial.println(" → FRENTE");
      u8x8.drawString(0, 3, "Avancar          ");
      andarFrente(VEL_AVANCO, TEMPO_AVANCO);
    }
    else if (w > W_MAX || h > H_MAX) {
      Serial.println(" → TRAS");
      u8x8.drawString(0, 3, "Recuar           ");
      andarTras(VEL_AVANCO, TEMPO_AVANCO);
    }
    else {
      Serial.println(" → PARAR (ideal)");
      u8x8.drawString(0, 3, "Parado (ideal)   ");
      parar();
    }
  }

  delay(200);
}

// ---------------------- Funções de movimento --------------------------
void andarFrente(int vel, int tempo) {
  digitalWrite(M1, HIGH); digitalWrite(M2, HIGH);
  analogWrite(E1, vel); analogWrite(E2, vel);
  delay(tempo);
  parar();
}

void andarTras(int vel, int tempo) {
  digitalWrite(M1, LOW); digitalWrite(M2, LOW);
  analogWrite(E1, vel); analogWrite(E2, vel);
  delay(tempo);
  parar();
}

void virarEsquerda(int vel, int tempo) {
  digitalWrite(M1, HIGH); digitalWrite(M2, LOW);
  analogWrite(E1, vel); analogWrite(E2, vel);
  delay(tempo);
  parar();
}

void virarDireita(int vel, int tempo) {
  digitalWrite(M1, LOW); digitalWrite(M2, HIGH);
  analogWrite(E1, vel); analogWrite(E2, vel);
  delay(tempo);
  parar();
}

void parar() {
  analogWrite(E1, 0); analogWrite(E2, 0);
  digitalWrite(M1, LOW); digitalWrite(M2, LOW);
}
