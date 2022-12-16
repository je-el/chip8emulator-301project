#include "chip8.h"

void chip8::initialize(){
    pc = 0x200; //program counter starts at 0x200
    opcode = 0; //reset current opcode
    I = 0; // reset index register
    sp = 0; // reset stack pointer

    //clear display
    //clear stack
    //clear registers V0-VF
    //clear mem
    
    //load fontset
    for(i=0; i <80;i++)
        memory[i] = chip8_fontset[i];
    
    //reset timers

}

void chip8::emulatecycle(){
    /* memory[pc] == 0xA2
    memory[pc +1] == 0xF0
    */

   //fetch opcode
   opcode = memory[pc] << 8 | memory[pc+1];
   //decode opcode
   switch (opcode & 0xF000){
        //opcodes
        /*
        0x2NNN
        0x8XY4
        */
    
        case 0x0000:
            switch(opcode & 0x000F)
            {
                case 0x0000: // 0x00E0: Clears the screen        
                    // Execute opcode
                    break;
 
                case 0x000E: // 0x00EE: Returns from subroutine          
                    // Execute opcode
                    break;
 
                default:
                    printf ("Unknown opcode [0x0000]: 0x%X\n", opcode);          
            }
            break;
        case 0x2000:
            stack[sp] = pc;
            ++sp;
            pc = opcode & 0x0FFF;
            break;

        case 0x0004::       
            if(V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 8])){
                V[0xF] = 1; //carry
            } 
            else {V[0xF] = 0;}
             
            V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
            pc += 2;          
            break;

        case 0xA000: //sets I to the address NNN
            I = opcode & 0x0FFF;
            pc +=2; //because each instruciton is 2 bytes long
            break;
        
        case 0x0033: //0xFX33 stores the binary-coded decimal representation of VX at the address I
        //I + 1 and I + 2
            memory[I]     = V[(opcode & 0x0F00) >> 8] / 100;
            memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
            memory[I + 2] = (V[(opcode & 0x0F00) >> 8] % 100) % 10;
            pc += 2;
            break;


        //more opcodes add them here

        //the graphics opcode 0xDXYN
        //Draws a sprite at (VX, VY) width = 8 px and hieght = N pixels
        case 0xD000:		   
        {
            unsigned short x = V[(opcode & 0x0F00) >> 8];//Fetch the position and height of the sprite
            unsigned short y = V[(opcode & 0x00F0) >> 4];// ^^
            unsigned short height = opcode & 0x000F; //pixel value
            unsigned short pixel;  //^^
            
            V[0xF] = 0; //register VF
            for (int yline = 0; yline < height; yline++) //loop over each row
            {
                pixel = memory[I + yline]; //fetch the pixel value from the memory starting at location I
                for(int xline = 0; xline < 8; xline++) //loop over 8 bits of one row
                {
                    if((pixel & (0x80 >> xline)) != 0) //check if the current evaluated pixel is set to 1. 0x80 >> xline scan through the byte one bit at a time
                    {
                        if(gfx[(x + xline + ((y + yline) * 64))] == 1) //check if pixel on display is set to 1. register collision by setting VF register
                            V[0xF] = 1;                                 
                            gfx[x + xline + ((y + yline) * 64)] ^= 1; //set the pixel value by using XOR
                    }
                }
            }
            
            drawFlag = true; //change our gfx[] array and update the screen
            pc += 2; //uodate program counter to move to the next opcode
        }
        break;

        //
        default:
            printf("Unknown opcode: 0x%X\n",opcode);
   }



   //update timer
    if (delay_timer > 0)
        --delay_timer;

    if(sound_timer > 0){
        if (sound_timer == 1)
            printf("BEEP!\n");
        --sound_timer;
        
    }
   
}