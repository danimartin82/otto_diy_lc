#include <Otto9.h>
#include <US.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"



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
#define PIN_RX_MP3 10 // Rx mp3 module
#define PIN_TX_MP3 11 // Tx mp3 module

Otto9 Otto;
DFRobotDFPlayerMini myDFPlayer;
SoftwareSerial mySoftwareSerial(PIN_RX_MP3, PIN_TX_MP3);

void setup() {
  Serial.begin(9600);
  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true, A6, PIN_Buzzer, PIN_Trigger, PIN_Echo);

  mySoftwareSerial.begin(9600);
  
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(20);  //Set volume value. From 0 to 30

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
        Otto.turn(4,1000, LEFT);
        break;
      }
      case 's':
      {
        Otto.turn(4,1000, RIGHT);
        break;
      }
      case 'd':
      {
        Otto.jump(4,1000);
        break;
      }  
      case 'f':
      {
        Otto.jitter(4,1000, 20);
        break;
      }
      case 'g':
      {
        Otto.moonwalker(4,1000,20,LEFT);
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
        Otto.sing(S_fart1);
        delay(500);
        Otto.sing(S_fart2);
        delay(500);
        Otto.sing(S_fart3);
        delay(500);
        Otto.sing(S_sad);
        delay(500);
        Otto.sing(S_confused);
        
        
        break;
      }

      case 'q':
      {
        myDFPlayer.play(1);
        break;
      }
      
      case 'w':
      {
        myDFPlayer.play(2);
        break;
      }      default:
        break;
  }
    
  delay(500);
  }

}
