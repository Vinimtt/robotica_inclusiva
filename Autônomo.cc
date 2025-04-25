#include <Ultrasonic.h> //Adicionar biblioteca no arduino
#include <Servo.h>      

#define ECHO_PIN 3  
#define TRIGGER_PIN 8     
#define SERVO_PIN 9    
 
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN); 
Servo servo;
 
// Definindo as portas dos motores
#define IN1 7  
#define IN2 6  
#define IN3 5  
#define IN4 4  
 
void setup() {
  Serial.begin(9600);
  // Configuração dos motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  servo.attach(SERVO_PIN);
  servo.write(90);
 
  delay(1000);
}
 
void loop() {
  robo_frente();
  float dist_cm = distancia();
  Serial.print("Distância: ");
  Serial.print(dist_cm);
  Serial.println(" cm");
 
  if (dist_cm < 20) {
    decidir_direcao();
  }
  delay(100);
}
 
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
 
void decidir_direcao() {
  robo_parado();
  delay(500);
 
  // Escaneia a esquerda
  servo.write(150);
  delay(500);
  float dist_esq = distancia();
 
  // Escaneia a direita
  servo.write(30);
  delay(500);
  float dist_dir = distancia();
 
  // Retorna ao centro
  servo.write(90);
  delay(500);
 
  // Decide para onde virar
  if (dist_esq > dist_dir && dist_esq > 20) {
    Serial.println("Virando para a esquerda");
    robo_esquerda();
  } else if (dist_dir > 20) {
    Serial.println("Virando para a direita");
    robo_direita();
  } else {
    Serial.println("Nenhuma direção livre, dando ré");
    robo_re();
    delay(500);
  }
  delay(400);
  robo_parado();
  delay(500);
}
 
void robo_re() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
