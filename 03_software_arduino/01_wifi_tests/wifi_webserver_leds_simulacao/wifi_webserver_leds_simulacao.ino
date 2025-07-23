// ========================================
// 📡 AzorCAR - Controlo remoto por Wi-Fi
// Simulação com LEDs usando Web Server HTTP
//
// Desenvolvido para o Arduino UNO R4 WiFi (com ESP32-S3)
// Corrigido para evitar duplicações no browser (client.stop())
//
// LED VERDE  → sistema ON
// LED VERMELHO → modo PARAR
// LED AMARELO → motor ESQUERDO
// LED AZUL   → motor DIREITO
// ========================================

#include <WiFiS3.h>  // Biblioteca para ESP32-S3 no Arduino UNO R4 WiFi

// -------- Pinos digitais para LEDs ----------
const int LED_VERDE_ON = 2;
const int LED_VERMELHO_PARAR = 4;
const int LED_AMARELO_ESQ = 5;
const int LED_AZUL_DIR = 6;

// -------- Credenciais da rede Wi-Fi ----------
char ssid[] = "NomeREDE";      // ← Substitui pelo nome da tua rede
char pass[] = "123456";      // ← Substitui pela tua password

int status = WL_IDLE_STATUS;
WiFiServer server(80);                 // Porta HTTP padrão

bool sistemaAtivo = false;            // Guarda estado ON/OFF

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Aguarda ligação ao monitor serial

  // Configura pinos dos LEDs como saídas
  pinMode(LED_VERDE_ON, OUTPUT);
  pinMode(LED_VERMELHO_PARAR, OUTPUT);
  pinMode(LED_AMARELO_ESQ, OUTPUT);
  pinMode(LED_AZUL_DIR, OUTPUT);

  apagarTodosLEDs();  // Inicializa com todos apagados

  // Conecta-se à rede Wi-Fi
  Serial.print("Ligando à rede Wi-Fi");
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    delay(2000);
    Serial.print(".");
  }

  Serial.println("\n✅ Conectado!");
  Serial.print("📡 IP Local: ");
  Serial.println(WiFi.localIP());

  server.begin();  // Inicia o servidor web
}

void loop() {
  WiFiClient client = server.available();  // Espera por um cliente

  if (client) {
    Serial.println("\n📶 Cliente conectado");

    String request = client.readStringUntil('\r');  // Lê primeira linha da requisição
    Serial.print("📥 Requisição: ");
    Serial.println(request);
    client.flush();  // Limpa dados residuais

    // Processamento de comandos
    if (request.indexOf("/start") != -1) {
      sistemaAtivo = true;
      acenderLEDsStart();
    }
    else if (request.indexOf("/stop") != -1) {
      sistemaAtivo = false;
      acenderLEDParar();
    }

    // Resposta HTML
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println("<!DOCTYPE html><html><head><meta charset='UTF-8'><title>AzorCAR Web</title></head>");
    client.println("<body style='text-align:center;font-family:sans-serif;'>");
    client.println("<h2>🚗 AzorCAR - Controlo Remoto</h2>");
    client.print("<p>Estado atual: <strong>");
    client.print(sistemaAtivo ? "ATIVO ✅" : "INATIVO ⛔");
    client.println("</strong></p>");
    client.println("<a href='/start'><button style='font-size:20px;'>▶️ Start</button></a>");
    client.println("<a href='/stop'><button style='font-size:20px;'>⛔ Stop</button></a>");
    client.println("<a href='/status'><button style='font-size:20px;'>ℹ️ Status</button></a>");
    client.println("</body></html>");

    client.stop();  // ✅ Fecha corretamente a ligação
    Serial.println("✅ Cliente desconectado");
  }
}

// ---------------------- Funções auxiliares -----------------------

void apagarTodosLEDs() {
  digitalWrite(LED_VERDE_ON, LOW);
  digitalWrite(LED_VERMELHO_PARAR, LOW);
  digitalWrite(LED_AMARELO_ESQ, LOW);
  digitalWrite(LED_AZUL_DIR, LOW);
}

void acenderLEDsStart() {
  apagarTodosLEDs();
  digitalWrite(LED_VERDE_ON, HIGH);
  digitalWrite(LED_AMARELO_ESQ, HIGH);
  digitalWrite(LED_AZUL_DIR, HIGH);
}

void acenderLEDParar() {
  apagarTodosLEDs();
  digitalWrite(LED_VERMELHO_PARAR, HIGH);
}
