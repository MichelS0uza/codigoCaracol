//Constantes Gerais
#define POT 250 //Potência dos Motores - Média 254 PWM = 100%
#define SLOW 100 //constante para andar devegar (PWM baixo)
#include <Servo.h>
#include <SoftwareSerial.h>



//Pinos Ponte H
#define IA1 5
#define IB1 6
#define IA2 10
#define IB2 11

const int BTState = 2; //Bluetooth (HC-06 JY-MCU) State pin on pin 2 of Arduino

//Variáveis Úteis
int i = 0;
int j = 0;
char state;
int state_rec;
int vSpeed=255;     // Default speed, from 0 to 255

int servo = 9;
  

//Movimento para Frente
void andarFrente() {
  analogWrite(IA1,POT);
  digitalWrite(IB1,LOW);
  analogWrite(IA2,POT);
  digitalWrite(IB2,LOW);
}

// Movimento para Tras
void andarTras() {
  digitalWrite(IA1,LOW );
  analogWrite(IB1,POT);  
  digitalWrite(IA2,LOW );
  analogWrite(IB2,POT); 
}

// Movimento para Direita
void andarDireita() {
  analogWrite(IA1,SLOW );
  digitalWrite(IB1,LOW); 
  analogWrite(IA2,POT);  
  digitalWrite(IB2,LOW); 
}

// Movimento para Esquerda
void andarEsquerda() {
  analogWrite( IA1,POT); 
  digitalWrite(IB1,LOW); 
  analogWrite(IA2,SLOW); 
  digitalWrite(IB2,LOW); 
}

// Gira para Direita
void girarDireita() {
  analogWrite(IA1,POT);
  digitalWrite(IB1,LOW);
  digitalWrite(IA2,LOW);
  analogWrite(IB2,POT); 
}

// Gira para Esquerda
void girarEsquerda() {
  digitalWrite(IA1,LOW ); 
  analogWrite(IB1,POT);  
  analogWrite(IA2,POT ); 
  digitalWrite(IB2,LOW); 
}

void parar() {
  digitalWrite(IA1,LOW);
  digitalWrite(IB1,LOW);
  digitalWrite(IA2,LOW);
  digitalWrite(IB2,LOW);
}

void setup() {

  //LED
  pinMode(13, OUTPUT);
 
 
  // MOTORES
  pinMode(IA1,OUTPUT);
  pinMode(IB1,OUTPUT);
  pinMode(IA2,OUTPUT);
  pinMode(IB2,OUTPUT);
  digitalWrite(IA1,LOW);
  digitalWrite(IB1,LOW);
  digitalWrite(IA2,LOW);
  digitalWrite(IB2,LOW);
 
  pinMode(BTState, INPUT);  
  Serial.begin(9600);

  //ServoMotor
  pinMode(servo,OUTPUT);
  
}

void loop() {

   //LED
  digitalWrite(13, HIGH);// turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second

  //ServoMotor
  
    
   // Para o carro quando a conexão com Bluetooth é perdida ou desconectada.
  if (digitalRead(BTState) == LOW) {
    state_rec = 'S';
  }

   // Salva os valores da variável 'state'
  if (Serial.available() > 0) {
    state_rec = Serial.read();
    state = state_rec;
    Serial.println(vSpeed);
    Serial.println(state);
  }
  
 // Se o estado recebido for igual a 'F', o carro se movimenta para frente.
  if (state == 'F') {
    analogWrite(IA1, vSpeed);
    analogWrite(IB1, 0);
    analogWrite(IA2, 0);
    analogWrite(IB2, vSpeed);
  }

  else if (state == 'B') { // Se o estado recebido for igual a 'B', o carro se movimenta para trás.
    analogWrite(IA1, 0);
    analogWrite(IB1, vSpeed);
    analogWrite(IA2, vSpeed);
    analogWrite(IB2, 0);
  }

  else if (state == 'L') {   // Se o estado recebido for igual a 'L', o carro se movimenta para esquerda.
    analogWrite(IA1, 0);
    analogWrite(IB1, vSpeed);
    analogWrite(IA2, 0);
    analogWrite(IB2, 250);
  }
  else if (state == 'R') {   // Se o estado recebido for igual a 'R', o carro se movimenta para direita.
    analogWrite(IA1, vSpeed);
    analogWrite(IB1, 0);
    analogWrite(IA2, 250);
    analogWrite(IB2, 0);
  }
  else if (state == 'S') {   // Se o estado recebido for igual a 'S', o carro permanece parado.
    analogWrite(IA1, 0);
    analogWrite(IA2, 0);
    analogWrite(IB1, 0);
    analogWrite(IB2, 0);
  }
  
}

