#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<Time.h>

#define GND2  D1; // define pin 2 or any other digital pin as Ground 2


char auth[] = "YOUR_AUTH";
char ssid[]="YOUR_SSID";
char password[] = "YOUR_PASSWORD";

int sensor_pin = A0; // Soil Sensor input at Analog PIN A0
int output_value ;
int In1 = D4;
int buzzerPin = D8;                
int pirPin = D2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;
int waittime = 1;

unsigned long previousMillis = 0;
const long interval = 600000;
const long minit = 60000;

void setup() {
  //wifi
  Serial.begin(9600);
  Blynk.begin(auth, ssid, password);

  // put your setup code here, to run once:
  pinMode(In1,OUTPUT);
  Serial.begin(9600);

  Serial.println("Reading From the Sensor ...");

  delay(2000);
  pinMode(buzzerPin, OUTPUT);      // initalize LED as an output
  //digitalWrite(buzzerPin, LOW);
  digitalWrite(pirPin, LOW);
  pinMode(pirPin, INPUT);    // initialize sensor as an input
  Serial.begin(9600);        // initialize serial

}

void loop() {
 Blynk.run();
  motion();
  moisture();
}

void moisture(){

output_value= analogRead(sensor_pin);
   //Serial.print("Raw : ");
   //Serial.print(output_value);
   //Serial.print("\n");

   output_value = map(output_value,1023,400,0 ,100);

   Serial.print("Moisture : ");
   Serial.print(output_value);
   Serial.println("%");
   Blynk.virtualWrite(V5, output_value);
   Blynk.virtualWrite(V4, In1);

  unsigned long currentMillis = millis();

     if(output_value <=30) {
      Blynk.notify("I need water..");
   }
  if(output_value<=30){
      digitalWrite(In1,LOW); //turn on
      //delay(10000);
     }
     else{
      digitalWrite(In1,HIGH); //turn off
      //delay(60000); 
     }
   delay(3000);
}

void motion(){
   val = digitalRead(pirPin);
  if (val == HIGH) {           // check if the sensor is HIGH
     digitalWrite(buzzerPin, HIGH);   // turn buzzer ON
     //tone(buzzerPin, 1200, 500);
     //delay(1000);
    if (state == LOW) {
      Serial.println("Motion detected!");
      Blynk.notify("Movement detected");
     // delay(waittime*600); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else{

     digitalWrite(buzzerPin,LOW); // turn buzzer OFF
     //noTone(buzzerPin);
      if (state == HIGH){
        Serial.println("Motion stopped!");    
        state = LOW;// update variable state to LOW
    }
  }  
}
