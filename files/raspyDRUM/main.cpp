#include <iostream>
#include <errno.h>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>



using namespace std;

// channel is the wiringPi name for the chip select (or chip enable) pin.
// Set this to 0 or 1, depending on how it's connected.
static const int CHANNEL = 1;
#define BASE 100
#define SPI_CHAN 0

int main() {


    int fd, result;
    unsigned char buffer[100];

    cout << "Initializing" << endl ;



    wiringPiSetup ();

    pinMode (0, OUTPUT);


   // Configure the interface.
   // CHANNEL insicates chip select,
   // 500000 indicates bus speed.
   //fd = wiringPiSPISetup(CHANNEL, 500000);
   fd =  mcp3004Setup (BASE, SPI_CHAN) ; // 3004 and 3008 are the same 4/8 channels


   cout << "Init result: " << fd << endl;

   // Send command
   //buffer[0] = 0x76;
   //wiringPiSPIDataRW(CHANNEL, buffer, 1);


    uint16_t chan = 0;

    for (;;)
    {
        float   x = analogRead (BASE + chan);
        printf("Channel %d: %f\n", chan, x);     
        digitalWrite (0, HIGH);
        delay (500);
        digitalWrite (0,  LOW);
        delay (500);
       
    }
   std::cout << "Goodbye World\n";
    return 0;
}




