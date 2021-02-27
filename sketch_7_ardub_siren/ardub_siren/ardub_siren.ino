#include "Arduino.h"
#include "TimerOne.h"
#include <math.h>

#define OSC1_DEBUG_PIN 3 // Debug pin with osc1
#define OSC2_PWM_PIN   9 // output pin for the pwm
#define INPUT_POT1_PIN 0 // input pot1
#define INPUT_POT2_PIN 1 // input pot2


//********************************************
// Main loop sleep
//********************************************
float sample_period = 0.1; // [s]



//********************************************
// INPUTS
//********************************************
uint16_t input1;
uint16_t input2;




//********************************************
// Global functions
//********************************************
void read_inputs(void);

void Osc2_setup(void);
void Osc2_update_frequency (uint16_t freq);
void Osc2_update_duty(uint16_t duty);

void Osc1_setup(void);
void Osc1_main_function(void);
void Osc1_update_freq(float freq);
void Osc1_update_offset(float offset);


//********************************************
// setup
//********************************************
void setup()
{  
   Serial.begin(9600);           // Iniciar puerto serie
   Serial.print("\nARDUB SIREN 1.0\n");
   Serial.print("*********************************\n\n");
   
   Osc1_setup();    
   Osc2_setup();            
  
}
//********************************************
// loop
//********************************************
void loop() 
{

   //read_inputs();

   Osc1_update_inputs();
   Osc1_main_function();

   Osc2_update_inputs();
   
   delay(sample_period*1000);
}



//********************************************
// read_inputs
//********************************************
void read_inputs(void)
{
   uint16_t aux= analogRead(INPUT_POT1_PIN);
   if(aux != input1)
   {
      input1=aux;
      Serial.print("INPUT_POT1_PIN = ");
      Serial.println(input1); 
   }
   aux = analogRead(INPUT_POT2_PIN);
   if(aux != input2)
   {
      input2=aux;
      Serial.print("INPUT_POT2_PIN = ");
      Serial.println(input2); 
   }

}
//********************************************
// Osc1_update_inputs
//********************************************
void Osc1_update_inputs(uint16_t freq, uint16_t offset)
{



}

//********************************************
// Osc2_update_inputs
//********************************************
void Osc2_update_inputs(float osc1_value)
{
  uint16_t factor =(uint16_t )osc1_value;

  Osc2_freq = osc1_value * Osc2_freq;
  Osc2_duty =  * Osc2_duty;


}
