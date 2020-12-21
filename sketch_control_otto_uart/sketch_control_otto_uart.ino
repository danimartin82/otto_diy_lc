#include <Otto9.h>
#include <US.h>


Otto9 Otto;

int distance = 0;
int incomingByte = 0;

#define PIN_YL 2 // left leg, servo[0]
#define PIN_YR 3 // right leg, servo[1]
#define PIN_RL 4 // left foot, servo[2]
#define PIN_RR 5 // right foot, servo[3]
#define PIN_Trigger 8 // ultrasound
#define PIN_Echo 9 // ultrasound
#define PIN_Buzzer  13 //buzzer
#define PIN_Trigger 8 // ultrasound
#define PIN_Echo 9 // ultrasound

void setup() {
  Serial.begin(9600);
  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true, A6, PIN_Buzzer, PIN_Trigger, PIN_Echo);
}

void loop() {
  Otto.home();


  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();  
    switch(incomingByte)
    {
      case 'a':
      {
        Otto.walk(4,1000, FORWARD);
        break;
      }
      case 's':
      {
        Otto.walk(4,1000, BACKWARD);
        break;
      }
      case 'd':
      {
        Otto.turn(4,2000, LEFT);
        break;
      }  
      case 'f':
      {
        Otto.turn(4,2000, RIGHT);
        break;
      }
      case 'g':
      {
        Otto.bend(1,1400,LEFT);
        break;
      }
        case 'h':
      {
        Otto.shakeLeg(1,2000, RIGHT);
        break;
      }

      case 'j':
      {
        distance=Otto.getDistance();
        Serial.println(distance);
        break;
      }
      case 'k':
      {
        Otto.sing(S_happy);
        delay(500);
        Otto.sing(S_sad);
        delay(500);
        Otto.sing(S_mode1);
        delay(500);
        Otto.sing(S_fart2);
      
        break;
      }


      
      default:
        break;
  }
    
  delay(500);
  }

}
