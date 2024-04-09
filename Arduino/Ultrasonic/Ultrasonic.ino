
//***************** Servo motor + Ultrasonic + Switch ***********************//

#include <Servo.h> // Llibreria servo
#include <Adafruit_NeoPixel.h>  //Llibreria LED's


//Pins
const int trigPin = 9;
const int echoPin = 10;
const int buttonPin = 3; 
const int bomba = 5; 
const int buttonPin2 = 4;


#define Altaveu_pin 13 

//No entenc
Servo servo1;
 
//Variables
long duration;
int distance;
int angl_i = 0;
int angl_f = 135;
int buttonState = 0;
int button2State = 0;
int stop = 90;
int leds = 2; //Pin donde está conectada la tira de leds
int numleds = 16; //Número de leds conectados


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numleds, leds, NEO_GRB + NEO_KHZ800);

void setup() {  // S'executa només quan sinicia el programa

  Serial.begin(9600); // Iniciar Serial (Consola)

  pinMode(trigPin, OUTPUT); // TrigPin en Ouput (Pin 9)
  pinMode(echoPin, INPUT); // EchoPin en Input (Pin 10)
  pinMode(buttonPin, OUTPUT); // buttonPin en Output(Pin 3)
  pinMode(buttonPin2, OUTPUT);

  pinMode(bomba, OUTPUT);

  pinMode(Altaveu_pin, OUTPUT);

  servo1.attach(8);  // Servo al Pin 8
  servo1.write(angl_i);  // Servo al angle de tancar la comporta
  Serial.println("si");

  pixels.begin(); // Inici leds
  pixels.show(); // Inicialitza tots els pixels apagats

}

void activarBomba(){
  digitalWrite(bomba,HIGH);
  delay(500);
}

void desactivarAlarma(){
  digitalWrite(bomba,LOW);
  delay(500);
}

void activarAlarma(){
  for (int i=0; i < 5; i++){
    tone(Altaveu_pin, 1000);
    delay(100);
    noTone(Altaveu_pin);
    delay(100); 
  }
}

void activarLeds(){
  colorFull(pixels.Color(255,0,0));
  //pixels.setPixelColor(4,pixels.Color(0,0,255));
  pixels.show();
}

void desactivarLeds(){
  colorFull(pixels.Color(0,0,0));
  //pixels.setPixelColor(4,pixels.Color(0,0,255));
  pixels.show();
}


void colorFull(uint32_t color){
  for(int i = 0; i < pixels.numPixels(); i++){
    pixels.setPixelColor(i, color);
  }
  pixels.show();
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

      delay(10000);
      activarLeds();
      activarAlarma();
      delay(500);

      Serial.println("Yes");
      servo1.write(angl_f); // Obra comporta
      delay(6000); // Temps de delay abans de tancar la comporta (temps en ms)
      //servo1.write(stop);
      //delay(3000);
      servo1.write(angl_i); // Tanca la comporta
      //delay(800); // Temps abans de tornar a començar el codi (temps en ms)
      //servo1.write(stop);
      delay(10000);
    }
    
    desactivarAlarma();
    desactivarLeds();
  
  }
  if (button2State == HIGH){
    
    activarBomba();
    delay(500);
  }


  delay(50);
} 
