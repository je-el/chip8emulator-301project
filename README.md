# chip8emulator-301project
## About
My CHIP8 interpretor /virtual machine  
  
For Main Project Code look at [CHIP_8](https://github.com/je-el/chip8emulator-301project/tree/main/CHIP_8)  
  
### Requirements
- SDL2 for graphics
- C++
- Understanding of CHIP-8's opcodes, and structure.


## References/Resources:
#### Videos: 
- NaN  
#### Absolutely Necessary Reads:
- [Lazy Foo' Productions "Setting up SDL 2 on Mac OS X Monterey" Because how else will I run my graphics on my swanky Apple Silicon Mac](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/mac/index.php)
    - Great read, in depth tutorial in how to set up SDL 2 and get to actually work compared to all the other tutorials that jsut say download it and be gone.
    - Another SDL wiki as a guide: [SDL Wiki](https://wiki.libsdl.org/SDL2/SDL_PixelFormatEnum)  
- [River Gillis Tutorial for creating a CHIP-8 Interpreter and virtual machine to run it](https://riv.dev/emulating-a-computer-part-1/)
    - The Tutorial itself is a bit abstract as it only explains how to create a more fashionable chip-8 emulator compared to a simpler explanation of how chip-8 is actually implemented.  
    -  My best recommendation would be to look at the wikipedia guide to CHIP-8 and implementing th ecode as simply as possible. but overall it is an absolutely perfect article that guided me through understanding how to implement chip-8 using c++
- [Assembler Directives(GNU)](https://ftp.gnu.org/old-gnu/Manuals/gas-2.9.1/html_chapter/as_7.html)
- [Cowgod's Chip-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) 

#### Not necessary but some more research:
 Other's Projects that I dissected and looked at to understand the making of my own project.  
- [Lonami Chip 8 Emulator Tutorial Project Really great project using Assembly to implement chip-8 opcode](https://github.com/Lonami/chip8-asm64-emu)
    - In Lonami's chip-8 emulator they used only assembly to structure the opcodes and they completed their emulator with over 500+ lines of code. not so easy in assembly but they tackled the project and provided some valuable comments throughout their project.  
    - By looking at others' comments throughout this process I have gotten a better understanding as to how it works and what alot of the code actually DOES to make the emulator actually work
