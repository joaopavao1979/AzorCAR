
# 📁 03_software_arduino

## 📌 Descrição
Esta pasta contém todos os códigos-fonte (sketches `.ino`) desenvolvidos para o **Arduino UNO/Nano**, usados no controlo direto dos motores, sensores de distância, leitura de dados e lógica local do robô **AzorCAR**.

A programação em Arduino é essencial para prototipagem, testes rápidos e funcionamento autónomo do robô em situações onde o Raspberry Pi está desligado ou funciona apenas como supervisor.

---

## 📂 Subpastas e ficheiros sugeridos

- `evitador_obstaculos/evitador.ino`  
  Código para teste com sensor ultrassónico e desvio automático.

- `seguidor_linha/seguidor.ino`  
  Algoritmo simples para seguir linha usando sensores de infravermelhos (ex: TCRT5000).

- `testes_motores/teste_motor.ino`  
  Teste individual dos motores DC com o shield L298P.

- `testes_sensores/teste_ultrassonico.ino`  
  Teste de leitura da distância frontal.

- `controlador_misto.ino`  
  Integração de múltiplos sensores e lógica de tomada de decisão simples baseada em estados.

---

## 💡 Notas Técnicas

- A maioria dos testes será feita com o **Arduino UNO R4 WiFi**, que tem maior capacidade e porta USB-C.
- Também podes usar um **Arduino Nano** em versões finais mais compactas do robô.
- O shield **L298P** encaixa diretamente no UNO e permite controlar dois motores DC de forma eficiente.
- A leitura de sensores como o **HC-SR04 (ultrassónico)** e **sensores de linha** será feita via pinos digitais e analógicos.
- Futuramente, a comunicação entre o Arduino e o Raspberry Pi poderá ser feita via **UART ou I2C**.

---

## 🎯 Objetivo pedagógico

- Praticar programação básica em C++ para microcontroladores.
- Desenvolver raciocínio lógico e reativo (if/else, delays, estados).
- Testar sensores e atuadores de forma modular antes de avançar para ROS 2.
- Ensinar eletrónica aplicada com base na robótica educativa.

---

> 🧪 **Dica pedagógica:** inicia com códigos isolados para cada sensor e motor. Só depois combina tudo num controlador geral. Isso facilita a depuração e a aprendizagem passo a passo.
