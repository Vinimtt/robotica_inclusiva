// Definição dos pinos de saída para os dois motores
#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4
 
void setup() {
Serial.begin(9600); // Inicia a porta serial com taxa de 9600 bps
 
// Declarando os motores como Saídas
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
}
 
char cha;
 
void loop() {
  if (Serial.available() > 0) {
  cha = Serial.read();
  delay(2);
  }
 
// Movimenta para frente
  if (cha == 'F') {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
// Movimenta para trás
  else if (cha == 'B') {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
// Movimenta para direita
  else if (cha == 'R') {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } 
// Movimenta para esquerda
  else if (cha == 'L') {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
// Sem movimento
  else if (cha == '0') {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}
