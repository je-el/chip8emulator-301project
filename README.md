# chip8emulator-301project
## About
My CHIP8 interpretor /virtual machine  
  
For Main Project Code look at [CHIP8](https://github.com/je-el/chip8emulator-301project/tree/main/CHIP8)  
  
*In reality this is all simulation.* *(I say as a jest pointing toward my unused video game consoles)*  
  
This Project was made using lots of tutorials and is heavily commented on so that I can gauge an understanding of the functionality of each line of code. 

### Requirements
- SDL Library(for graphics) ---> [See Absolutely Necessary Reads](#absolutely-necessary-reads)
- C++

## References/Resources:
#### Videos: 
- NaN  
#### Absolutely Necessary Reads:
- [Lazy Foo' Productions "Setting up SDL 2 on Mac OS X Monterey" Because how else will I run my graphics on my swanky Apple Silicon Mac](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/mac/index.php)
    - Great read, in depth tutorial in how to set up SDL 2 and get to actually work compared to all the other tutorials that jsut say download it and be gone.
    - Another SDL wiki as a guide: [SDL Wiki](https://wiki.libsdl.org/SDL2/SDL_PixelFormatEnum)  
- [River Gillis Tutorial for creating a CHIP-8 Interpreter and virtual machine to run it](https://riv.dev/emulating-a-computer-part-1/)
    - Absolutely perfect research that gave me the hope I needed to make this work for me
- [Assembler Directives(GNU)](https://ftp.gnu.org/old-gnu/Manuals/gas-2.9.1/html_chapter/as_7.html)
- [Cowgod's Chip-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) 

#### Not necessary but some more research:
 Other's Projects that I dissected and looked at to understand the making of my own project.  
- [Austin Morlan's Chip-8 Emulator Tutorial](https://austinmorlan.com/posts/chip8_emulator/)
    - While this was useful I was beginning to get frustrated with only reading tutorials meant to run on windows machines, I had a harder time finding information on how to make this work on Linux or Mac  
- [Lonami Chip 8 Emulator Tutorial Project](https://github.com/Lonami/chip8-asm64-emu)
- [f0lg0's Chip-8 Emulator](https://github.com/f0lg0/CHIP-8) 
    - By looking at others' comments throughout this process I have gotten a better understanding as to how it works and what alot of the code actually DOES to make the emulator actually work
