#include <Servo.h>
#include<string.h>
#include<SoftwareSerial.h>
#define RX 50 // Broche 50 en tant que RX, à raccorder sur TX du HC-05
#define TX 51 // Broche 51 en tant que TX, à raccorder sur RX du HC-05
SoftwareSerial BlueT(RX,TX);
char caract;// Caractère relevé lors de la communication bluetooth

int power=255; //Puissance des moteurs de traction

//-- MOTEUR A (Avant Droit) --
int ENG=7; //Connecté à Arduino pin 7(sortie PWM)
int IN1=6; //Connecté à Arduino pin 6
int IN2=5; //Connecté à Arduino pin 5

//-- MOTEUR B (Avant Gauche) --
int END=2; //Connecté à Arduino pin 2(Sortie PWM)
int IN3=4; //Connecté à Arduino pin 4
int IN4=3; //Connecté à Arduino pin 3

const int enableMotor1 = 13;
const int motor1Input1 = 12;
const int motor1Input2 = 11;
const int enableMotor2 = 8;
const int motor2Input1 = 10;
const int motor2Input2 = 9;
const int servoPin1 = 42; // Broche pour le premier servo-moteur
const int servoPin2 = 40; // Broche pour le deuxième servo-moteur
const int servoPin3 = 41;

Servo myServo1; // Crée une instance de la classe Servo pour le premier servo-moteur
Servo myServo2; // Crée une instance de la classe Servo pour le deuxième servo-moteur
Servo myServo3;

// Fonction pour convertir un angle de -90 à 90 degrés en une valeur de 0 à 180 degrés
int mapAngle(int angle) {
  return map(angle, -90, 90, 0, 180);
}

void setup() {
  // Configuration des broches en sortie pour les moteurs
  pinMode(enableMotor1, OUTPUT);
  pinMode(motor1Input1, OUTPUT);
  pinMode(motor1Input2, OUTPUT);
  pinMode(enableMotor2, OUTPUT);
  pinMode(motor2Input1, OUTPUT);
  pinMode(motor2Input2, OUTPUT);

  pinMode(END,OUTPUT); // Configurer
  pinMode(ENG,OUTPUT); // les broches
  pinMode(IN1,OUTPUT); // comme sortie
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  //moteurs à l'arrêt
  digitalWrite(END,LOW);
  digitalWrite(ENG,LOW);

  digitalWrite(END,LOW);
  digitalWrite(ENG,LOW);
  
  analogWrite(END,0); 
  analogWrite(ENG,0);

  // Configuration des broches pour les servo-moteurs
  myServo1.attach(servoPin1);
  myServo2.attach(servoPin2);
  myServo3.attach(servoPin3);

  // Démarre la communication série
  Serial.begin(9600);
  //Début de la communication bluetooth
  BlueT.begin(9600);
  Serial.println("Bonjour -Pret pour les commandes AT");
}

void loop() {
  
  while (BlueT.available()) {
    caract = BlueT.read();
    Serial.println(caract);
    switch(caract){
      case 'R':
        fire();
        break;
      case 'T':
        rotateServoClockwise(myServo3, 40);
        break;
      case 'G':
        rotateServoClockwise(myServo3,-40);;
        break;
      case 'Z':
        forward();
        break;
      case 'S':
        moveBack();
        break;
      case 'D':
        right();
        break;
      case 'Q':
        left();
        break;
      case '/':
        analogWrite(END,0); //la voiture s'arrête lorsque l'on appuie sur aucun bouton
        analogWrite(ENG,0);
        break;
    }
  }
}

//Fonction relatif au canon
void MotorsOn() {
  // Activation du moteur 1
  analogWrite(enableMotor1, 255);
  digitalWrite(motor1Input1, LOW);
  digitalWrite(motor1Input2, HIGH);

  // Activation du moteur 2
  analogWrite(enableMotor2, 255);
  digitalWrite(motor2Input1, LOW);
  digitalWrite(motor2Input2, HIGH);
}

void rotateServoClockwise(Servo servo, int angle) {
  servo.write(mapAngle(angle)); 
}

void MotorsOff(){
  digitalWrite(enableMotor1, LOW);
  digitalWrite(enableMotor2, LOW);
}

void fire(){
  MotorsOn();
  delay(800);

  rotateServoClockwise(myServo2, 30);
  delay(200);
  rotateServoClockwise(myServo1, 40);
  delay(200);

  rotateServoClockwise(myServo1, -40); // Deuxième servo-moteur
  delay(200);
  rotateServoClockwise(myServo2, -30);
  delay(200);
  MotorsOff();
}

// Code relatif au mouvement
void forward(){
  //Serial.println(caract);

   // Direction du Moteur A (Gauche)
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  // Direction du Moteur B (Droite)
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  analogWrite(END,power); //vitesse droit
  analogWrite(ENG,power); //vitesse gauche
}

void moveBack(){
  // Direction du Moteur A (Gauche)
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  // Direction du Moteur B (Droite)
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  analogWrite(END,power); //vitesse droit
  analogWrite(ENG,power); //vitesse gauche
}

void left(){
  // Direction du Moteur A (Gauche)
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  // Direction du Moteur B (Droite)
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  //analogWrite(END,power); //vitesse droit
  analogWrite(ENG,power); //vitesse gauche
}

void right(){
  // Direction du Moteur A (Gauche)
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  // Direction du Moteur B (Droite)
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  analogWrite(END,power); //vitesse droit
  //analogWrite(ENG,power); //vitesse gauche
}
