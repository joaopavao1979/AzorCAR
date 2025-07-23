// ============================================================================
// 🤖 AzorCAR – Controlo via Wi-Fi com ajuste independente das rodas
// ----------------------------------------------------------------------------
// O utilizador define a velocidade e duração de cada roda (esquerda e direita)
// através de uma interface web simples (browser).
// Desenvolvido para Arduino UNO R4 WiFi com shield L298P.
// ============================================================================

#include <WiFiS3.h>  // Biblioteca de Wi-Fi para o Arduino UNO R4 WiFi

// ------------------ Definições da rede Wi-Fi ------------------
char ssid[] = "Xiaomi T11";         // 🔒 Substituir pelo nome da tua rede
char pass[] = "petitus2022";     // 🔒 Substituir pela password

WiFiServer server(80);           // Servidor HTTP na porta 80

// ------------------ Pinos do motor (L298P) ------------------
const int E1 = 10;  // PWM motor direito
const int M1 = 12;  // Direção motor direito
const int E2 = 11;  // PWM motor esquerdo
const int M2 = 13;  // Direção motor esquerdo

// ------------------ Parâmetros de controlo ------------------
int velDir = 150;
int tempoDir = 500;
int velEsq = 150;
int tempoEsq = 500;

void setup() {
  Serial.begin(9600);

  // Configura os pinos como saídas
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);

  // Liga à rede Wi-Fi
  Serial.println("🔌 A ligar ao Wi-Fi...");
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\n✅ Ligado ao Wi-Fi!");
  Serial.print("🌐 Endereço IP: ");
  Serial.println(WiFi.localIP());

  server.begin();  // Inicia o servidor web
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("\n📥 Cliente conectado.");

    String request = client.readStringUntil('\r');
    client.flush();

    // Analisa parâmetros da URL (ex: /mover?vel1=120&tempo1=400&vel2=180&tempo2=600)
    if (request.indexOf("/mover") != -1) {
      velDir = extrairParametro(request, "vel1", velDir);
      tempoDir = extrairParametro(request, "tempo1", tempoDir);
      velEsq = extrairParametro(request, "vel2", velEsq);
      tempoEsq = extrairParametro(request, "tempo2", tempoEsq);

      Serial.println("🚗 A executar movimento...");
      moverRodas();
    }

    // Envia a página HTML para o navegador
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println(gerarHTML());

    client.stop();
    Serial.println("❎ Cliente desconectado.");
  }
}

// ------------------ Função para mover as rodas ------------------
void moverRodas() {
  // Define direção para frente
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);

  analogWrite(E1, velDir);
  analogWrite(E2, velEsq);

  delay(max(tempoDir, tempoEsq));  // Espera pelo maior tempo

  parar();
}

// ------------------ Função para parar os motores ------------------
void parar() {
  analogWrite(E1, 0);
  analogWrite(E2, 0);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
}

// ------------------ Extrai valor de um parâmetro da URL ------------------
int extrairParametro(String req, String nome, int valorAtual) {
  int idx = req.indexOf(nome + "=");
  if (idx != -1) {
    int inicio = idx + nome.length() + 1;
    int fim = req.indexOf("&", inicio);
    if (fim == -1) fim = req.indexOf(" ", inicio);
    String valorStr = req.substring(inicio, fim);
    int valor = valorStr.toInt();
    if (valor >= 0 && valor <= 2550) return valor;
  }
  return valorAtual;
}

// ------------------ Página HTML dinâmica ------------------
String gerarHTML() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>AzorCAR Web</title></head><body>";
  html += "<h2>🚗 AzorCAR – Controlo Remoto por Wi-Fi</h2>";
  html += "<form action='/mover' method='GET'>";
  html += "<p><strong>Roda Direita</strong><br>";
  html += "Velocidade (0–255): <input name='vel1' value='" + String(velDir) + "'><br>";
  html += "Tempo (ms): <input name='tempo1' value='" + String(tempoDir) + "'></p>";
  html += "<p><strong>Roda Esquerda</strong><br>";
  html += "Velocidade (0–255): <input name='vel2' value='" + String(velEsq) + "'><br>";
  html += "Tempo (ms): <input name='tempo2' value='" + String(tempoEsq) + "'></p>";
  html += "<button type='submit'>▶️ Mover</button></form>";
  html += "<p><em>Após clicar, o robô move-se conforme os valores indicados.</em></p>";
  html += "</body></html>";
  return html;
}
