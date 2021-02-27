//********************************************
// OSCILLATOR 2 (PWM)
//********************************************

uint16_t Osc2_freq =70;    // [Hz]
uint16_t Osc2_duty =50;    // [%]
uint16_t Osc2_time_on=512;
uint16_t Osc2_period=20000;


//********************************************
// Osc2_setup
//********************************************
void Osc2_setup(void)
{
  Serial.println("OSC2 setup");
  Timer1.initialize(Osc2_period);    // initialize timer1 period [us]
  Timer1.pwm(OSC2_PWM_PIN, Osc2_time_on); // setup pwm on pin 9,[0-1024] Default period -> 50% duty cycle

  Osc2_freq = 70; // Hz
  Osc2_duty = 50; // %
  Osc2_update_frequency(Osc2_freq);
  
  Osc2_update_duty(Osc2_duty);
 
  Serial.print("Osc2_freq = ");
  Serial.print(Osc2_freq);
  Serial.print(" Hz, ");
  Serial.print("Osc2_duty = ");
  Serial.print(Osc2_duty);
  Serial.print(" %\n"); 
  
}

//********************************************
// Osc2_update_frequency
//********************************************
 void Osc2_update_frequency (uint16_t freq)
 {
   Osc2_period = 1000000/freq;
  
    Timer1.pwm(OSC2_PWM_PIN, Osc2_time_on, Osc2_period);
  
   Serial.print("Osc2_update_frequency=");
   Serial.print(freq);
   Serial.print(" Hz\n");     
  
  return;
 }

//********************************************
// Osc2_update_duty
//********************************************
 void Osc2_update_duty(uint16_t duty)
 {
  Osc2_time_on = map(duty,0,100,0,1024);
  Serial.print("duty=");
  Serial.print(duty);
  Serial.print(" [%]\n");
   
  Timer1.pwm(OSC2_PWM_PIN, Osc2_time_on, Osc2_period);
  return;
 }