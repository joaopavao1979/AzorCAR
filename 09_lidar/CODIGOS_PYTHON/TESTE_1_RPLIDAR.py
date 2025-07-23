from rplidar import RPLidar

PORT = 'COM9'  # ou 'COM3' no Windows
lidar = RPLidar(PORT)

info = lidar.get_info()
print("Info:", info)

for i, scan in enumerate(lidar.iter_scans()):
    print(f'Scan {i}: {scan}')
    if i > 5:
        break

lidar.stop()
lidar.disconnect()
