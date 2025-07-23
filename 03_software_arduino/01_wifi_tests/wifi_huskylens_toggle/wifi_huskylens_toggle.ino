// ===========================================================
// 🤖 AzorCAR – Etapa 3 FINAL: Controlo Web + HuskyLens + Modo Offline
// -----------------------------------------------------------
// - Interface Web via Wi-Fi (quando disponível)
// - Leitura da HuskyLens com reconhecimento de cores
// - LEDs simulam ações do robô
// - Funciona mesmo sem Wi-Fi disponível (modo offline)
// ===========================================================

#include <WiFiS3.h>
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

// 📡 Credenciais da rede Wi-Fi
char ssid[] = "nome rede";
char pass[] = "senha rede";

// 🌐 Servidor Web
WiFiServer server(80);
bool wifiLigado = false;         // Estado da ligação Wi-Fi
bool modoVisaoAtivo = false;     // Estado do modo visão

// 🎦 Comunicação com HuskyLens
SoftwareSerial mySerial(8, 9); // RX, TX
HUSKYLENS huskylens;

// 💡 Pinos dos LEDs
const int ledVerde    = 2;
const int ledVermelho = 4;
const int ledAmarelo  = 5;
const int ledAzul     = 6;

void setup() {
  Serial.begin(9600);
  delay(1000);

  // Inicialização dos LEDs
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  apagarTodosLEDs();

  // Tenta ligar ao Wi-Fi (máx 10 seg.)
  Serial.print("🔌 A tentar ligar ao Wi-Fi");
  WiFi.begin(ssid, pass);
  unsigned long t0 = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t0 < 10000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    wifiLigado = true;
    Serial.println("\n✅ Ligado ao Wi-Fi");
    Serial.print("🌐 IP: ");
    Serial.println(WiFi.localIP());
    server.begin();
  } else {
    Serial.println("\n⚠️ Wi-Fi não disponível. A correr em modo offline.");
    modoVisaoAtivo = false; // Ativa (true) ou desativa(false) o modo visão em modo offline
  }

  // Inicia comunicação com a HuskyLens
  mySerial.begin(9600);
  if (!huskylens.begin(mySerial)) {
    Serial.println("❌ HuskyLens não ligada.");
  } else {
    Serial.println("✅ HuskyLens pronta.");
  }

  digitalWrite(ledVerde, HIGH); // LED de sistema ligado
}

void loop() {
  // Parte Web (só se Wi-Fi ligado)
  if (wifiLigado) {
    WiFiClient client = server.available();
    if (client) {
      String request = client.readStringUntil('\r');
      Serial.println("\n📥 Pedido: " + request);
      client.flush();

      if (request.indexOf("/start") != -1) {
        modoVisaoAtivo = true;
      } else if (request.indexOf("/stop") != -1) {
        modoVisaoAtivo = false;
        apagarTodosLEDs();
        digitalWrite(ledVerde, HIGH);
      }

      // Página HTML
      String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>AzorCAR</title></head><body>";
      html += "<h2>🤖 AzorCAR – Modo Visão</h2>";
      html += "<p>Estado: <strong>" + String(modoVisaoAtivo ? "ATIVO" : "INATIVO") + "</strong></p>";
      html += "<a href='/start'><button>▶️ Start</button></a> ";
      html += "<a href='/stop'><button>⛔ Stop</button></a> ";
      html += "<a href='/status'><button>ℹ️ Status</button></a>";
      html += "</body></html>";

      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println();
      client.println(html);
      client.stop();
    }
  }

  // Parte da visão (sempre ativa se modoVisaoAtivo estiver true)
  if (modoVisaoAtivo) {
    if (huskylens.request()) {
      if (huskylens.available()) {
        HUSKYLENSResult result = huskylens.read();
        int id = result.ID;
        Serial.print("🎯 ID Detetado: ");
        Serial.println(id);

        apagarTodosLEDs();
        digitalWrite(ledVerde, HIGH);

        if (id == 1) {
          Serial.println("↪️ Virar à esquerda");
          digitalWrite(ledAmarelo, HIGH);
        } else if (id == 2) {
          Serial.println("↩️ Virar à direita");
          digitalWrite(ledAzul, HIGH);
        } else if (id == 3) {
          Serial.println("⛔ Parar");
          digitalWrite(ledVermelho, HIGH);
        } else {
          Serial.println("⚠️ ID desconhecido");
        }
      }
    }
  }

  delay(300);
}

// 🔄 Apagar todos os LEDs
void apagarTodosLEDs() {
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledAzul, LOW);
}
