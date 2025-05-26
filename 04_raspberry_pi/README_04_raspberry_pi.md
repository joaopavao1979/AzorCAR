
# 📁 04_raspberry_pi

## 📌 Descrição
Esta pasta contém scripts e módulos Python para correr diretamente no **Raspberry Pi 5 (8GB)** com Ubuntu. Estes scripts realizam tarefas mais avançadas de processamento, como visão computacional, controlo por gestos e análise de sensores conectados por USB, GPIO ou I2C.

O Raspberry Pi funciona como o "cérebro superior" do AzorCAR, responsável por decisões baseadas em IA ou análise visual, enquanto o Arduino pode ser usado como "sistema nervoso motor".

---

## 📂 Subpastas e ficheiros sugeridos

- `cam_openCV_tracking.py` — rastreamento de objetos por cor com OpenCV.
- `opencv_color_detect.py` — deteção e segmentação por cor (HSV).
- `mediapipe_gestos.py` — reconhecimento de gestos com MediaPipe.
- `sensor_integration.py` — leitura de sensores via GPIO.
- `notas_instalacao_opencv.md` — instruções para instalação de bibliotecas úteis no RPi (OpenCV, numpy, picamera2).

---

## 💻 Dependências recomendadas

No Raspberry Pi (com Ubuntu 22.04 ou 25.04), instala:

```bash
sudo apt update
sudo apt install python3-pip python3-opencv libopencv-dev
pip install mediapipe numpy
```

---

## 🎓 Integração com visão computacional

- Usa câmaras USB ou a porta CSI do Pi.
- Usa OpenCV para análise de imagem em tempo real (seguimento de linha, deteção de obstáculos, reconhecimento de padrões).
- Usa MediaPipe para reconhecimento de **rostos, gestos, mãos, corpo**.

---

## 🧠 Expansões futuras

- Comunicação com Arduino via porta serial (`/dev/ttyUSB0`)
- Controlo de motores diretamente via GPIO (em substituição ao Arduino)
- Deteção de QR codes, placas e formas geométricas
- Treinamento de modelos com TensorFlow Lite no Pi

---

## 🎯 Objetivo pedagógico

- Introduzir os alunos a visão computacional prática.
- Ensinar integração de hardware com código Python.
- Desenvolver sistemas de perceção artificial simples com baixo custo.
- Mostrar a diferença entre "reação" (Arduino) e "interpretação" (Raspberry Pi).

---

> 🧠 **Nota:** Todos os scripts devem ser escritos em Python 3, com comentários explicativos, para uso didático e experimental.
