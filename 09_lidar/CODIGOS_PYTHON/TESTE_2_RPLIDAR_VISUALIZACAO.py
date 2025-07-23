# Importa a biblioteca para comunicar com o RPLIDAR
from rplidar import RPLidar

# Importa bibliotecas para gráficos e cálculos
import matplotlib.pyplot as plt
import numpy as np

# ============================
# CONFIGURAÇÃO DA PORTA SERIAL
# ============================

# Define a porta COM usada pelo RPLIDAR (ver no Gestor de Dispositivos do Windows)
PORT = 'COM9'  # Altera para a tua porta real (ex: 'COM3', 'COM4', etc.)

# ============================
# INICIALIZAÇÃO DO LIDAR
# ============================

# Cria o objeto lidar, que vai comunicar com o sensor
lidar = RPLidar(PORT)

# Inicia o motor de rotação do sensor (obrigatório para A1, A2, A3)
lidar.start_motor()

# ============================
# CONFIGURAÇÃO DO GRÁFICO POLAR
# ============================

# Cria uma figura (janela) do Matplotlib
fig = plt.figure()

# Cria um gráfico "polar" (estilo radar)
ax = plt.subplot(111, polar=True)

# Cria o objeto que irá desenhar os pontos vermelhos no radar
scan_plot, = ax.plot([], [], 'ro', markersize=2)

# Ajustes visuais do gráfico
ax.set_rmax(4000)  # Raio máximo de visualização em milímetros (ex: 4 metros)
ax.grid(True)  # Mostra grelha no fundo
ax.set_theta_zero_location('N')  # Define 0° como "Norte"
ax.set_theta_direction(-1)  # Faz os ângulos crescerem no sentido horário

# ============================
# GERADOR DE VARREDURAS
# ============================

# Cria um gerador de varreduras completas do lidar
scan_generator = lidar.iter_scans()

# ============================
# FUNÇÃO PARA ATUALIZAR O RADAR
# ============================

def update():
    # Listas para guardar ângulos e distâncias de cada ponto
    angles = []
    distances = []

    try:
        # Lê a próxima varredura completa (uma volta de 360°)
        scan = next(scan_generator)

        # Para cada ponto detetado na varredura:
        for (_, angle, distance) in scan:
            if distance > 0:  # Filtra pontos válidos
                angles.append(np.radians(angle))      # Converte grau → radianos
                distances.append(distance)            # Guarda distância em mm

        # Atualiza os dados do gráfico
        scan_plot.set_data(angles, distances)

        # Atualiza o título com o número de pontos lidos
        ax.set_title(f"Leituras: {len(distances)} pontos", fontsize=10)

        return scan_plot,  # necessário para o matplotlib

    except Exception as e:
        # Mostra o erro completo (útil para depuração)
        print("⚠️ Erro durante leitura:", repr(e))
        return scan_plot,

# ============================
# LOOP PRINCIPAL DO PROGRAMA
# ============================

try:
    print("🔄 A visualizar... Pressiona Ctrl+C para sair.")
    
    # Executa infinitamente até o utilizador parar
    while True:
        update()             # Atualiza o gráfico com a próxima varredura
        plt.pause(0.001)     # Dá tempo para desenhar (quase tempo real)

# ============================
# ENCERRAMENTO SEGURO
# ============================

except KeyboardInterrupt:
    print("⛔ Interrompido pelo utilizador.")

finally:
    print("🛑 A desligar...")

    # Para o motor do LIDAR
    lidar.stop_motor()

    # Para a leitura de dados e termina a comunicação
    lidar.stop()
    lidar.disconnect()

    # Fecha a janela do gráfico
    plt.close()
