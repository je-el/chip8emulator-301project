#ifndef SDL_VIEWER_H_
#define SDL_VIEWER_H_

#include <mutex>
#include <sdl_viewer.h>/SDL.h>

#include "common_headers.h"
//#include "sdl_timer.h"

//RAII hardware-accelerated SDL window
// optimized for RGB24 texture streaming.
//this class will recieve texture updates and perform the rendering
//the constructor will take the window scale because if we tried to draw a 64x32 image to screen 
//it would be super tiny.

class SDLViewer{
    public:
        //the width and height have to be equal to the size of the images uploaded
        //via setFrameRGB24
        SDLViewer(const std::string& title, int width, int height, int window_scale = 1);
        ~SDLViewer();

        //renders the frame adn returns a list of the events
        std::vector<SDL_Event> Update();

        //assumes 8bit RGB image with stride/length is equal towidth
        void SetFrameRGB24(uint8_t* rgb24, int height);

    private:
        SDL_Window* window_ = nullptr;
        SDL_Renderer* renderer_ = nullptr;
        SDL_Texture* window_tex_ = nullptr;
};


#endif