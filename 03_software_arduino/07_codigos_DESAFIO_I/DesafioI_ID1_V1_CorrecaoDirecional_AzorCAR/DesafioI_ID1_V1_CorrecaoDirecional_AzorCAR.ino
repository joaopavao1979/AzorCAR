// =================================================================================
// 🤖 HuskyCar Challenge – Desafio I – V1.1: Controlo de Movimento Independente
// =================================================================================
// Objetivo:
// Controlar o robô com base na deteção de cor (ID1), com parâmetros de velocidade
// e tempo separados para movimentos de avanço e rotação, permitindo uma
// afinação mais precisa.
//
// O robô:
// - Fica parado se não detetar nada
// - Só reage ao ID1
// - Corrige a direção com velocidade/tempo de ROTAÇÃO
// - Aproxima-se/recua com velocidade/tempo de AVANÇO
// - Para automaticamente na zona ideal
//
// Utilização:
// 1. Treinar a HuskyLens com uma cor (ID1)
// 2. Afinar os parâmetros de movimento e calibração para um desempenho suave
// 3. Ligar o sistema: o robô alinhar-se-á e aproximar-se-á do alvo.
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

// Faixa ideal de proximidade (ajustar com calibração real)
const int W_MIN = 75;
const int W_MAX = 120;
const int H_MIN = 75;
const int H_MAX = 116;

// Tolerância para correção de direção com base no X (centrado em 0)
const int LIMIAR_X = 15;

// ---------------------- Parâmetros de Movimento ---------------------------
// --- Controlo de Avanço/Recuo ---
const int VEL_AVANCO = 120;   // Velocidade para andar para a frente/trás (0-255)
const int TEMPO_AVANCO = 150; // Duração do passo para a frente/trás (ms)

// --- Controlo de Rotação ---
const int VEL_ROTACAO = 110;    // Velocidade para virar (geralmente menor para precisão)
const int TEMPO_ROTACAO = 100; // Duração do passo de rotação (geralmente mais curto)

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
  u8x8.drawString(0, 1, "Aguardando ID1...");
}

// ---------------------- Loop principal --------------------------
void loop() {
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

  // ----------- Corrigir direção se não estiver centrado -----------
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
    // ---------- Já centrado → avaliar distância (W/H) ----------
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
void andarTras(int vel, int tempo) {
  digitalWrite(M1, HIGH); digitalWrite(M2, HIGH);
  analogWrite(E1, vel); analogWrite(E2, vel);
  delay(tempo);
  parar();
}

void andarFrente(int vel, int tempo) {
  digitalWrite(M1, LOW); digitalWrite(M2, LOW);
  analogWrite(E1, vel); analogWrite(E2, vel);
  delay(tempo);
  parar();
}

void virarDireita(int vel, int tempo) {
  digitalWrite(M1, HIGH); digitalWrite(M2, LOW);
  analogWrite(E1, vel); analogWrite(E2, vel);
  delay(tempo);
  parar();
}

void virarEsquerda(int vel, int tempo) {
  digitalWrite(M1, LOW); digitalWrite(M2, HIGH);
  analogWrite(E1, vel); analogWrite(E2, vel);
  delay(tempo);
  parar();
}

void parar() {
  analogWrite(E1, 0); analogWrite(E2, 0);
  digitalWrite(M1, LOW); digitalWrite(M2, LOW);
}