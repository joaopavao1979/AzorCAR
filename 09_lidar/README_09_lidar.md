
# 📁 09_lidar

## 📌 Descrição
Esta pasta contém scripts, dados e testes relacionados com o uso de sensores LIDAR no projeto **AzorCAR**, nomeadamente o **RPLIDAR A2**. Estes sensores permitem obter uma visão 2D do ambiente, essencial para mapeamento, navegação e evasão de obstáculos.

---

## 📂 Subpastas e ficheiros sugeridos

- `visualizacao_python/radar_live.py` — visualização em tempo real dos dados do LIDAR com Matplotlib.
- `dados_csv/` — ficheiros `.csv` com dados brutos recolhidos durante testes.
- `integracao_ros.md` — instruções para usar o RPLIDAR no ROS 2 (via rplidar_ros).
- `testes_lidar_angulo.md` — testes para medir ângulo de deteção e alcance máximo.

---

## 💻 Requisitos para uso com Python

Instalar via pip:

```bash
pip install rplidar matplotlib numpy
```

Ligar o RPLIDAR via USB e verificar a porta COM (ex: `COM3` no Windows, `/dev/ttyUSB0` no Linux).

---

## 🌐 Uso com ROS 2 (Humble)

```bash
sudo apt install ros-humble-rplidar-ros
ros2 launch rplidar_ros rplidar.launch.py
```

---

## 🎯 Objetivos dos testes

- Verificar varrimento em 360º e precisão das leituras.
- Criar visualizações simples para ajudar na compreensão do sensor.
- Recolher dados para mapeamento e navegação autónoma.
- Comparar desempenho com outros sensores de distância.

---

## 🎓 Objetivo pedagógico

- Introduzir os alunos à leitura espacial em 2D.
- Visualizar de forma concreta o conceito de varrimento a laser.
- Estimular experimentação com sensores avançados e representação gráfica.

---

> 🧪 **Nota:** Para iniciar testes com código Python, começar com `radar_live.py` e visualizar a deteção em tempo real.
