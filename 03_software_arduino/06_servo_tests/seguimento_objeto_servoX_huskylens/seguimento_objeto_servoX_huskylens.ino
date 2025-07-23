// ===================================================================
// 🤖 AzorCAR – Etapa 4: Seguimento de objeto no eixo X com servo
// -------------------------------------------------------------------
// VERSÃO FINAL CORRIGIDA
// -------------------------------------------------------------------
// A HuskyLens deve estar em modo "Object Tracking".
// O Arduino UNO R4 WiFi lê a posição X do objeto e move um servo horizontal.
// O centro da imagem (160,120) é mapeado como (0,0) no referencial cartesiano.
// ===================================================================

#include <Servo.h>              // Biblioteca oficial para controlo de servos
#include "HUSKYLENS.h"          // Biblioteca oficial da HuskyLens (DFRobot)
#include "SoftwareSerial.h"     // Comunicação UART em pinos alternativos

// ------------------ Definições de hardware ------------------
const int SERVO_PIN_X = 10;     // Pino digital onde o servo está ligado
Servo servoX;                   // Objeto para controlar o servo no eixo X

SoftwareSerial huskySerial(6, 7); // Comunicação com HuskyLens: RX = D8, TX = D9
HUSKYLENS huskylens;              // Objeto principal da câmara

// ------------------ Variáveis de controlo ------------------
int posX = 90;                 // Posição atual do servo (inicia ao centro)
bool objetoDetetado = false;   // Flag para saber se há deteção ativa

void setup() {
  Serial.begin(9600);
  Serial.println("🔄 A iniciar AzorCAR Etapa 4 (Versão Corrigida)...");

  // Inicia e centraliza o servo
  servoX.attach(SERVO_PIN_X);
  posX = 90;               // Centro da amplitude (0-180 graus)
  servoX.write(posX);
  Serial.println("✅ Servo ligado e centrado (90º)");

  // Inicia a comunicação com a HuskyLens
  huskySerial.begin(9600);
  delay(300); // Dar tempo para a estabilização da comunicação

  // Verifica se a HuskyLens está a responder
  if (huskylens.begin(huskySerial)) {
    Serial.println("✅ HuskyLens ligada com sucesso.");
  } else {
    Serial.println("❌ ERRO CRÍTICO: HuskyLens não comunicável! Verifique as ligações.");
    while (1); // Para toda a execução em caso de erro na inicialização
  }
}

void loop() {
  // 1. Tenta solicitar dados da HuskyLens.
  if (!huskylens.request()) {
    // Se a solicitação falhar, é um erro de comunicação.
    Serial.println("❌ Erro ao solicitar dados à HuskyLens. Verifique as ligações.");
  }
  // 2. Se a solicitação foi bem-sucedida, processa os dados.
  else {
    // 2.1 Verifica se há algum objeto detetado disponível nos dados recebidos.
    if (huskylens.available()) {
      HUSKYLENSResult r = huskylens.read(); // Lê os dados do primeiro objeto detetado
      
      // Se um objeto foi detetado, atualiza a flag
      if (!objetoDetetado) {
        objetoDetetado = true;
        Serial.println("🎯 Objeto detetado!");
      }

      // Converte a coordenada X da imagem para um referencial cartesiano (-160 a +160)
      // O centro da imagem da HuskyLens (320x240) é (160, 120).
      int xCartesiano = r.xCenter - 160;

      // Mostra a posição no monitor série para depuração
      Serial.print("  → Posição X (cartesiano): ");
      Serial.println(xCartesiano);

      // Mapeia a posição cartesiana do objeto (-160 a +160) para o ângulo do servo (0 a 180)
      posX = map(xCartesiano, -160, 160, 0, 180);

      // Garante que o valor final está dentro dos limites seguros do servo (0 e 180)
      posX = constrain(posX, 0, 180);

      // Envia o comando de posição para o servo
      servoX.write(posX);
    }
    // 2.2 Se a comunicação funcionou, mas NENHUM objeto foi detetado...
    else {
      // Se o objeto estava a ser detetado no ciclo anterior, mostra uma mensagem única.
      if (objetoDetetado) {
        Serial.println("⚠️ Objeto deixou de ser visível. Mantendo a última posição.");
        objetoDetetado = false; // Reinicia a flag para evitar mensagens repetidas
      }
      // Se não há objeto, o servo simplesmente mantém a sua última posição.
    }
  }

  // Pequena pausa para evitar movimentos excessivamente bruscos e sobrecarga do sistema.
  delay(100);
}