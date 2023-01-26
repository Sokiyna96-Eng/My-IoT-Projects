#include <Arduino.h>

int buzzerPin = 4;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(buzzerPin,OUTPUT);
  pinMode(16,HIGH);  // Blue led Pin Connected To D0 Pin   
  pinMode(5,HIGH);  // Green Led Pin Connected To D1 Pin   
  pinMode(4,HIGH);  // Red Led Connected To D2 Pin    

}


void loop() {
  // // read the input on analog pin 0:
   int sensorValue = analogRead(A0);
  // // Convert the analog reading to Lux
   float lux = 122.86* (sensorValue * (3.3 / 1023.0)) - 79.195;
  // // print out the value you read:
   Serial.print("Lux Values:");
   Serial.println(lux);
   delay(1000);

   if(lux < 10){
       tone(buzzerPin, 440); 
       delay(5000);
       noTone(buzzerPin);
       delay(5000);
   }else if (lux >= 10 && lux < 50 ){
    digitalWrite(16,HIGH);  
    digitalWrite(5,LOW);  
    digitalWrite(4,LOW);  
    delay(1000);  
   }else if(lux >= 50 && lux < 200){
    digitalWrite(16,LOW);  
    digitalWrite(5,HIGH);  
    digitalWrite(4,LOW);  
    delay(1000);  
   }else if( lux > 300){
    digitalWrite(16,LOW);  
    digitalWrite(5,LOW);  
    digitalWrite(4,HIGH);  
    delay(3000);  
   }

      
   while (Serial.available() > 0){
     int input = Serial.read();
     if(input == 'b' || input == 'B'){
     
          tone(buzzerPin, 440); 
          delay(5000);
          noTone(buzzerPin);
          delay(5000);
      }
   }
}

