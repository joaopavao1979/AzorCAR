# 📡 Descrição do Código – `wifi_webserver_leds_simulacao.ino`

Este código implementa um sistema de **controlo remoto por Wi-Fi** para o Arduino UNO R4 WiFi, com **simulação do estado e movimento de um robô** através de 4 LEDs.

É possível **ligar/desligar o sistema e observar visualmente os estados** do robô (ON, Parar, Motor ESQ, Motor DIR) diretamente a partir de um browser, usando uma interface web mínima.

---

## 🔁 Funcionamento passo-a-passo

### 🔹 1. Inicialização (`setup()`)

- Inicia comunicação com o Serial Monitor.
- Define os pinos `D2`, `D4`, `D5` e `D6` como saídas digitais para os LEDs:
  - `D2` → LED VERDE → sistema ON
  - `D4` → LED VERMELHO → modo PARAR
  - `D5` → LED AMARELO → motor ESQUERDO
  - `D6` → LED AZUL → motor DIREITO
- Apaga todos os LEDs ao início.
- Tenta ligar-se à rede Wi-Fi com as credenciais fornecidas.
- Quando a ligação for bem-sucedida, imprime o IP local no Serial Monitor.
- Inicia o Web Server na porta 80 (HTTP).

---

### 🔹 2. Loop principal (`loop()`)

- Espera por um cliente (navegador ou app).
- Lê o pedido HTTP (`/start`, `/stop`, `/status`) enviado pelo browser.
- Interpreta o pedido e atualiza o estado do sistema.

---

### 🔹 3. Comandos disponíveis

| Comando HTTP recebido | Ação executada |
|-----------------------|----------------|
| `/start`              | Liga LEDs Verde, Amarelo e Azul (simula robô em movimento). |
| `/stop`               | Liga apenas o LED Vermelho (simula paragem total). |
| `/status`             | Apenas mostra o estado atual no browser (sem alterar LEDs). |

---

### 🔹 4. Interface web gerada

- O Arduino responde com uma página HTML simples.
- Mostra o título do projeto, estado atual (ATIVO/INATIVO) e três botões:
  - `▶️ Start` → envia `/start`
  - `⛔ Stop` → envia `/stop`
  - `ℹ️ Status` → envia `/status`

---

### 🔹 5. Fecho da ligação

- Após enviar a página HTML, o Arduino fecha corretamente a ligação com `client.stop();`.
- Isto evita duplicações da interface no browser (problema comum quando `client.stop()` está ausente).

---

## 🔦 Comportamento visual dos LEDs

| Estado do sistema | Verde (ON) | Vermelho (PARAR) | Amarelo (ESQ) | Azul (DIR) |
|-------------------|------------|------------------|----------------|-------------|
| Inicial           | OFF        | OFF              | OFF            | OFF         |
| `/start` enviado  | ON         | OFF              | ON             | ON          |
| `/stop` enviado   | OFF        | ON               | OFF            | OFF         |

---

## 📘 Resumo técnico

- Comunicação via Web Server HTTP (`WiFiS3.h`)
- Interface simples via browser (sem app externa)
- LEDs simulam o estado e os motores do robô
- Ideal para testes de bancada e demonstrações pedagógicas
- Base futura para integrar sensores, motores reais ou lógica automática

---

> 💡 Este código pode ser expandido facilmente para incluir leitura da HuskyLens, controlo de motores reais com L298P, ou lógica baseada em sensores.

