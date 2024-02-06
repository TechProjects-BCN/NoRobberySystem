
//*****************Servo motor + Ultrasonic + Switch***********************//

#include <Servo.h> // Llibreria servo


//Pins
const int trigPin = 9;
const int echoPin = 10;
const int buttonPin = 3; 


//No entenc
Servo servo1;

//Variables
long duration;
int distance;
int angle_inicial = 10;
int angle_final = 120;
int buttonState = 0;

void setup() {  // S'executa només quan sinicia el programa

  pinMode(trigPin, OUTPUT); // TrigPin en Ouput (Pin 9)
  pinMode(echoPin, INPUT); // EchoPin en Input (Pin 10)
  pinMode(buttonPin, OUTPUT); // buttonPin en Output(Pin 3)



  servo1.attach(8);  // Servo al Pin 8
  servo1.write(angle_inicial);  // Servo al angle de tancar la comporta


  Serial.begin(9600); // Iniciar Serial (Consola)

}
void loop() {  // S'executa sempre en bucle (Loop principal)

  buttonState = digitalRead(buttonPin); // Llegeix estat switch


  if (buttonState == HIGH) { // Si el switch està encés entra al if

    // Pin 9 a Low
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Pin 9 a High durant 10 ms
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Llegeix el Pin 10, en mc
    duration = pulseIn(echoPin, HIGH);
    // Calcula la distancia rebuda del Pin 10
    distance = duration * 0.034 / 2;
    // Escriu la distancia a la consola
    Serial.print("Distance: ");
    Serial.println(distance);
    delay(500);

    if (distance < 50){ // Si la distancia és menor a 50 entra al if
      Serial.println("Yes");
      servo1.write(angle_final); // Obra comporta
      delay(8000); // Temps de delay abans de tancar la comporta (temps en ms)
      servo1.write(angle_inicial); // Tanca la comporta
      delay(1000); // Temps abans de tornar a començar el codi (temps en ms)
    }
      
  }
    delay(50);
} 
