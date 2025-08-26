// Projeto: Robô Básico com Desvio de Obstáculos
// Autor: João Paulo Nunes Andrade
// Linguagem: C++ (Arduino)

// --- Bibliotecas ---
#include <Servo.h>

// --- Definições dos pinos ---
#define trigPin 9     // Pino TRIG do sensor ultrassônico
#define echoPin 10    // Pino ECHO do sensor ultrassônico
#define motorLeft 5   // Motor esquerdo
#define motorRight 6  // Motor direito

Servo servoLeft;
Servo servoRight;

// --- Função para medir distância ---
long readUltrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Distância em cm
  return distance;
}

// --- Configuração inicial ---
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servoLeft.attach(motorLeft);
  servoRight.attach(motorRight);

  Serial.begin(9600);
}

// --- Loop principal ---
void loop() {
  long distance = readUltrasonic();
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 20) {
    // Caminho livre → anda para frente
    servoLeft.write(180);  
    servoRight.write(0);   
  } else {
    // Obstáculo → parar e virar
    servoLeft.write(0);    
    servoRight.write(0);   
    delay(500);

    servoLeft.write(0);    
    servoRight.write(180); 
    delay(700); // tempo de curva
  }
}

//🔧 How it works:

//The ultrasonic sensor measures the distance to obstacles.

//If the distance is greater than 20 cm, the robot moves forward.

//If it is less than or equal to 20 cm, the robot stops and turns to the right.

//📦 Required components:

//1 Arduino Uno (or compatible).

//1 HC-SR04 Ultrasonic Sensor.

//2 Servos (or DC motor + driver).

//Jumpers + Breadboard + Battery.
