
//********************************************
// OSCILLATOR 1 variables
//********************************************
#define  NUM_FREQS 10 //len(freqs)
float freqs[NUM_FREQS]={0.05,0.1,0.2,0.3,0.5,1,2,3,4,5};
float ks[NUM_FREQS]={200,100,10,4,2,0.2,0.1,0.08,0.04,0.03};
float k;
float period_1;
float semiperiod_1;
float tau;
float aplied_offset;
float Osc1_amplitude;

float t = 0;
float value = 0;
float final_value = 0;
bool check = false;



//********************************************
// Local functions
//********************************************
float Osc1_interpolate_f(float freq);


//********************************************
// Osc1_setup
//********************************************
void Osc1_setup(void)
{
   Serial.println("OSC1 setup");
   
   Osc1_amplitude  = 100; //It will be the main aoutput, in % for Osc 2
   float Osc1_freq = 0.5; // Hz
   float offset    = 10;  // [%]
   
   Osc1_update_freq(Osc1_freq);
   Osc1_update_offset(offset);

   Serial.print("Osc1_freq = ");
   Serial.print(Osc1_freq);
   Serial.print(" Hz, ");
   Serial.print("Osc1_amplitude = ");
   Serial.print(Osc1_amplitude);
   Serial.print(" %, offset = ");
   Serial.print(offset);
   Serial.print(" %\n"); 
}


    
//********************************************
// Osc1_main_function
//********************************************
void Osc1_main_function(void)
{
 t= t + sample_period;
  if (t < semiperiod_1)
  {
    value = Osc1_amplitude* exp(-t/tau);
  }
  if (t >= semiperiod_1)
  {
    if (check == false)
    {
      final_value = Osc1_amplitude* exp(-t/tau) + aplied_offset;
      check = true;
    }
  }
  if (t > semiperiod_1)
  {
    value = final_value + Osc1_amplitude*(1- exp(-(t-semiperiod_1)/tau));
  }
  if (t >= period_1)
  { 
    t = 0;
    check = false;
  }    
 // Serial.println(value);
  analogWrite(OSC1_DEBUG_PIN,value);
}



//********************************************
// Osc1_update_freq
//********************************************
void Osc1_update_freq(float freq)
{
    period_1= 1 / freq; //s
    semiperiod_1 = period_1 / 2; //s
    k = Osc1_interpolate_f(freq);
    tau = freq * k;
    Serial.print("Osc1_update_freq( ");
    Serial.print(freq);
    Serial.print(" Hz ), k = ");
    Serial.print(k);
    Serial.print("\n");
}
//********************************************
// Osc1_update_offset
//********************************************
void Osc1_update_offset(float offset)
{
  aplied_offset= offset/100 * Osc1_amplitude;
}
  
//********************************************
// Osc1_interpolate_f
//********************************************
float Osc1_interpolate_f(float freq)
{
  float x, x0,x1,y0,y1;
  
  if (freq < freqs[0])
  {
    k = ks[0];
  }
  else if (freq > freqs[NUM_FREQS-1])
  {
      k = ks[NUM_FREQS-1];
  }
  else
  {
    for(uint16_t i = 0; i < NUM_FREQS; i++)
    {
      if (freq == freqs[i])
      {
        k = ks[i];
        break;
      }
      if (i < (NUM_FREQS-1))
      {

        if  ((freq > freqs[i]) && (freq < freqs[i+1]))
        {
          y0=ks[i];
          y1=ks[i+1];
          x0=freqs[i];
          x1=freqs[i+1];         
          x=freq;
          k = (y0*(x1-x)+y1*(x-x0))/(x1-x0);
        }
      }
    }
  }

  return k;
}
