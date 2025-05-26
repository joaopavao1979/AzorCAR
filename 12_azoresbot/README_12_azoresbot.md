
# 📁 12_azoresbot

## 📌 Descrição
Esta pasta reúne recursos, ideias e propostas para desenvolver um **desafio de navegação autónoma tipo Maze (labirinto)**, inspirado em competições como **RoboCup Rescue Maze** e **AzoresBot HuskyCar Challenge**.

O objetivo é construir um percurso modular com obstáculos, zonas de decisão, marcadores visuais e desafios de lógica, no qual o robô **AzorCAR** deve navegar, interpretar e reagir de forma autónoma.

---

## 🎯 Objetivo do desafio Maze

Simular um cenário educativo e competitivo onde o robô:
- Navega por um percurso labiríntico
- Identifica e reage a zonas visuais (cores, símbolos, formas)
- Evita obstáculos e ajusta trajeto
- Executa decisões com base em padrões ou regras pré-programadas
- Explora o ambiente com visão, LIDAR ou sensores simples

---

## 🧠 Possibilidades de Implementação

| Elemento            | Versão prática no AzorCAR                   |
|---------------------|---------------------------------------------|
| Labirinto físico    | Paredes em cartão/pvc, chão com pista ou cor |
| Marcadores visuais  | Formas A4 coladas nas paredes ou chão        |
| Sensores            | Câmera USB + OpenCV, ultrassónicos, LIDAR    |
| Decisões programadas| Máquina de estados, contadores, lógica de cores |
| "Pontuação"         | Contagem de zonas visitadas ou símbolos vistos |

---

## 📂 Estrutura sugerida

- `plano_labirinto.md` — planta do labirinto modular (pode ser impresso ou simulado).
- `marcadores/` — imagens SVG/PNG para impressão (círculos, triângulos, QR codes).
- `pistas_exemplo/` — percursos de treino e competição.
- `avaliacao.md` — critérios e grelha de pontuação (inspirado em concursos).
- `video_demonstacao/` — exemplos de funcionamento em vídeo (opcional).

---

## 🧩 Dicas de construção

- Usa fita isoladora preta ou impressões em papel para criar o trajeto no chão.
- Reaproveita caixas de cartão ou impressões 3D para criar obstáculos.
- Cria zonas de decisão com cores fortes (vermelho, verde, azul).
- Marca pontos de reconhecimento com etiquetas visuais (ex: OpenCV detecta formas).

---

## 🧪 Objetivo pedagógico

- Trabalhar navegação autónoma com sensores reais
- Estimular a resolução de problemas com feedback visual
- Desenvolver raciocínio lógico com base em máquina de estados
- Aplicar visão computacional de forma acessível
- Incentivar trabalho em grupo com tarefas interdisciplinares

---

> 🚧 **Nota:** Esta pasta pode crescer com os teus próprios desafios! Podes criar variações do labirinto e propor desafios diferentes para cada turma, nível ou objetivo pedagógico.
