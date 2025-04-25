#include <Ultrasonic.h>
#include <Servo.h>

// Definições dos pinos
#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4

#define ECHO_PIN 3
#define TRIGGER_PIN 8
#define SERVO_PIN 9

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
Servo servo;

char cha;
bool modo_autonomo = false;

void setup() {
  Serial.begin(9600);

  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

 
  servo.attach(SERVO_PIN);
  servo.write(90);
  delay(1000);
}

void loop() {
  if (Serial.available() > 0) {
    cha = Serial.read();
    delay(2);

    if (cha == 'A') {
      modo_autonomo = true;
    } else if (cha == 'M') {
      modo_autonomo = false;
    }
  }

  if (modo_autonomo) {
    robo_frente();
    float dist_cm = distancia();

    if (dist_cm < 20) {
      decidir_direcao();
    }
    delay(100);
  } else {
    // parte blut
    if (cha == 'F') {
      robo_frente();
    } else if (cha == 'B') {
      robo_re();
    } else if (cha == 'R') {
      robo_direita();
    } else if (cha == 'L') {
      robo_esquerda();
    } else if (cha == '0') {
      robo_parado();
    }
  }
}

// Funções auxiliares

float distancia() {
  return ultrasonic.read();
}

void robo_frente() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void robo_esquerda() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void robo_direita() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void robo_parado() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void robo_re() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void decidir_direcao() {
  robo_parado();
  delay(500);

  // Escaneia esquerda
  servo.write(150);
  delay(500);
  float dist_esq = distancia();

  // Escaneia direita
  servo.write(30);
  delay(500);
  float dist_dir = distancia();

  // Retorna ao centro
  servo.write(90);
  delay(500);

  // Escolhe direção
  if (dist_esq > dist_dir && dist_esq > 20) {
    robo_esquerda();
  } else if (dist_dir > 20) {
    robo_direita();
  } else {
    robo_re();
    delay(500);
  }
  delay(400);
  robo_parado();
  delay(500);
}
