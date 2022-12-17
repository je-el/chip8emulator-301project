#include <iostream>
#include "chip8.h"
#include "SDL2/SDL.h" 
//#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;

chip8 myChip8;

//might not need this ugh
bool loadROM(const std::string& filename, chip8& myChip8)
{
    // Open the ROM file
    std::ifstream rom(filename, std::ios::binary);
    if (!rom)
    {
        std::cerr << "Error: Failed to open ROM file" << std::endl;
        return false;
    }

    // Read the ROM file into memory
    rom.seekg(0, std::ios::end);
    int size = rom.tellg();
    rom.seekg(0, std::ios::beg);
    if (size > 3584) // 3584 = 4096 - 512 (fontset)
    {
        std::cerr << "Error: ROM file is too large" << std::endl;
        return false;
    }
    rom.read((char*)&myChip8.memory[512], size);
    rom.close();

    return true;
    /* 
        use this to access the rom from the function with this:
            if (!loadROM("TETRIS", myChip8))
            {
                return 1;
            }
    */
}


void handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            exit(0);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            // Update the key state
            myChip8.key[event.key.keysym.sym] = 1;
        }
        else if (event.type == SDL_KEYUP)
        {
            // Update the key state
            myChip8.key[event.key.keysym.sym] = 0;
        }
    }
}

void updateScreen(SDL_Renderer* renderer, SDL_Texture* screen)
{
    // Update the screen texture
    void* pixels;
    int pitch;
    SDL_LockTexture(screen, NULL, &pixels, &pitch);
    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 64; x++)
        {
            if (myChip8.gfx[(y * 64) + x] == 0)
            {
                ((Uint32*)pixels)[y * 64 + x] = 0;
            }
            else
            {
                ((Uint32*)pixels)[y * 64 + x] = 0xFFFFFFFF;
            }
        }
    }
    SDL_UnlockTexture(screen);

    // Render the screen texture
    SDL_RenderCopy(renderer, screen, NULL, NULL);
    SDL_RenderPresent(renderer);

    // Reset the draw flag
    myChip8.drawFlag = false;
}


int main(int argc, char* argv[])
{
    // Initialize the Chip 8 emulator and SDL2
    myChip8.initialize();
    SDL_Init(SDL_INIT_VIDEO);
    //Load the ROM file
    if (argc < 2)
    {
        std::cerr << "Error: no ROM file specified." << std::endl;
        return 1;
    }

    // Load the ROM file
    if (!myChip8.loadROM(argv[1]))
    {
        std::cerr << "Error: failed to load ROM file." << std::endl;
        return 1;
    }

    // Create the window and renderer
    SDL_Window* window = SDL_CreateWindow("Chip 8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);

    // Enter the main loop
    while (true)
    {
        // Handle events
        handleEvents();

        // Emulate one cycle of the Chip 8 emulator
        myChip8.emulateCycle();

        // Update the screen if necessary
        if (myChip8.drawFlag)
        {
            updateScreen(renderer, screen);
        }

        // Update the timers
        if (myChip8.delay_timer > 0)
        {
            myChip8.delay_timer--;
        }
        if (myChip8.sound_timer > 0)
        {
            if (myChip8.sound_timer == 1)
            {
                // Play a beep sound
            }
            myChip8.sound_timer--;
        }
    }

    // Clean up
    SDL_DestroyTexture(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}



//original main file
/*
#include <iostream>
#include "chip8.h"
#include "SDL2/SDL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;

chip8 myChip8;

int main(int argc, char* argv[])
{
    // Initialize the Chip 8 emulator
    myChip8.initialize();

    // Load the program into memory
    myChip8.loadGame("program.ch8");

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create the window
    SDL_Window* window = SDL_CreateWindow("Chip 8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create the renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create the texture for the screen
    SDL_Texture* screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);
    if (screen == nullptr)
    {
        std::cout << "Screen texture creation failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Main loop
    bool running = true;
    while (running)
    {
        // Check for events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                // Update the key state
                myChip8.key[event.key.keysym.sym] = 1;
            }
            else if (event.type == SDL_KEYUP)
            {
                // Update the key state
                myChip8.key[event.key.keysym.sym] = 0;
            }
        }

        // Emulate one cycle
        myChip8.emulatecycle();

        // Update the screen if necessary
        if (myChip8.drawFlag)
        {
            // Clear the screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(            renderer);

            // Update the screen texture
            void* pixels;
            int pitch;
            SDL_LockTexture(screen, NULL, &pixels, &pitch);
            for (int y = 0; y < 32; y++)
            {
                for (int x = 0; x < 64; x++)
                {
                    if (myChip8.gfx[(y * 64) + x] == 0)
                    {
                        ((Uint32*)pixels)[y * 64 + x] = 0;
                    }
                    else
                    {
                        ((Uint32*)pixels)[y * 64 + x] = 0xFFFFFFFF;
                    }
                }
            }
            SDL_UnlockTexture(screen);

            // Render the screen texture
            SDL_RenderCopy(renderer, screen, NULL, NULL);
            SDL_RenderPresent(renderer);

            // Reset the draw flag
            myChip8.drawFlag = false;
        }

        // Update the timers
        if (myChip8.delay_timer > 0)
        {
            myChip8.delay_timer--;
        }
        if (myChip8.sound_timer > 0)
        {
            if (myChip8.sound_timer == 1)
            {
                                // Play a beep sound
            }
            myChip8.sound_timer--;
        }
    }

    // Clean up
    SDL_DestroyTexture(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

    This main file initializes the Chip 8 emulator and SDL2, creates a window and renderer using SDL2, and enters a main loop to run the emulator. 
    In the main loop, it checks for events (such as key presses), emulates one cycle of the Chip 8 emulator, and updates the screen if necessary.
    It also updates the timers and plays a beep sound when the sound timer reaches 0. The main loop exits when the user closes the window. 
    Finally, it cleans up the SDL2 resources and exits the program.
*/
