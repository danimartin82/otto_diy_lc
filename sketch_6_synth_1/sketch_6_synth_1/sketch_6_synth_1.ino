#include "Arduino.h"
#include "TimerOne.h"



uint16_t outputValue;
uint16_t time_on = 512;    // [0-1024] Default period -> 50% duty cycle
uint16_t period = 20000;   // [us]
uint16_t PWM_PIN=9;        // the output pin for the pwm


void update_frequency (uint16_t freq);
void update_duty(uint16_t duty);


void setup()
{  
   Serial.begin(9600);           // Iniciar puerto serie

   Timer1.initialize(period);    // initialize timer1 period [us]
   Timer1.pwm(PWM_PIN, time_on); // setup pwm on pin 9,

}
 
void loop() 
{
   if (Serial.available()>0)  // Si hay datos disponibles
   {
         outputValue = Serial.read();   // Leemos la opción
         outputValue -= '0';      // Restamos '0' para convertir a un número
         Serial.print("outputValue=");
         Serial.print(outputValue);
         Serial.print("\n");
         switch(outputValue)
        {
          case 0:
            update_frequency(50);
            break;
          case 1:
            update_frequency(500);
            break;
          case 2:
            update_frequency(5000);
            break;
          case 3:
            update_frequency(50000);
            break;
          case 4:
            update_duty(10);
            break;      
          case 5:
            update_duty(50);
            break;      
          case 6:
            update_duty(80);
            break;      
         case 7:
            Timer1.start();
            break;      
         case 8:
            Timer1.stop();
            break;      

                                   
        }

   }
}  

 void update_frequency (uint16_t freq)
 {
   period = 1000000/freq;

  Serial.print("freq=");
  Serial.print(freq);
  Serial.print(" Hz\n");       
  Timer1.pwm(PWM_PIN, time_on,period);
  return;
 }

 void update_duty(uint16_t duty)
 {
  time_on = map(duty,0,100,0,1024);
  Serial.print("duty=");
  Serial.print(duty);
  Serial.print(" [%]\n");
   
   Timer1.pwm(PWM_PIN, time_on,period);
  return;
 }
