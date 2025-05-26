
# 📁 05_ros2

## 📌 Descrição
Esta pasta contém os pacotes, nós, ficheiros de lançamento e modelos URDF usados na integração do robô **AzorCAR** com o **ROS 2 (Robot Operating System)**, versão **Humble**.

O ROS 2 permite transformar o AzorCAR num sistema modular e escalável, com tópicos, serviços e simulações conectadas entre sensores, atuadores e lógica de navegação.

---

## 📂 Estrutura sugerida

- `nodes/` — nós em Python (ex: controlo de motores, leitura de sensores, visão).
- `launch/` — ficheiros `.launch.py` para iniciar vários nós em conjunto.
- `urdf/` — modelos do robô (estrutura física) em formato URDF/XACRO.

---

## 📦 Exemplo de nós ROS 2

- `motor_controller_node.py` — lê /cmd_vel e envia PWM para motores (via Arduino ou Pi GPIO).
- `lidar_scan_node.py` — subscreve /scan e analisa distâncias para navegação.
- `vision_node.py` — usa OpenCV para gerar informação visual publicada no ROS.

---

## 🔄 Exemplo de fluxo com ROS 2

```plaintext
[vision_node]        --> /image_raw
[lidar_scan_node]    --> /scan
[slam_toolbox]       --> /map + /odom
[navigation2]        --> /cmd_vel
[motor_controller]   <-- /cmd_vel
```

---

## 🧰 Ferramentas úteis

- `rqt_graph` — visualizar tópicos e conexões
- `rviz2` — visualizar sensores e mapa
- `ros2 topic echo` — monitorizar dados em tempo real
- `colcon build` — compilar pacotes ROS 2

---

## 📦 Instalação do ROS 2 (Ubuntu 22.04 ou superior)

```bash
sudo apt update && sudo apt install ros-humble-desktop python3-colcon-common-extensions
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
```

---

## 🎯 Objetivo pedagógico

- Ensinar conceitos fundamentais de sistemas distribuídos (nós, tópicos, serviços)
- Permitir o controlo remoto e inteligência distribuída no robô
- Facilitar a expansão com SLAM, mapeamento e navegação autónoma

---

> ⚙️ **Dica:** Começa com simulações e tópicos simples antes de integrar com hardware físico.
