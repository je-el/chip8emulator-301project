//main.cpp file
#include "common_headers.h"
#include <iostream>
#include <exception>
#include "cpu_chip8.h"
#include "Image.h"
#include "sdl_viewer.h"

//chip 8 class will hold onto the state of the machine and interpreter 
void RUN() {
    int width = 64;
    int height = 32;

    SDLViewer viewer("CHIP-8 Emulator",  width, height, /*window_scale=*/8);
        uint8_t* rgb24 = static_cast<uint8_t*>(std::calloc(width * height * 3, sizeof(uint8_t)));
    viewer.SetFrameRGB24(rgb24, height);

    cpuchip8 cpu;
    cpu.Initialize("/path/to/program/file");
    bool quit = false;
    while (!quit) {
        cpu.runcycle();
        cpu.GetFrame()->CopyToRGB24(rgb24, /*r=*/255, /*g=*/0, /*b=*/0);
        viewer.SetFrameRGB24(rgb24, height);
        auto events = viewer.Update();

        for (const auto& e : events) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
  }
}

int main(int argc, char** argv)
{
    try{ RUN(); } 
    catch (const std::exception& e){
        std::cerr << "ERROR: "<< e.what();
        return 1; }
        
}


