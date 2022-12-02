#ifndef CPU_CHIP8_H_
#define CPU_CHIP8_H_
//#include <string>
#include <unordered_map>
#include <thread>
#include <functional>
#include <atomic>

class cpuchip8 {
    public:
        public Initialize(const std::string& rom);
        void runcycle();
    private:
        //our instructions
        void BUILDinstructionset();

        using Instruction = std::function<void(void)>;
        std::unordered_map < uint16_t, Instruction>> instructions_;

        uint16_t current_opcode_;

        uint8_t memory_[4096]; // 4K
        uint8_t v_register_[16];

        uint16_t index_register_;
        // Points to the next instruction in memory_ to execute.
        uint16_t program_counter_;

        // 60Hz timers.
        uint8_t delay_timer_;
        uint8_t sound_timer_;

        uint16_t stack_[16];
        // Points to the next empty spot in stack_.
        uint16_t stack_pointer_;

        // 0 when not pressed.
        uint8_t keypad_state_[16];

        //when I hook up input we'll find the way to feed 
        // the 16 digital input keys which are either on or off
        //into the class between cycles
        //all chip8 instructions are 2 bytes long

        //mem map will be made in the Initialize function checkout cpu_chip8.cpp
        
};

#endif