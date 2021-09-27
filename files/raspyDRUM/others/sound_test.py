import pygame
import pygame._sdl2 as sdl2


pygame.mixer.init()


pygame.mixer.music.load("080_01A.wav")
pygame.mixer.music.play()
while pygame.mixer.music.get_busy() == True:
    continue
