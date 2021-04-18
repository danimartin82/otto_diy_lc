#include "TimerOne.h"
#include <math.h>

#define OSC1_DEBUG_PIN   3 // Debug pin with osc1
#define OSC2_PWM_PIN     9 // output pin for the pwm
#define INPUT_POT1_PIN   1 // input pot1 -> R6 Freq OSC1
#define INPUT_POT2_PIN   2 // input pot2 -> R3 Offset OSC1
#define INPUT_POT3_PIN   3 // input pot3 -> R9 Freq OSC2
#define INPUT_BUTTON_PIN 2 // input button
#define LED1_PIN         6 // Led 1
#define LED2_PIN         5 // Led 2


#define ARDUB_SIREN_VERSION 1

//********************************************
// Main loop sleep
//********************************************
float sample_period = 0.05; // [s]



//********************************************
// INPUTS
//********************************************
uint16_t input_pot1;
uint16_t input_pot2;
uint16_t input_pot3;
uint16_t input_button;



//********************************************
// Global functions
//********************************************
float fmap(float x, float x0, float x1, float y0, float y1);


void read_inputs(void);

void Osc2_setup(void);
void Osc2_update_frequency (uint16_t freq);
void Osc2_update_duty(uint16_t duty);
void Osc2_update_inputs(float osc1_value, uint16_t input_pot_freq, uint16_t input_button);


void Osc1_setup(void);
float Osc1_main_function(void);
void Osc1_update_inputs(uint16_t input_pot_freq, uint16_t input_pot_offset);
void Osc1_update_freq(float freq);
void Osc1_update_offset(float offset);


//********************************************
// setup
//********************************************
void setup()
{  
   Serial.begin(9600);           // Iniciar puerto serie
   Serial.print("\nARDUB SIREN v");
   Serial.println(ARDUB_SIREN_VERSION);
   Serial.print("*********************************\n\n");
   
   Osc1_setup();    
   Osc2_setup();            

   pinMode(INPUT_BUTTON_PIN, INPUT_PULLUP);
   
}
//********************************************
// loop
//********************************************
void loop() 
{

   read_inputs();

   Osc1_update_inputs(input_pot1,input_pot2);
   
   float Osc1_output = Osc1_main_function();

   Osc2_update_inputs(Osc1_output,input_pot3,input_button);

   leds_blink(Osc1_output);
   
   delay(sample_period*1000);
}



//********************************************
// read_inputs
//********************************************
void read_inputs(void)
{
   uint16_t aux= analogRead(INPUT_POT1_PIN);
   if(aux != input_pot1)
   {
      input_pot1=aux;
      Serial.print("INPUT_POT1_PIN = ");
      Serial.println(input_pot1); 
   }
   aux = analogRead(INPUT_POT2_PIN);
   if(aux != input_pot2)
   {
      input_pot2=aux;
    //  Serial.print("INPUT_POT2_PIN = ");
    //  Serial.println(input_pot2); 
   }
   aux = analogRead(INPUT_POT3_PIN);
   if(aux != input_pot3)
   {
      input_pot3=aux;
      //Serial.print("INPUT_POT3_PIN = ");
      //Serial.println(input_pot3); 
   }

    input_button = digitalRead(INPUT_BUTTON_PIN);
   // Serial.print("input_button = ");
   // Serial.println(input_button); 
}


//********************************************
// leds_blink
//********************************************
void leds_blink(float osc1_amplitude)
{
  uint8_t brightness1 = (uint8_t)osc1_amplitude;
  uint8_t brightness2 = 255 - brightness1;
  
  analogWrite(LED1_PIN,brightness1);
  analogWrite(LED2_PIN,brightness2);
}

//********************************************
// Map (float version) gets y corresponding to x.
//********************************************
float fmap(float x, float x0, float x1, float y0, float y1)
{
  return (y0*(x1-x)+y1*(x-x0))/(x1-x0);
}
