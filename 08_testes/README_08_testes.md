
# 📁 08_testes

## 📌 Descrição
Esta pasta contém todos os testes realizados com os diferentes módulos e componentes do robô **AzorCAR**. Serve para validar o funcionamento de sensores, motores, algoritmos e integração entre sistemas antes de consolidar o projeto final.

---

## 📂 Ficheiros sugeridos

- `calib_ultrassom.md` — Testes com sensor HC-SR04: tempo de resposta, alcance, precisão.
- `teste_motores_pwm.md` — Testes de velocidade e resposta dos motores DC via L298P.
- `validacao_lidar.md` — Testes com RPLIDAR A2: deteção de paredes e objetos.
- `teste_camera_usb.md` — Imagens capturadas e frames processados com OpenCV.
- `tempos_execucao.md` — Comparação entre leitura no Arduino vs Raspberry Pi.
- `log_erros.md` — Documentação de problemas encontrados e resoluções aplicadas.

---

## 📊 Objetivos dos testes

- Verificar que cada sensor funciona de forma isolada.
- Confirmar a resposta dos motores e o controlo de direção.
- Testar tempos de reação e latência dos comandos.
- Identificar limitações físicas e lógicas de hardware/software.

---

## 🧪 Metodologia recomendada

1. **Testar individualmente** cada componente.
2. Recolher e registar **dados objetivos** (tempo, distância, número de falhas).
3. Repetir testes com variações de código e ambiente (luz, cor, obstáculos).
4. Documentar resultados com **gráficos, tabelas ou imagens**.

---

## 🎯 Objetivo pedagógico

- Ensinar os alunos a trabalhar com método científico na robótica.
- Promover o pensamento crítico e a análise de dados.
- Desenvolver boas práticas de documentação e depuração de sistemas.

---

> 🧠 **Nota:** Sempre que possível, guardar os dados em `.csv` ou `.json` para futura análise em Python ou Excel.
