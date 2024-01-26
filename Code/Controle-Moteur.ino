#include<math.h>
//-- MOTEUR A --
int ENG=5; //Connecté à Arduino pin 5(sortie PWM)
int IN1=2; //Connecté à Arduino pin 2
int IN2=3; //Connecté à Arduino pin 3
//-- MOTEUR B --
int END=6; //Connecté à Arduino pin 6(Sortie PWM)
int IN3=12; //Connecté à Arduino pin 12
int IN4=13; //Connecté à Arduino pin 13

int PWMD;
int PWMG;

int x;
int y;

void setup() {
pinMode(END,OUTPUT); // Configurer
pinMode(ENG,OUTPUT); // les broches
pinMode(IN1,OUTPUT); // comme sortie
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
Serial.begin(9600);
}

void loop() {
  delay(100);
  move(255,255);
}

void forward() {

// Direction du Moteur A
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
// Direction du Moteur B
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
}

void moveBack() {

  // Direction du Moteur A
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
// Direction du Moteur B
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
}

void direction(int X, int Y){
  //Moitier haute du cadre donc avancer
    //Quart gauche du cadre donc tourner à gauche 
  if((X<=255)&& (Y<=255)){
    PWMD=255-Y;
    PWMG=255-Y-(255-X);
    if(PWMD<0) PWMD=0;
    if(PWMG<0) PWMG=0;
    forward();
  }
    //Quart droit du cadre donc tourner à droite
  if((X>255) && (Y<=255)){
    PWMD=255-Y-(X-256);
    PWMG=255-Y;
    if(PWMD<0) PWMD=0;
    if(PWMG<0) PWMG=0;
    forward();
  }
  //Moitier basse du cadre donc reculer
    //Quart gauche du cadre donc tourner à gauche 
  if((X<=255) && (Y>255)){
    PWMD=Y-256;
    PWMG=Y-256-(255-X);
    if(PWMD<0) PWMD=0;
    if(PWMG<0) PWMG=0;
    moveBack();
  }
    //Quart droit du cadre donc tourner à droite
  if((X>255) && (Y>255)){
    PWMD=Y-256-(X-256);
    PWMG=Y-256;
    if(PWMD<0) PWMD=0;
    if(PWMG<0) PWMG=0;
    moveBack();
  }
  Serial.print("PWMD");
  Serial.println(PWMD);
  Serial.print("PWMG");
  Serial.println(PWMG);
  
}

void move(int X, int Y){
  direction(X,Y);
  analogWrite(END,PWMD);
  analogWrite(ENG,PWMG);
}