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
        case 0x2000:
            stack[sp] = pc;
            ++sp;
            pc = opcode & 0x0FFF;
            break;
        case 0x0004:
            break;

        case 0xA000: //sets I to the address NNN
            I = opcode & 0x0FFF;
            pc +=2; //because each instruciton is 2 byts long
            break;
        //more opcodes add them here

        default:
            printf("Unknown opcode: 0x%X\n",opcode);
   }
   //execute opcode???

   //update timer
    if (delay_timer > 0)
        --delay_timer;

    if(sound_timer > 0){
        if (sound_timer == 1)
            printf("BEEP!\n");
        --sound_timer;
        
    }
   
}