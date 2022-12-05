#include "common_headers.h"
#include "sdl_viewer.h"
#include <sdl_viewer.h>/SDL.h>

SDLViewer::SDLViewer(const std::string& title, int width, int height, int window_scale) : title_(title){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        throw std::runtime_error(SDL_GetError());
    }

}