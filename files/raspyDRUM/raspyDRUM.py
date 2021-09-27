import time

import RPi.GPIO as GPIO

import pygame
import pygame._sdl2 as sdl2
import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008



##########################################################################################################
#
##########################################################################################################

# Software SPI configuration:
CLK  = 11
MISO = 9
MOSI = 10
CS   = 8
mcp = Adafruit_MCP3008.MCP3008(clk=CLK, cs=CS, miso=MISO, mosi=MOSI)

# Hardware SPI configuration:
# SPI_PORT   = 0
# SPI_DEVICE = 0
# mcp = Adafruit_MCP3008.MCP3008(spi=SPI.SpiDev(SPI_PORT, SPI_DEVICE))


##########################################################################################################
#
##########################################################################################################
led = 17 # BCM 17 = GPIO 0
GPIO.setup(led, GPIO.OUT)
led_state = GPIO.LOW
##########################################################################################################
#
##########################################################################################################

pygame.mixer.init()

s1= pygame.mixer.Sound('audio/1-Cartoon-sound-effect.wav')
s2= pygame.mixer.Sound('audio/6-Cartoon-sound-effect.wav')
s3= pygame.mixer.Sound('audio/11-Cartoon-sound-effect.wav')
s4= pygame.mixer.Sound('audio/13-Cartoon-sound-effect.wav')
s5= pygame.mixer.Sound('audio/14-Cartoon-sound-effect.wav')
s6= pygame.mixer.Sound('audio/15-Cartoon-sound-effect.wav')
s7= pygame.mixer.Sound('audio/21-Cartoon-sound-effect.wav')
s8= pygame.mixer.Sound('audio/50-Cartoon-sound-effect.wav')

volumes=[1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0]

##########################################################################################################
#
##########################################################################################################

print('Reading MCP3008 values, press Ctrl-C to quit...')
# Print nice channel column headers.
print('| {0:>4} | {1:>4} | {2:>4} | {3:>4} | {4:>4} | {5:>4} | {6:>4} | {7:>4} |'.format(*range(8)))
print('-' * 57)


# Main program loop.
prev   = 0
actual = 0


##########################################################################################################
#
##########################################################################################################

while True:
    # Read all the ADC channel values in a list.
    values = [0]*8
    for i in range(8):
        # The read_adc function will get the value of the specified channel (0-7).
        values[i] = mcp.read_adc(i)
    # Print the ADC values.
    print('| {0:>4} | {1:>4} | {2:>4} | {3:>4} | {4:>4} | {5:>4} | {6:>4} | {7:>4} |'.format(*values))
    

    # Pause for half a second.
    time.sleep(0.5)
    actual = values[0]
    if (actual>150) and (prev <150):
        print("PLAY\n")
        pygame.mixer.Sound.play(s1)
        while pygame.mixer.get_busy() == True:
            time.sleep(0.1)

    prev = actual         

    GPIO.output(led, led_state)
    led_state = GPIO.HIGH - led_state