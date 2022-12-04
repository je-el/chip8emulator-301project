//headers from program
#include "cpu_chip8.h"

//inbuilt headers
#include <thread>
#include <atomic>
#include <fstream>
#include <iostream>
#include <chrono>
#include <iterator>
#include <vector>
#include <cmath>
#include <string>

//defines

#define NEXT program_counter_ += 2 //becasue each opcode is 2 bytes
#define SKIP program_counter_ += 4

// once Initialize is set up then we'll be able to execute a user program
cpuchip8::Initialize(const std::string& rom) {

    current_opcode_ = 0;
    std::memset(memory_, 0, 4096); //void * memset(void *__b, int __c, size_t __len)
    std::memset(v_registers_, 0, 16);
    index_register_ = 0;
    //typically chip8 memory begins at 0x200 so our pc is there
    program_counter_ = 0x200;
    delay_timer_ = 0;
    sound_timer_ = 0;
    std::memset(stack_, 0, 16); 
    stack_pointer_ = 0;
    std::memset(keypad_state_, 0, 16);


    uint8_t chip8_font[80] =
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

    //we'll put the font set into 0x050 - 0x0A0
    //void * memcpy(void *__dst, const void *__src, size_t __n)
    std::memcpy(memory_ + 0x50, chip8_font, 80);

    //now lets add the ROM into the program 
    //this way it'll actually be able tp run the games

     std::ifstream input(filename, std::ios::in | std::ios::binary);
     std::vector<uint8_t> bytes(
        //vector(std::__1::vector<uint8_t> &&__x)
        (std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>())
     );

     if (bytes.size() > kMAXROMSize) {
        throw std::runtime_error("File size is too big.");
     } else if (bytes.size() <= 0) {
        throw std::runtime_error("Um... No file / empty file.");
     }
     
     //void * memcpy(void *__dst, const void *__src, size_t __n)
     std::memcpy(memory_ + 0x200, bytes.data(), bytes.size());
    //memory allocation hehehe
     BUILDinstructionset();


}

void cpuchip8::runcycle() {
    //getting that opcode
    current_opcode_ = memory_[program_counter_] << 8 | memory_[program_counter_ + 1];
    auto instr = instructions_.find(current_opcode_);

    if (instr != instructions_.end()) {
        instr->second();
    } else { throw std::runtime_error("Couldn't find that instruction for opcode " + std::to_string(current_opcode_));
    }
    //now to update sound and delay timerds
}
/* with runcycle we don't alter the prorgam counter
as this is done function by function
that will get done by a specific `instruction`*/

/*
chip8 uses big-endian arch so the most significant part of the word
comes first followed by th least significant part
this is  reversed in x86 based systems
*/

void cpuchip8::BUILDinstructionset(){
    instructions.clear();
    instructions.reserve(0xFFFF);

    instructions_[0x00E0] = [this]() { frame_.SetAll(0); NEXT;};
    instructions_[0x00EE] = [this]() { program_counter_ = stack_[stack_pointer_] + 2; //ret
    };

    for (int opcode = 0x1000; opcode < 0xFFFF; opcode++) {
        uint16_t nnn = opcode & 0x0FFF;
        uint8_t kk = opcode & 0x00FF;
        uint8_t x = (opcode & 0x0F00) >> 8;
        uint8_t y = (opcode & 0x00F0) >> 4;
        uint8_t n = opcode & 0x000F;
        
        //each of these iinstrucitons encode parameters that we decode when needed
        //the tutorial I am following chose to define Gen[INSTRCUTION_NAME] 
        //rather than using std::bind to generate the std::functions
        //it returns the funcitons as lambdas and binds all the data
        if ((opcode & 0xF000) == 0x1000){
            instructions_[opcode] = GenJP(nnn);
        } else if ((opcode & 0xF000) == 0x2000) { 
            instructions_[opcode] = GenCALL(nnn);
        } else if ((opcode & 0xF000) == 0x3000) {
            instructions_[opcode] = GenSE(x, kk);
        } else if ((opcode & 0xF000) == 0x4000)
        {
            instructions_[opcode] = GenSNE(x, kk);
        } else if ((opcode & 0xF00F) == 0x5000)
        {
            instructions_[opcode] = GenSEREG(x, y);
        } else if ((opcode & 0xF000) == 0x6000)
        {
            instructions_[opcode] = GenLDIMM(x, kk);
        } else if ((opcode & 0xF000) == 0x7000)
        {
            instructions_[opcode] = GenADDIMM(x, kk);
        } else if ((opcode & 0xF00F) == 0x8000)
        {
            instructions_[opcode] = GenLDV(x, y);
        } else if ((opcode & 0xF00F) == 0x8001)
        {
            instructions_[opcode] = GenOR(x, y);
        } else if ((opcode & 0xF00F) == 0x8002)
        {
            instructions_[opcode] = GenAND(x, y);
        } else if ((opcode & 0xF00F) == 0x8003)
        {
            instructions_[opcode] = GenXOR(x, y);
        } else if ((opcode & 0xF00F) == 0x8004)
        {
            instructions_[opcode] = GenADD(x, y);
        } else if ((opcode & 0xF00F) == 0x8005)
        {
            instructions_[opcode] = GenSUB(x, y);
        } else if ((opcode & 0xF00F) == 0x8006)
        {
            instructions_[opcode] = GenSHR(x);
        } else if ((opcode & 0xF00F) == 0x8007)
        {
            instructions_[opcode] = GenSUBN(x, y);
        } else if ((opcode & 0xF00F) == 0x800E)
        {
            instructions_[opcode] = GenSHL(x);
        } else if ((opcode & 0xF00F) == 0x9000)
        {
            instructions_[opcode] = GenSNEREG(x, y);
        } else if ((opcode & 0xF000) == 0xA000)
        {
            instructions_[opcode] = GenLDI(nnn);
        } else if ((opcode & 0xF000) == 0xB000)
        {
            instructions_[opcode] = GenJPREG(nnn);
        } else if ((opcode & 0xF000) == 0xC000)
        {
            instructions_[opcode] = GenRND(x, kk);
        } else if ((opcode & 0xF000) == 0xD000)
        {
            instructions_[opcode] = GenDRAW(x, y, n);
        } else if ((opcode & 0xF0FF) == 0xE09E)
        {
            instructions_[opcode] = GenSKEY(x);
        } else if ((opcode & 0xF0FF) == 0xE0A1)
        {
            instructions_[opcode] = GenSNKEY(x);
        } else if ((opcode & 0xF0FF) == 0xF007)
        {
            instructions_[opcode] = GenRDELAY(x);
        } else if ((opcode & 0xF0FF) == 0xF00A)
        {
            instructions_[opcode] = GenWAITKEY(x);
        } else if ((opcode & 0xF0FF) == 0xF015)
        {
            instructions_[opcode] = GenWDELAY(x);
        } else if ((opcode & 0xF0FF) == 0xF018)
        {
            instructions_[opcode] = GenWSOUND(x);
        } else if ((opcode & 0xF0FF) == 0xF01E)
        {
            instructions_[opcode] = GenADDI(x);
        } else if ((opcode & 0xF0FF) == 0xF029)
        {
            instructions_[opcode] = GenLDSPRITE(x);
        } else if ((opcode & 0xF0FF) == 0xF033)
        {
            instructions_[opcode] = GenSTBCD(x);
        } else if ((opcode & 0xF0FF) == 0xF055)
        {
            instructions_[opcode] = GenSTREG(x);
        } else if ((opcode & 0xF0FF) == 0xF065)
        {
            instructions_[opcode] = GenLDREG(x);
        }
    }
}

//when we JP to an addr we set the counter = to the addr so the next cycle executes from that point
cpuchip8::Instruction cpuchip8::GenJP(uint16_t addr) {
    return [this, addr]() { program_counter_ = addr;};

}

cpuchip8::Instruction cpuchip8::GenCALL(uint16_t addr){
    return [this, addr](){
        stack_[stack_pointer_++] = program_counter_;
        program_counter_ = addr;
    };
} //with call it is the same as JP but we have to return 
// so we storethe counter to the stack

cpuchip8::Instruction cpuchip8::GenADD(uint8_t reg_x, uint8_t reg_y){
    return [this, reg_x, reg_y](){
        uint16_t res = v_registers_[reg_x] += v_registers_[reg_y];
        v_registers_[0xF] = res > 0xFF; //set carry
        v_registers_[reg_x] = res;
        NEXT;
    };
}
cpuchip8::Instruction cpuchip8::GenSUB(uint8_t reg_x, uint8_t reg_y){
    return [this, reg_x, reg_y](){
        uint16_t res = v_registers_[reg_x] > v_registers_[reg_y]; // set not borrow
        v_registers_[reg_x] = res;
        NEXT;
    }; 
} //we need to keep track of the overflow so we check for it and if it
// is detected then we set VF


/* VV my sprite loading function VV*/
cpuchip8::Instruction cpuchip8::GenLDSSPRITE(uint8_t reg){
    return [this, reg](){
        uint8_t digit = v_registers_[reg];
        index_register_ = 0x50 + ( 5* digit);
        NEXT;
    };
}
// the fonset is stored at 0x50 and eaxh character is 5 bytes wide
// we set I to ox50 + (5 * digit)
//the program will use it to figure out where a digit is inside the fontset

cpuchip8::Instruction cpuchip8::GenSTREG(uint8_t reg){
    return [this, reg]() {
        for (uint8_t v = 0; v <= reg; v++){
            memory_[index_register_ + v] = v_registers_[v];
        }
        NEXT;
    };
}
cpuchip8::Instruction cpuchip8::GenLDREG(uint8_t reg){
    return [this, reg]() {
        for (uint8_t v = 0; v <= reg; v++){
            v_registers_[v] = memory_[index_register_ + v];
        }
        NEXT;
    };
}
//the user provides the register they wanna use
//when they load either register V0, V1, or V2 the values stored 
//in MEM[I] they would pass in V2 after setting up I
