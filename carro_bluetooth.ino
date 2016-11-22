#include <Servo.h>
Servo servo;

const int pinState = 13;
const int pinServo = 2;

const int anguloDerecha= 110;
const int anguloCentro = 80;
const int anguloIzquierda = 50;

const int pinAvanzarR = 6;
const int pinAvanzarL = 5;
const int pinRetrocederR = 7;
const int pinRetrocederL = 4;

int angulo = anguloCentro;
char comando;
char comandoAnterior = 'S';
boolean flag = 0;

void girarDerecha(){
  angulo = anguloDerecha;
  servo.write(angulo);
}
void girarCentro(){
  angulo = anguloCentro;
  servo.write(angulo);
}
void girarIzquierda(){
  angulo = anguloIzquierda;
  servo.write(angulo);
}

void avanzar(){
  digitalWrite(pinRetrocederR,LOW);
  digitalWrite(pinRetrocederL,LOW);
  delay(200);
  digitalWrite(pinAvanzarR,HIGH);
  digitalWrite(pinAvanzarL,HIGH);
}
void retroceder(){
  digitalWrite(pinAvanzarR,LOW);
  digitalWrite(pinAvanzarL,LOW);
  delay(200);
  digitalWrite(pinRetrocederR,HIGH);
  digitalWrite(pinRetrocederL,HIGH);
}

void detener(){
  digitalWrite(pinAvanzarR,LOW);
  digitalWrite(pinAvanzarL,LOW);
  digitalWrite(pinRetrocederR,LOW);
  digitalWrite(pinRetrocederL,LOW);
}

void iniciar(){
  switch (comando) {
    case 'R':
      girarDerecha();
      break;
    case 'L':
      girarIzquierda();
      break;
    case 'F':
      girarCentro();
      avanzar();
      break;
    case 'B':
      girarCentro();
      retroceder();
      break;
    case 'G':
      girarIzquierda();
      avanzar();
      break;
    case 'I':
      girarDerecha();
      avanzar();
      break;
    case 'H':
      girarIzquierda();
      retroceder();
      break;
    case 'J':
      girarDerecha();
      retroceder();
      break;
    case 'S':
      Serial.println("detener");
      detener();
      break;
    default: 
      Serial.println("otro");
      detener();
    break;
  }
}

void setup() {
  pinMode(pinState,OUTPUT);
  pinMode(pinAvanzarR,OUTPUT);
  pinMode(pinAvanzarL,OUTPUT);
  pinMode(pinRetrocederR,OUTPUT);
  pinMode(pinRetrocederL,OUTPUT);
  
  servo.attach(pinServo);
  Serial.begin(9600);

  digitalWrite(pinState,HIGH);
  girarCentro();
}

void loop() {
  while(Serial.available()){
    comando = (char) Serial.read();
    flag = 1;
  }
  if(!Serial.available() && flag){
    flag = 0; 
  }
  Serial.println(comando);
  if(comandoAnterior != comando){
    comandoAnterior=comando;
    iniciar();
    delay(400);
  }
}
