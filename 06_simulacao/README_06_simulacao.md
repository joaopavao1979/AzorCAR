
# 📁 06_simulacao

## 📌 Descrição
Esta pasta contém os mundos, modelos e controladores desenvolvidos no simulador **Webots**, usados para testar, validar e treinar o comportamento do robô **AzorCAR** num ambiente virtual antes de implementar no mundo real.

A simulação é uma etapa essencial para desenvolver algoritmos com segurança e rapidez, especialmente em robótica educativa.

---

## 📂 Estrutura sugerida

- `mundos/` — ficheiros `.wbt` com o ambiente virtual completo.
- `modelos_3d/` — modelos de sensores, chassi e obstáculos (formato `.proto`, `.obj`, `.stl`).
- `controladores/` — scripts para controlar o robô no ambiente simulado (Python/C).

---

## 🧪 Objetivos da simulação

- Testar comportamento de sensores (ultrassónicos, LIDAR, visão)
- Avaliar navegação e seguimento de linha
- Simular labirintos, zonas coloridas, obstáculos móveis
- Testar lógica reativa e tomada de decisão (ex: máquina de estados)
- Prototipar o jogo/lógica do AzorCAR em contexto educacional

---

## 💻 Exemplo de funcionamento

```bash
# Para abrir o mundo
webots mundos/azorcar_labirinto.wbt
```

---

## 🔧 Exemplos de cenários simulados

- Labirinto com paredes e zonas coloridas no chão
- Tapete com linha preta e marcadores laterais (como no AzoresBot)
- Obstáculos com movimento programado
- Simulação de zonas de "pontos" ou "desafios" para gamificação

---

## 🎯 Objetivo pedagógico

- Ajudar os alunos a testar algoritmos de navegação sem medo de danificar o robô
- Incentivar o pensamento computacional e o raciocínio espacial
- Preparar demonstrações e experiências para eventos científicos

---

> 🧠 **Nota:** Começa com um robô simples (diferencial, 2 rodas) e depois melhora o URDF ou PROTO para representar melhor o AzorCAR real.
