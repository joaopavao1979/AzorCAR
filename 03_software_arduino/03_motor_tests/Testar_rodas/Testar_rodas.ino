// ==========================================================================
// 🤖 AzorCAR – Menu Serial para controlo de movimento com L298P
// ==========================================================================
// Permite escolher:
// - Velocidade (mesma para ambas as rodas)
// - Direção: frente, trás, virar esquerda ou direita
// - Duração do movimento (em ms)
// ==========================================================================

// -------------------- Pinos e configuração --------------------
const int E1 = 10;  // PWM motor A (direita)
const int M1 = 12;  // Direção motor A
const int E2 = 11;  // PWM motor B (esquerda)
const int M2 = 13;  // Direção motor B

int velocidade = 150;      // Velocidade padrão (0–255)
int duracao = 1000;        // Duração padrão em ms

void setup() {
  Serial.begin(9600);
  pinMode(E1, OUTPUT); // Velocidade da roda DIREITA
  pinMode(M1, OUTPUT); // SENTIDO da roda DIREITA (1 FRENTE e 0 TRAS)
  pinMode(E2, OUTPUT); // Velocidade da roda ESQ
  pinMode(M2, OUTPUT); // SENTIDO da roda ESQ (1 FRENTE e 0 TRAS)
  parar();

  Serial.println("🚗 AzorCAR – Menu de Movimento");
}

void loop() {
  mostrarMenu();

  while (!Serial.available()) delay(100);
  int opcao = Serial.readStringUntil('\n').toInt();

  switch (opcao) {
    case 1:
      Serial.print("⚙️ Nova velocidade (0–255): ");
      velocidade = lerValor();
      break;

    case 2:
      Serial.print("⏱️ Nova duração (ms): ");
      duracao = lerValor();
      break;

    case 3:
      Serial.println("⬆️ Movimento para a FRENTE");
      andarFrente(velocidade, duracao);
      break;

    case 4:
      Serial.println("⬇️ Movimento para TRÁS");
      andarTras(velocidade, duracao);
      break;

    case 5:
      Serial.println("↪️ Virar para a ESQUERDA");
      virarEsquerda(velocidade, duracao);
      break;

    case 6:
      Serial.println("↩️ Virar para a DIREITA");
      virarDireita(velocidade, duracao);
      break;

    case 0:
      mostrarParametros();
      break;

    default:
      Serial.println("❌ Opção inválida.");
      break;
  }

  limparBuffer();
}

// ------------------- Funções de Movimento -------------------

void andarFrente(int vel, int tempo) {
  digitalWrite(M1, 1);  // F DIR
  digitalWrite(M2, 1);  // F ESQ
  analogWrite(E1, vel); // Velocidade DIR
  analogWrite(E2, vel);   // Velocidade ESQ
  delay(tempo);
  parar();
}

void andarTras(int vel, int tempo) {
  digitalWrite(M1, 0);  // T DIR
  digitalWrite(M2, 0);  // T ESQ
  analogWrite(E1, vel);   // Velocidade DIR
  analogWrite(E2, vel); // Velocidade ESQ
  delay(tempo);
  parar();
}

void virarEsquerda(int vel, int tempo) {
  digitalWrite(M1, 1);  // F DIR
  digitalWrite(M2, 0);  // T ESQ
  analogWrite(E1, vel); // Velocidade DIR
  analogWrite(E2, vel); // Velocidade ESQ
  delay(tempo);
  parar();
}

void virarDireita(int vel, int tempo) {
  digitalWrite(M1, 0);  // T DIR
  digitalWrite(M2, 1);  // F ESQ
  analogWrite(E1, vel); // Velocidade DIR
  analogWrite(E2, vel); // Velocidade ESQ
  delay(tempo);
  parar();
}

void parar() {
  analogWrite(E1, 0);
  analogWrite(E2, 0);
  digitalWrite(M1, 0);
  digitalWrite(M2, 0);
}

// ------------------- Funções auxiliares -------------------

int lerValor() {
  while (!Serial.available()) delay(100);
  int val = Serial.readStringUntil('\n').toInt();
  Serial.println(val);
  return val;
}

void mostrarMenu() {
  Serial.println("\n========= MENU =========");
  Serial.println("1. Definir velocidade");
  Serial.println("2. Definir duração (ms)");
  Serial.println("3. Andar para FRENTE");
  Serial.println("4. Andar para TRÁS");
  Serial.println("5. Virar ESQUERDA");
  Serial.println("6. Virar DIREITA");
  Serial.println("0. Mostrar parâmetros atuais");
  Serial.print(">> ");
}

void mostrarParametros() {
  Serial.println("🔧 Parâmetros atuais:");
  Serial.print("Velocidade: "); Serial.println(velocidade);
  Serial.print("Duração: "); Serial.print(duracao); Serial.println(" ms");
}

void limparBuffer() {
  while (Serial.available()) Serial.read();
}
