# AzorCAR 🚗🌋

**AzorCAR** é um projeto educacional, científico e open source que visa o desenvolvimento de um carro robótico autónomo baseado em Arduino e Raspberry Pi 5, com suporte para sensores de distância, LIDAR, visão computacional e navegação inteligente. Este projeto será aplicado em contextos pedagógicos, feiras de ciência (ex: AzoresBot) e como plataforma de aprendizagem em robótica, IA e ROS 2.

---

## 🎯 Objetivos do Projeto

- Desenvolver um **robô móvel autónomo** com capacidades de evitar obstáculos, seguir trajetos e reagir ao ambiente.
- Integrar sensores como **ultrassónicos**, **LIDAR**, e **câmaras USB** com processamento em Python.
- Explorar **Visão Computacional** com OpenCV e MediaPipe.
- Criar uma base sólida para **expansão com ROS 2 e simulação em Webots**.
- Fornecer documentação, fichas pedagógicas e materiais open source reutilizáveis.

---

## 📁 Estrutura de Pastas

| Pasta                          | Descrição                                                                         |
|-------------------------------|------------------------------------------------------------------------------------|
| `01_documentacao/`            | Planeamento geral, objetivos, cronogramas e análise de projetos anteriores.        |
| `02_hardware/`                | Lista de componentes, esquemas elétricos e imagens da montagem física.             |
| `03_software_arduino/`        | Sketches Arduino (evitador, sensores, motores).                                    |
| `04_raspberry_pi/`            | Scripts Python para visão, deteção de cor, controlo e testes com câmera.           |
| `05_ros2/`                    | Pacotes ROS 2, nós em Python, ficheiros `.launch.py`, `URDF` e simulações futuras. |
| `06_simulacao/`               | Ficheiros do Webots: mundos `.wbt`, modelos 3D e controladores.                    |
| `07_design_3d/`               | STL e ficheiros FreeCAD para impressão 3D do chassi e suportes.                    |
| `08_testes/`                  | Relatórios e scripts de calibração de sensores e motores.                          |
| `09_lidar/`                   | Scripts de visualização com RPLIDAR A2, dados brutos e integração ROS.             |
| `10_recursos_pedagogicos/`    | Fichas de atividade, guias para professores, propostas de aula.                    |
| `11_apresentacao/`            | Posters, imagens, vídeos e apresentações para o AzoresBot.                         |
| `12_azoresbot/`               | Adaptação de desafios para o AzorCAR.                                              |
| `13_artigo_cientifico/`       | Manuscrito do artigo final (Markdown ou LaTeX), figuras e bibliografia.            |
| `14_website/`                 | Ficheiros para futura publicação com GitHub Pages.                                 |

---

## 💡 Tecnologias Usadas

- **Arduino UNO/Nano** com L298P (controlo de motores)
- **Raspberry Pi 5 (8GB)** com Ubuntu 25.04
- **Python 3** + OpenCV + MediaPipe
- **RPLIDAR A2** para mapeamento e deteção de obstáculos
- **ROS 2 Humble** (futuramente)
- **Webots** para simulação 3D

---

## 👥 Público-Alvo

- Professores e alunos do ensino básico e secundário (STEM)
- Estudantes de ensino superior em Engenharia, Robótica, IA
- Entusiastas maker e educadores
- Organizadores de eventos e feiras tecnológicas

---

## 🔓 Licença

Este projeto é licenciado sob a [MIT License](LICENSE), com todos os recursos educacionais e imagens sob Creative Commons BY-NC-SA 4.0.

---

## 🤝 Contribuições

Contribuições são bem-vindas!  
Podes propor melhorias, adicionar exemplos, corrigir erros ou traduzir conteúdos.  
Verifica o ficheiro `CONTRIBUTING.md` (em breve) para mais detalhes.

---

## 📢 Nota

O projeto **AzorCAR** é inspirado por projetos anteriores de alunos da PRIA e pelo desafio **HuskyCar Challenge do AzoresBot**, mas é uma iniciativa **completamente autónoma, com visão open source e integração de tecnologias acessíveis** como webcam, sensores baratos e Arduino.

---

---

# 🤖 AzorCAR

**AzorCAR** é um projeto educativo e científico de robótica autónoma, desenvolvido com Arduino, Raspberry Pi 5, sensores variados e visão computacional. É open source, modular e adaptável para ensino, feiras tecnológicas, clubes de robótica e aplicações pedagógicas interdisciplinares.

---

## 📂 Estrutura Geral do Projeto

| Pasta | Descrição |
|-------|-----------|
| [01_documentacao](./01_documentacao) | Planeamento, objetivos, cronogramas e análise de projetos |
| [02_hardware](./02_hardware) | Lista de componentes, esquemas, fotos de montagem e testes |
| [03_software_arduino](./03_software_arduino) | Sketches e testes com Arduino UNO/Nano e o shield L298P |
| [04_raspberry_pi](./04_raspberry_pi) | Scripts Python para visão computacional e sensores via GPIO |
| [05_ros2](./05_ros2) | Integração com ROS 2 (nós, URDFs, launchers, comunicação) |
| [06_simulacao](./06_simulacao) | Simulações com Webots: mundos, controladores e testes virtuais |
| [07_design_3d](./07_design_3d) | Modelos STL/FreeCAD para impressão 3D do robô e acessórios |
| [08_testes](./08_testes) | Calibração, validação de sensores, motores e desempenho |
| [09_lidar](./09_lidar) | Visualização de dados com RPLIDAR, scripts e dados CSV |
| [10_recursos_pedagogicos](./10_recursos_pedagogicos) | Fichas de atividade, planos de aula, guias e propostas didáticas |
| [11_apresentacao](./11_apresentacao) | Posters, slides, imagens e vídeos para eventos e divulgação |
| [12_azoresbot](./12_azoresbot) | Desafio tipo maze inspirado no HuskyCar – versão open e pedagógica |
| [13_artigo_cientifico](./13_artigo_cientifico) | Estrutura do artigo final, referências, figuras e manuscrito |
| [14_website](./14_website) | Arquivos e estrutura para criar um site estático (GitHub Pages) |

---

## 🧩 Tecnologias e Linguagens Usadas

- 🛠️ **Arduino UNO/Nano** com C++
- 🐍 **Python 3** (para visão computacional, sensores e LIDAR)
- 🧠 **OpenCV, MediaPipe** para análise visual e deteção de padrões
- 📡 **RPLIDAR A2** para navegação 2D e mapeamento
- 🧭 **ROS 2 Humble** para integração avançada e navegação autónoma
- 🧪 **Webots** para simulação 3D e desenvolvimento seguro antes do teste físico
- 🧱 **FreeCAD, STL** para design e impressão de peças

---

## 🎓 Aplicações Educativas

- Ensino STEAM (Física, Química, TIC, Matemática, Robótica)
- Projetos interdisciplinares com 2.º, 3.º ciclo e ensino secundário
- Apoio a clubes de programação e oficinas maker
- Demonstrações públicas e participação em eventos (como AzoresBot)
- Desenvolvimento de competências em pensamento computacional e raciocínio lógico

---

## 📖 Licença

Este projeto é distribuído sob a [MIT License](./LICENSE_AzorCAR.txt).  
Conteúdos pedagógicos estão sob Creative Commons BY-NC-SA 4.0.

---

## 🤝 Contribuições

Aceitamos melhorias, exemplos, testes e adaptações pedagógicas.  
Consulta o [guia de contribuição](./CONTRIBUTING_AzorCAR.md) para saber como participar.

---

> 🌍 Este projeto é 100% open source, educativo e adaptável.  
> Concebido para ensinar, inspirar e aproximar a robótica de todos.