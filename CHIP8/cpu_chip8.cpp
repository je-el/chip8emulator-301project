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