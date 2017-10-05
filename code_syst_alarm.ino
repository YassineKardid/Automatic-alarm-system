#include <Ultrasonic.h>

#define Trig 12     // pin "Trig" du HC-SR04 connectée à pin 3 de l'Arduino
#define Echo 11     // pin "Echo" du HC-SR04 connectée à pin 2 de l'Arduino
#define led 13      // LEDs reliées aux pins de l'Arduino via une résistance

const int cmd_alarm=A0;
int etat=0;

int bipeur=10;      // l'un des broches du bipeur est connectée au pin 10 de l'Arduino
int i=0;

unsigned long cm;   // stockage de la distance de l'objet en cm
void blink(int ledPin, int bipeur);
Ultrasonic HCSR04(Trig,Echo);  // appel à la bibiothéque ultrasonic de l'arduino qui contient les fonctions nécessaire pour récuperer les valeurs détectées par le capteur ultrason

void setup()
{
  pinMode(cmd_alarm,INPUT);
  
  pinMode(led, OUTPUT);
  pinMode(bipeur, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
   etat=digitalRead(cmd_alarm);
  if(etat==0) 
  {
               //programme de désactivation 
        digitalWrite(led,LOW);
        digitalWrite(bipeur,LOW);     
   
  }

  else
  {  
                            //programme d'activation
                            
       cm = HCSR04.Ranging(CM);   // On récupère la distance dérectée par le capteur ultrason directement en cm
       if(cm <5)    {blink(led, bipeur);}              // un objet est détecté
  }

}
// La fonction ci-dessous fait clignoter less LEDs et lance le son dans le bipeur pendant 5 secondes.

void blink(int ledPin, int buzer)
{
  for(i=0;i<4;i++){
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzer, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    digitalWrite(buzer, LOW);
    delay(250);
  }
}
