//chip8.h
class chip8{
    public:
        void initialize();//initialize registers and mem 
        void emulatecycle();
        /*
        {
            fetch decode
            decode opcode
            execute opcode
            update my timers
        }
        */



    private:
        unsigned short opcode; //our opcode in use
        unsigned char memory[4096]; //setting up our 4kB memory
        unsigned char V[16]; //our registers
        unsigned short I; //index
        unsigned short pc; //program counter these two can havw a value from 0x000-0xFFF

        /*
        0x000 - 0x1FF - CHIP8 Interpreter with font set
        0x050 - 0x0A0 - used for built in font set [4x5 pixel 0-F]
        0x200 - 0xFFF - Program ROM and work RAM
        */
        unsigned char gfx[64 * 32];
        
        //timers count at 60Hz when set above 0 they count down to 0 and sounds when it reaches it
        unsigned char delay_timer;
        unsigned char sound_timer;

        unsigned short stack[16];
        unsigned short sp;
        unsigned char key[16];



};

