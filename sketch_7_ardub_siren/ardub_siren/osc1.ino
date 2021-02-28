
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
float Osc1_output = 0;
float Osc1_semiperiod_value = 0;
bool  Osc1_semiperiod_check = false;



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
float Osc1_main_function(void)
{
 t= t + sample_period;
  if (t < semiperiod_1)
  {
    Osc1_output = Osc1_amplitude* exp(-t/tau);
  }
  if (t >= semiperiod_1)
  {
    if (Osc1_semiperiod_check == false)
    {
      Osc1_semiperiod_value = Osc1_amplitude* exp(-t/tau) + aplied_offset;
      Osc1_semiperiod_check = true;
    }
  }
  if (t > semiperiod_1)
  {
    Osc1_output = Osc1_semiperiod_value + Osc1_amplitude*(1- exp(-(t-semiperiod_1)/tau));
  }
  if (t >= period_1)
  { 
    t = 0;
    Osc1_semiperiod_check = false;
  }    
 // Serial.println(Osc1_output);
  analogWrite(OSC1_DEBUG_PIN,Osc1_output);

  return Osc1_output;
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
          k= fmap(freq, freqs[i], freqs[i+1], ks[i], ks[i+1]);
        }
      }
    }
  }

  return k;
}


//********************************************
// Osc1_update_inputs
//********************************************
void Osc1_update_inputs(uint16_t input_pot_freq, uint16_t input_pot_offset)
{
    // Map input input_pot_freq from [0-1023] to [0.1-5] Hz
    float new_freq = fmap(input_pot_freq, 0, 1023, 0.1, 5);
    
    // Map input osc1_value from [0-1023] to [0.9-1.1]
    float new_offset = fmap(input_pot_offset, 0, 1023,0, 50);

    Osc1_update_offset(new_offset);
    Osc1_update_freq(new_freq);

/*  Serial.print("osc1_value=");
  Serial.print(osc1_value);
  Serial.print(", factor=");
  Serial.print(factor);
  Serial.print(", new_freq=");
  Serial.print(new_freq);
  Serial.print(", new_duty=");
  Serial.print(new_duty);
  Serial.print("\n");
*/
  


}
