# chip8emulator-301project
## About
My CHIP8 interpretor /virtual machine  
  
For Main Project Code look at [CHIP8](https://github.com/je-el/chip8emulator-301project/tree/main/CHIP8)  
  

#### My Goals, Milestones, and Thoughts 
My main goal in this project is to understand how the interpretor works and in what ways I could possibly improve it. My main struggle when I began this project was finding information on how to make it work on my Mac OS systems. As I mainly use Mac Computers. After researching the technical references via [CowGods Chip8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) and following along with [River Gillis Tutorial for creating a CHIP-8 Interpreter and virtual machine to run it](https://riv.dev/emulating-a-computer-part-1/) I felt that I was ready enough to begin exploring more possiblities with the Chip8 Interpreter.  
In the near future I plan on using the Emulator/Interpreter to create a firewall worm, and I will keep track of that progress in a repo that will fork this project over.  
This Project was made using lots of tutorials and is heavily commented on so that I can gauge an understanding of the functionality of each line of code. 
  
##### Final Comment:
Originally I wanted this to work as expected and write it in complete asm, but as I went along I kept running into issues.  
Whether it be technical issues with the fact that I was writing this entirely on a MacOS system and it not compiling or just running into the issue of understanding why the assembly was taking so long to write.  
Eventually I opted for writing the program in C++ and following three seperate tutorials to understand what was actually happening with the creation of the opcodes in the program. I hope that all of my comments will be useful for someone else in understanding what is going on when they write an emulator.   
Completing a CHIP-8 Emulator is a very ambitious project to complete in only three weeks, I wish I would have opted to complete just running the opcode itself in assembly compared to creating the opcode, creating a 16 register stack and utilizign the opcodes as intended. 

###### Future Planning:
In the future I plan on using the completed emulator project to create a firewall worm. Or even to create a converter that will be able to translate from one programming language to another.



Eventually I want to turn this emulator into a Worm that can break through firewalls, as I think that might be an interesting project to work on.  
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
    - Absolutely perfect article that guided me through understanding how to implement chip-8 using c++
- [Assembler Directives(GNU)](https://ftp.gnu.org/old-gnu/Manuals/gas-2.9.1/html_chapter/as_7.html)
- [Cowgod's Chip-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) 

#### Not necessary but some more research:
 Other's Projects that I dissected and looked at to understand the making of my own project.  
- [Austin Morlan's Chip-8 Emulator Tutorial](https://austinmorlan.com/posts/chip8_emulator/)
    - While this was useful I was beginning to get frustrated with only reading tutorials meant to run on windows machines, I had a harder time finding information on how to make this work on Linux or Mac  
- [Lonami Chip 8 Emulator Tutorial Project Really great project using Assembly to implement chip-8 opcode](https://github.com/Lonami/chip8-asm64-emu)
- [f0lg0's Chip-8 Emulator](https://github.com/f0lg0/CHIP-8) 
    - By looking at others' comments throughout this process I have gotten a better understanding as to how it works and what alot of the code actually DOES to make the emulator actually work
