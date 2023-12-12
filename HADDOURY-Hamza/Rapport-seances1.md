### • Matériel recue
2 moteurs pour tirer les projectiles  
2 servomoteurs pour controler l'orientation du canon  

### • Montage Arduino
Attribution des broches appropriées de l'Arduino pour le contrôle des moteurs, avec un pont en H (L298N) pour gérer la polarité et la vitesse.  


<img src="https://github.com/hamza-haddoury/TheDestroyer/assets/66840168/30ab21a8-991e-42f9-b6de-9e2c2081768c" alt="Mon Image" width="302,4" height="403,2">


### • Code de Contrôle des Moteurs
Développement d'un code Arduino permettant un contrôle de la vitesse (puissance de tir).

```
int enableMotor1 = 9;   

int motor1Input1 = 8;    
int motor1Input2 = 7;    

int enableMotor2 = 10;    
int motor2Input1 = 11; 
int motor2Input2 = 12; 

void setup() {
  // Configuration des broches en sortie
  pinMode(enableMotor1, OUTPUT);
  pinMode(motor1Input1, OUTPUT);
  pinMode(motor1Input2, OUTPUT);

  pinMode(enableMotor2, OUTPUT);
  pinMode(motor2Input1, OUTPUT);
  pinMode(motor2Input2, OUTPUT);
}

void loop() {
  analogWrite(enableMotor1, 200); 
  digitalWrite(motor1Input1, HIGH);
  digitalWrite(motor1Input2, LOW);

  analogWrite(enableMotor2, 150); // Valeur entre 0 (arrêt) et 255 (vitesse maximale)
  digitalWrite(motor2Input1, HIGH);
  digitalWrite(motor2Input2, LOW);

  delay(5000);

  // Arrêt des moteurs
  digitalWrite(motor1Input1, LOW);
  digitalWrite(motor1Input2, LOW);
  digitalWrite(motor2Input1, LOW);
  digitalWrite(motor2Input2, LOW);

  delay(2000);
}

```
