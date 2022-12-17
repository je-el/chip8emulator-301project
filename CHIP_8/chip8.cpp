//chip8.cpp
#include <iostream>
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
    
    unsigned char chip8_fontset[80] =
    { 
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    
    //load fontset
    for(int i=0; i <80;i++){
        memory[i] = chip8_fontset[i];
    }
    //reset timers

}

void chip8::emulatecycle()
{
    /* 
    memory[pc] == 0xA2
    memory[pc +1] == 0xF0
    */

   //fetch opcode
   opcode = memory[pc] << 8 | memory[pc+1];
   //decode opcode
   switch (opcode & 0xF000)
   {
        //opcodes
        case 0x0000:
            switch(opcode & 0x000F)
            {
                case 0x0000: // 0x00E0: Clears the screen
                    // This opcode clears the display by setting all pixels to zero.
                    break;

                case 0x000E: // 0x00EE: Returns from subroutine
                    // This opcode returns from a subroutine by setting the program counter to the address at the top of the stack, and decrementing the stack pointer.
                    break;

                default:
                    printf ("Unknown opcode [0x0000]: 0x%X\n", opcode);          
            }
            break;
        
        case 0x1000: // 0x1NNN: Jumps to the address NNN
            // This opcode sets the program counter to the address NNN.
            pc = opcode & 0x0FFF;
            break;

        case 0x2000: // 0x2NNN: Calls subroutine at NNN
            // This opcode calls a subroutine by setting the program counter to the address NNN, and pushing the current address onto the stack.
            stack[sp] = pc;
            ++sp;
            pc = opcode & 0x0FFF;
            break;

        case 0x3000: // 0x3XNN: Skips the next instruction if the value of VX equals NN
            // This opcode compares the value of register VX to the value NN, and if they are equal, it skips the next instruction by incrementing the program counter by 4. Otherwise, it increments the program counter by 2 to move to the next instruction.
            if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
            {    pc += 4; }
            else{
                pc += 2;
            }
            break;
        
        case 0x4000: // 0x4XNN: Skips the next instruction if the value of VX is not equal to NN
            if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
                pc += 4;
            else
                pc += 2;
            break;
        case 0x5000: //5xy0 skip next instruction if Vx = Vy
            //Interpreter compares the register Vx to register Vy and if they equal increments the program counter by 2
            if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
            {
                pc += 4; 
            } 
            else{
                pc += 2;
            }
            break;
        case 0x6000: // 0x6XNN: Sets VX to NN
            V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
            pc += 2;
            break;

        case 0x7000: // 0x7XNN: Adds NN to VX
            V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
            pc += 2;
            break;

        case 0x8000: // 0x8XY0 to 0x8XYF
            switch (opcode & 0x000F)
            {
                case 0x0000: // 0x8XY0: Sets VX to the value of VY
                    // This opcode sets the value of register VX to the value of register VY.
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;

                case 0x0001: // 0x8XY1: Sets VX to the value of VX or VY
                    // This opcode performs a bitwise OR operation on the values in registers VX and VY, and stores the result in VX.
                    V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;

                case 0x0002: // 0x8XY2: Sets VX to the value of VX and VY
                    // This opcode performs a bitwise AND operation on the values in registers VX and VY, and stores the result in VX.
                    V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;

                case 0x0003: // 0x8XY3: Sets VX to the value of VX xor VY
                    // This opcode performs a bitwise XOR operation on the values in registers VX and VY, and stores the result in VX.
                    V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;

                case 0x0004: // 0x8XY4: Adds VY to VX, sets VF to 1 if there's a carry, 0 otherwise
                    // This opcode adds the value of register VY to register VX, and stores the result in VX. If the result is greater than 255 (0xFF), the carry flag (VF) is set to 1, otherwise it is set to 0.
                    if(V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 8])){
                        V[0xF] = 1; //carry
                    } 
                    else {V[0xF] = 0;}
                    V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
                    pc += 2;          
                    break;

                case 0x0005: // 0x8XY5: VY is subtracted from VX, VF is set to 0 when there's a borrow, 1 otherwise
                    // This opcode subtracts the value of register VY from register VX, and stores the result in VX. If the value of VX is less than the value of VY, the borrow flag (VF) is set to 0, otherwise it is set to 1.
                    if(V[(opcode & 0x00F0) >> 4] > V[(opcode & 0x0F00) >> 8])
                    {
                        V[0xF] = 0; //borrow
                    } 
                    else {V[0xF] = 1;}
                    V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;

                case 0x0006: // 0x8XY6: Shifts VY right by one and copies the result to VX, VF is set to the least significant bit of VY before the shift
                    // This opcode shifts the value in register VY right by one bit, and stores the result in register VX. The carry flag (VF) is set to the least significant bit of VY before the shift.
                    V[0xF] = V[(opcode & 0x00F0) >> 4] & 0x1;
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] >> 1;
                    pc += 2;
                    break;

                case 0x0007: // 0x8XY7: Sets VX to VY minus VX, VF is set to 0 when there's a borrow, 1 otherwise
                    // This opcode sets the value of register VX to the value of register VY minus the value of register VX. If the value of VY is less than the value of VX, the borrow flag (VF) is set to 0, otherwise it is set to 1.
                    if(V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4]){
                        V[0xF] = 0; //borrow
                    } 
                    else {V[0xF] = 1;}
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
                    pc += 2;
                    break;
                
                case 0x0008: // 0x8XY8: Sets VX to VX xor VY
                    // This opcode performs a bitwise XOR operation on the values in registers VX and VY, and stores the result in VX.
                    V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;

                case 0x000E: // 0x8XYE: Shifts VY left by one and copies the result to VX, VF is set to the most significant bit of VY before the shift
                    // This opcode shifts the value in register VY left by one bit, and stores the result in register VX. The carry flag (VF) is set to the most significant bit of VY before the shift.
                    V[0xF] = V[(opcode & 0x00F0) >> 4] >> 7;
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] << 1;
                    pc += 2;
                    break;

            }
            break;

        case 0x9000: // 0x9XY0: Skips the next instruction if VX doesn't equal VY
            // This opcode compares the values in registers VX and VY, and if they are not equal, it skips the next instruction by incrementing the program counter by 4. Otherwise, it increments the program counter by 2 to move to the next instruction.
            if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
            {    pc += 4; }
            else{
                pc += 2;
            }
            break;

        case 0xA000: // 0xANNN: Sets I to the address NNN
            // This opcode sets the value of the index register (I) to the address NNN.
            I = opcode & 0x0FFF;
            pc +=2; //because each instruciton is 2 bytes long
            break;

        case 0xB000: // 0xBNNN: Jumps to the address NNN plus V0
            pc = (opcode & 0x0FFF) + V[0];
            break;

        case 0xC000: // 0xCXNN: Sets VX to a random number and NN
            V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
            pc += 2;
            break;

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
                        if(gfx[(x + xline + ((y + yline) * 64))] == 1){
                            //check if pixel on display is set to 1. register collision by setting VF register
                            V[0xF] = 1;
                        }                                 
                        gfx[x + xline + ((y + yline) * 64)] ^= 1; //set the pixel value by using XOR
                    }
                }
            }
            
            drawFlag = true; //change our gfx[] array and update the screen
            pc += 2; //uodate program counter to move to the next opcode
        }
        break;

        case 0xE000: // 0xEX9E and 0xEXA1
            switch (opcode & 0x00FF)
            {
                case 0x009E: // 0xEX9E: Skips the next instruction if the key stored in VX is pressed
                    if (key[V[(opcode & 0x0F00) >> 8]] != 0)
                    {
                        pc += 4;
                    }
                    else
                    {
                        pc += 2;
                    }
                    break;

                case 0x00A1: // 0xEXA1: Skips the next instruction if the key stored in VX isn't pressed
                    if (key[V[(opcode & 0x0F00) >> 8]] == 0)
                    {
                        pc += 4;
                    }
                    else
                    {
                        pc += 2;
                    }
                    break;

                default:
                    printf ("Unknown opcode [0xE000]: 0x%X\n", opcode);
                    break;
            }
            break;
        
        case 0xF000:
        switch(opcode & 0x00FF)
        {
            case 0x0007: // 0xFX07: Sets VX to the value of the delay timer
                V[(opcode & 0x0F00) >> 8] = delay_timer;
                pc += 2;
                break;

            case 0x000A: // 0xFX0A: A key press is awaited, and then stored in VX
                {
                    bool key_pressed = false;
                    for(int i = 0; i < 16; ++i)
                    {
                        if(key[i] != 0)
                        {
                            V[(opcode & 0x0F00) >> 8] = i;
                            key_pressed = true;
                        }
                    }
                    // If no key is pressed, return and try again.
                    if(!key_pressed)
                        return;
                    pc += 2;
                }
                break;
            case 0x0015: // 0xFX15: Sets the delay timer to VX
                delay_timer = V[(opcode & 0x0F00) >> 8];
                pc += 2;
                break;

            case 0x0018: // 0xFX18: Sets the sound timer to VX
                sound_timer = V[(opcode & 0x0F00) >> 8];
                pc += 2;
                break;
            case 0x001E: // 0xFX1E: Adds VX to I
                I += V[(opcode & 0x0F00) >> 8];
                pc += 2;
                break;

            case 0x0029: // 0xFX29: Sets I to the location of the sprite for the character in VX
                I = V[(opcode & 0x0F00) >> 8] * 0x5;
                pc += 2;
                break;

            case 0x0033: // 0xFX33: Stores the binary-coded decimal representation of VX at the address I
                // This opcode stores the hundreds digit, tens digit, and ones digit of the value in register VX at the addresses I, I+1, and I+2, respectively.
                memory[I] = V[(opcode & 0x0F00) >> 8] / 100;
                memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
                memory[I + 2] = (V[(opcode & 0x0F00) >> 8] % 100) % 10;
                pc += 2;
                break;

            case 0x0055: // 0xFX55: Stores V0 to VX in memory starting at address I
                for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
                    memory[I + i] = V[i];
                // On the original interpreter, when the operation is done, I = I + X + 1.
                I += ((opcode & 0x0F00) >> 8) + 1;
                pc += 2;
                break;
            
            default:
                printf ("Unknown opcode [0xF000]: 0x%X\n", opcode);
        }
        break;

   }
   

   //update timer
    if (delay_timer > 0)
    {
        --delay_timer;
    }
    if(sound_timer > 0)
    {
        if (sound_timer == 1)
        {
            printf("BEEP!\n");
        }    
        --sound_timer;
        
    }
   
}

