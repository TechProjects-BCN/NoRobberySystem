/*****************************************************
 *****************************************************
 *****     BALANZA ELECTRÓNICA CON HX711         *****
 *****************************************************/
//llibrerias
#include "HX711.h"
#include <Wire.h>
#include <EEPROM.h>

//Variables globals
byte DT= A0;
byte CLK= A1;
byte modo = 7;
byte tara = 6;
int peso_conocido[4] = {500,1000,3000,5000};
long escala;
  

//Crear el objecte balança
HX711 balanza;

//Definir bomba aigua
const int pin = 9;


//Funció de calibrar
void calibration(){
  
  int i = 0,cal=1;
  long adc_lecture;
  

  balanza.read();
  balanza.set_scale(); //L'escala per defecte és 1
  balanza.tare(20);  //El pes actual es considerat Tara.


  //Inici del procès de calibració
  while(cal == 1){
    
    
      //Llegeix el valor del HX711
      adc_lecture = balanza.get_value(100);

      //Calcula la escala amb el valor llegit dividit per el pes conegut
      escala = adc_lecture / peso_conocido[i];

      //Guarda l'escala en la EEPROM
      EEPROM.put( 0, escala );
      delay(100);
      cal = 0; //Trencar bucle 
    }
    
  }


void setup() {
  Serial.begin(9600);
  Serial.println("1");
  //Configura la balança
  balanza.begin(DT, CLK);
  
  //Configura els botons
  pinMode(modo, INPUT);
  pinMode(tara, INPUT);

  //Llegeix el valor de l'escala en la EEPROM
  EEPROM.get( 0, escala );

  //Preguntar pel procès de calibrar
  //if(digitalRead(modo) && digitalRead(tara))
    //calibration();

  balanza.set_scale(escala); // Establim l'escala
  balanza.tare(20);  //El peso actual es considerat Tara.

  pinMode(pin, OUTPUT);  //definir pin com sortida 

}

void loop() {
  float peso;
  Serial.println("Si");
  //Medeix el pin de la balança
  peso = balanza.get_units(10);
  Serial.println(peso);
  
  if (peso != balanza.get_units(10)); // Canvi de pes
    
    
    //digitalWrite(pin, HIGH);   // posa el Pin en HIGH
    //delay(10000);              // esperar 10 segons * s'ha de canviar el temps
    //digitalWrite(pin, LOW);    // pona el Pin en LOW
    //delay(10000);              // esperar 10 segons * s'ha de canviar el temps
    
}