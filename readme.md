# 🤖 AzorCAR – Robô Educativo Open Source com Visão Computacional

**AzorCAR** é um robô autónomo modular, desenvolvido com base em **Arduino UNO R4 WiFi** e **câmara HuskyLens**, com foco em aplicações pedagógicas de programação, visão computacional e controlo de movimento. Criado no âmbito da pós-graduação **PRIA – Universidade dos Açores**, o projeto serve como ferramenta educativa, experimental e de participação em desafios como o **AzoresBot**.

---

## 🗂️ Estrutura do Projeto

```
AzorCAR/
├── 01_documentacao/           → Guias técnicos, fichas, anotações
├── 02_hardware/               → Lista de componentes, esquemas elétricos e físicos
├── 03_software_arduino/       → Código principal: HuskyLens, motores, OLED, desafios
├── 04_microbit/               → Testes com micro:bit e Maqueen (fase 0)
├── 05_raspberry_pi/           → Planeamento futuro com Pi 5 + OpenCV
├── 06_ros2/                   → Estrutura reservada para futura integração com ROS 2
├── 07_simulacao/              → Ambientes simulados (Webots ou similares)
├── 08_design_3d/              → Ficheiros STL/OBJ da estrutura e suportes
├── 09_lidar/                  → Notas e testes com sensores LIDAR (planeado)
├── 10_recursos_pedagogicos/  → Fichas didáticas, planos de aula e atividades STEM
├── 11_apresentacao/           → Slides, vídeos, imagens para divulgação
├── 12_azoresbot/              → Regras e materiais oficiais do desafio AzoresBot
├── 13_artigo_cientifico/      → Artigo PIF (Springer LNAI) e referências académicas
├── 14_website/                → Página web local / mockup para divulgação online
```

---

## ⚙️ Tecnologias e Componentes

| Componente             | Função                                      |
|------------------------|---------------------------------------------|
| Arduino UNO R4 WiFi    | Controlo principal                          |
| HuskyLens (DFRobot)    | Visão computacional com IA integrada        |
| Driver L298P           | Controlo de motores DC                      |
| Motores + rodas        | Locomoção do robô                           |
| OLED SH1106 (128x64)   | Feedback visual em tempo real               |
| Servo motor SG90       | Rotação horizontal da câmara (opcional)     |
| Powerbank / Li-ion     | Fonte de alimentação                        |

---

## 🎯 Funcionalidades

✅ Deteção de cor e TAGs com HuskyLens  
✅ Aproximação autónoma ao alvo (15–25 cm)  
✅ Correção lateral com base no eixo X da imagem  
✅ Paragem automática + temporização  
✅ Procura sequencial de múltiplos IDs (por etapas)  
✅ Visualização de dados em OLED e monitor série  
✅ Rotação inicial de 360° para varrimento  
✅ Organização modular do código por tarefas  

---

## 🧪 Casos de Uso

- 💡 **Educação STEM** no 3.º ciclo e secundário  
- 🧩 **Desafios competitivos** com regras reais (AzoresBot)  
- 🧠 **Exploração de IA embarcada** com HuskyLens  
- 🧰 **Protótipo de baixo custo** e personalizável  
- 👨‍🏫 **Ferramenta de apoio em clubes de robótica escolar**  

---

## 📸 Galeria

> Fotos e esquemas do robô, da arena e da HuskyLens em funcionamento podem ser consultados na pasta [`11_apresentacao`](./11_apresentacao) e [`imagens`](./11_apresentacao/imagens).

---

## 🚀 Caminho Futuro

🟡 Integração de múltiplas TAGs (sequência lógica)  
🟡 Controlo por interface web (via Wi-Fi)  
🟡 Uso de simulação (fase ROS 2)  
🟡 Navegação por mapa com LIDAR (opcional)  
🟢 Artigo científico PRIA em progresso (`13_artigo_cientifico`)  
🟢 Preparação para partilha open source e kits educativos

---

## 📚 Recursos e Referências

- 📘 [HuskyLens Wiki (DFRobot)](https://wiki.dfrobot.com/HUSKYLENS_Vision_Sensor_SKU_SEN0305)
- 🧪 [Learn DFRobot HuskyLens Course](https://learn.dfrobot.com/)
- 🖥️ [U8g2 OLED Library](https://github.com/olikraus/u8g2)
- 🔧 [Arduino Documentation](https://docs.arduino.cc/)
- 📄 [Artigo “AzorCAR” – Versão PRIA 2025 (em preparação)]

---

## 🧑‍💻 Autor

**João Pavão**  
Pós-Graduação em Programação, Robótica e Inteligência Artificial  
Universidade dos Açores · 2025  
[github.com/joaopavao1979](https://github.com/joaopavao1979)

---

## ⚖️ Licença

Este projeto é disponibilizado sob a [Licença MIT](./LICENSE_AzorCAR).  
Sinta-se à vontade para reutilizar, modificar ou adaptar para fins **educativos e não comerciais**.  
Contribuições são bem-vindas!

---

## 🙌 Agradecimentos

A todos os colegas, professores e membros da PRIA que contribuíram com ideias, testes e apoio técnico ao longo do desenvolvimento deste projeto.

---

## 🤝 Como Contribuir

1. Faça um fork deste repositório  
2. Crie uma nova branch (`git checkout -b feature/minha-funcionalidade`)  
3. Commit das suas alterações (`git commit -m 'Nova funcionalidade'`)  
4. Push para a branch (`git push origin feature/minha-funcionalidade`)  
5. Abra um Pull Request e descreva a sua proposta

> Detalhes em [`CONTRIBUTING_AzorCAR`](./CONTRIBUTING_AzorCAR)
