#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h> //lets use OpenGL instead
#include "chip8.h"

chip8 Chip8;

int main(int argc, char **argv)
{
    //render system and input callback
   /* setupGraphics();
    setupInput(); */ //when setting up graphics

    Chip8.initialize();

    Chip8.loadGame("IBMlogo");

    //emulation loop
    for(;;){
        //emulate one cycle
        Chip8.emulatecycle();

        //if draw flag is set then it will update the screen
        if(Chip8.drawFlag) drawGraphics();

        //storing the keys that are pressed current state so when pressed and when released
        Chip8.setKeys();

    }

    return 0;
}