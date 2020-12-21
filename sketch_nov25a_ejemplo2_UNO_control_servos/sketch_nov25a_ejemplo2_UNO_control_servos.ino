#include <Servo.h>


Servo servo1;

const int LED=11;

bool move = false;
 
void setup() {
   servo1.attach(5);
  pinMode(LED,OUTPUT);
     Serial.begin(115200);
  while (!Serial) {

  }
  Serial.println("Move servos? (set angle in degrees");      
}
 
void loop() {
 
 int incomingData= Serial.read();
    if (incomingData=='1')
    {
      move=true;
      digitalWrite(LED,HIGH);
    }
    if (incomingData=='0')
    {
      move=false;
      digitalWrite(LED,LOW);
    }


    if(move==true)
    {
      servo1.write(45);
      delay(1000);
      servo1.write(0);
      delay(1000);
    }
}
