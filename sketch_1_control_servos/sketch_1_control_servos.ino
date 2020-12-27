#include <Servo.h>
 
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;  

const int LED=11;

bool move = false;
 
void setup() {
   servo1.attach(6);
   servo2.attach(2);
   servo3.attach(3);
   servo4.attach(4);
   servo5.attach(5);

  pinMode(LED,OUTPUT);

     Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  Serial.println("Move servos? (1-> move, 0-> stop)");      
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
      servo1.write(0);
      servo2.write(0);
      servo3.write(0);
      servo4.write(0);
      servo5.write(0);
       
      delay(500);
     
      servo1.write(180);
      servo2.write(180);
      servo3.write(180);
      servo4.write(180);
      servo5.write(180);
     
      delay(500);
    }
}
