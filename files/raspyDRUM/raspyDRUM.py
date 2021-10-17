import time
import threading
from datetime import datetime
import sys


import RPi.GPIO as GPIO

import pygame
import pygame._sdl2 as sdl2

import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008

from PIL import Image,ImageDraw,ImageFont


sys.path.insert(1, 'waveshare_OLED/')

import DEV_Config
import OLED_Driver


##########################################################################################################
#
# Global variables
#
##########################################################################################################
threshold_1=[20]*8
threshold_2=[150]*8
threshold_3=[150]*8

ADC_values = [0]*8
ADC_prev   = [0]*8

sounds=[0]*8
volumes=[1.0]*8
mcp  = 0

MODE = 'PLAYING'

##########################################################################################################
#
##########################################################################################################
def init_HW():
    global mcp
    # Software ADC MCP3008 SPI configuration:
    CLK  = 11
    MISO = 9
    MOSI = 10
    CS   = 8
    #mcp = Adafruit_MCP3008.MCP3008(clk=CLK, cs=CS, miso=MISO, mosi=MOSI)
    
    #configure LED
    led = 17 
    GPIO.setup(led, GPIO.OUT)
    led_state = GPIO.LOW



##########################################################################################################
#
##########################################################################################################
def init_SOUND():
    global sounds
    global volumes
    pygame.mixer.init()

    s1= pygame.mixer.Sound('audio/1-Cartoon-sound-effect.wav')
    s2= pygame.mixer.Sound('audio/6-Cartoon-sound-effect.wav')
    s3= pygame.mixer.Sound('audio/11-Cartoon-sound-effect.wav')
    s4= pygame.mixer.Sound('audio/13-Cartoon-sound-effect.wav')
    s5= pygame.mixer.Sound('audio/14-Cartoon-sound-effect.wav')
    s6= pygame.mixer.Sound('audio/15-Cartoon-sound-effect.wav')
    s7= pygame.mixer.Sound('audio/21-Cartoon-sound-effect.wav')
    s8= pygame.mixer.Sound('audio/50-Cartoon-sound-effect.wav')

    sounds=[s1,s2,s3,s4,s5,s6,s7,s8]



##########################################################################################################
#
##########################################################################################################
threshold_1=[20]*8
threshold_2=[150]*8
threshold_3=[150]*8

ADC_values = [0]*8
ADC_prev   = [0]*8
is_playing = [False]*8

##########################################################################################################
#
##########################################################################################################
def GUI_function(name):
    global MODE
    while(True):
        time.sleep(5)
        if MODE == "PLAYING":
            MODE = "MENU"
        else:
            MODE = "PLAYING"    

##########################################################################################################
#
##########################################################################################################
def OLED_function(name):
    OLED = OLED_Driver.OLED()

    print ("**********Init OLED**********")

    OLED_ScanDir = OLED_Driver.SCAN_DIR_DFT  #SCAN_DIR_DFT = D2U_L2R
    OLED.OLED_Init(OLED_ScanDir)

    #OLED.OLED_Clear()
    DEV_Config.Driver_Delay_ms(20)
    font_size = 20
    font = ImageFont.truetype("waveshare_OLED/arial.ttf", size=font_size)
   
    image = Image.open('waveshare_OLED/raspyDRUM_init.bmp')
    OLED.OLED_ShowImage(image,0,0)

    DEV_Config.Driver_Delay_ms(2000)

    image = Image.new("L", (OLED.OLED_Dis_Column, OLED.OLED_Dis_Page), 0)# grayscale (luminance)
    draw = ImageDraw.Draw(image)

    while (True):
        if MODE != 'PLAYING':
            draw.rectangle([(0,0),(127,127)],fill = "Black")

            now = datetime.now()

            current_time = now.strftime("%H:%M:%S")
            print("Current Time =", current_time)


            draw.line([(0,40),(127,40)], fill = "White",width = 1)
            draw.line([(127,40),(127,100)], fill = "White",width = 1)
            draw.line([(127,100),(0,100)], fill = "White",width = 1)
            draw.line([(0,100),(0,40)], fill = "White",width = 1)

            draw.text((25, 62), current_time, fill = "White", font = font)
    
            OLED.OLED_ShowImage(image,0,0)
        



##########################################################################################################
#
##########################################################################################################
def init_LOG():
    print('Reading ADC values')
    print('| {0:>4} | {1:>4} | {2:>4} | {3:>4} | {4:>4} | {5:>4} | {6:>4} | {7:>4} |'.format(*range(8)))
    print('-' * 57)

##########################################################################################################
#
##########################################################################################################
def play_sound(index):
    print(f"\nPLAY ch {index}\n")

    pygame.mixer.Sound.stop(sounds[index])
    pygame.mixer.Sound.set_volume(sounds[index], volumes[index])
    pygame.mixer.Sound.play(sounds[index])
            #while pygame.mixer.get_busy() == True:
            #    time.sleep(0.1)

##########################################################################################################
#
##########################################################################################################
def core_raspyDRUM():
    while True:
        # Read all the ADC channel values in a list.
        if MODE == 'PLAYING':

            for i in range(8):
                #ADC_values[i] = mcp.read_adc(i)
            
                if (ADC_values[i] > threshold_2[i]) and (ADC_prev[i] < threshold_3[i]):
                    play_sound(i)
                    is_playing[i] = True


                ADC_prev[i] = ADC_values[i]         
    
            # Print the ADC values.
            print('| {0:>4} | {1:>4} | {2:>4} | {3:>4} | {4:>4} | {5:>4} | {6:>4} | {7:>4} |'.format(*ADC_values))
            

            # Pause for half a second.
            time.sleep(0.5)
        
        #led control
        #GPIO.output(led, led_state)
        #led_state = GPIO.HIGH - led_state


##########################################################################################################
#
##########################################################################################################
if __name__ == "__main__":

    init_HW()
    init_SOUND()
    init_LOG()

    x = threading.Thread(target=OLED_function, args=(1,), daemon=True)
    x.start()

    x = threading.Thread(target=GUI_function, args=(1,), daemon=True)
    x.start()
    core_raspyDRUM()
    