# chip8emulator-301project
## About
My CHIP8 interpretor /virtual machine  
  
For Main Project Code look at [CHIP8](https://github.com/je-el/chip8emulator-301project/tree/main/CHIP_8C)  
  
### Requirements
- SDL2 for graphics
- C++
- Understanding of CHIP-8's opcodes, and structure.
  
  
#### My Goals, Milestones, and Thoughts  
My main goal in this project is to understand how the interpretor works and in what ways I could possibly improve it. My main struggle when I began this project was finding information on how to make it work on my Mac OS systems. As I mainly use Mac Computers. After researching the technical references via [CowGods Chip8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) and following along with [River Gillis Tutorial for creating a CHIP-8 Interpreter and virtual machine to run it](https://riv.dev/emulating-a-computer-part-1/) I felt that I was ready enough to begin exploring more possiblities with the Chip8 Interpreter.  
In the near future I plan on using the Emulator.
This Project was made using lots of tutorials and is heavily commented on so that I can gauge an understanding of the functionality of each line of code. 

By the end of reading the tutorial I realized that I understood what was happening only half of the time and the code that I was running hadn't felt complete at all and when I thought it was ready to compile the console simple pooped its pants.
  
  
##### Final Comment:
Originally I wanted this to work as expected and write it in complete asm, but as I went along I kept running into issues.  
Whether it be technical issues with the fact that I was writing this entirely based off of others knowledge compared to writing the opcodes to my own understand or the issue of the program not printing to the terminal console becasue my files were linked incorrectly to one another.  
I'm planning to tackle the project in a new light in the following days before submitting th efinal polished code, as I've come to understand my shortcomings, the final codeed project will incllude the chip 8 interpreter in simpler terms and shorter code blocks. I may or may not implement the Graphics for the project by the turn-in date but the final code should be able to perform simple tasks without the need of a graphics renderer.


In the end, I opted for writing the program in C++ and following three seperate tutorials to understand what was actually happening with the creation of the opcodes in the program. I hope that all of my comments will be useful for someone else in understanding what is going on when they write an emulator.   
Completing a CHIP-8 Emulator is a very ambitious project to complete in only five weeks as a full-time student, I wish I would have opted to complete just running the opcode itself in assembly compared to creating the opcode, creating a 16 register stack and utilizing the opcodes as intended. 

###### Future Planning:
In the future I plan on using the completed emulator project to create a firewall worm. Or even to create a converter that will be able to translate from one programming language to another. But with what I've learned in creating this interpreter is that it won't be an easy task.
Eventually I want to turn this emulator into a Worm that can break through firewalls, as I think that might be an interesting project to work on.  





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
