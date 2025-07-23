#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(10);       // Liga o servo ao pino digital D10
  servo.write(90);        // Vai diretamente para 90 graus (posição central)
}

void loop() {
  // Mantém o servo fixo a 90 graus
}
