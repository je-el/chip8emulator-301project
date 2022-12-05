#include "common_headers.h"
#include "sdl_viewer.h"
#include <SDL2/SDL.h>

SDLViewer::SDLViewer(const std::string& title, int width, int height, int window_scale) : title_(title){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        throw std::runtime_error(SDL_GetError());
    }

    //
    window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width * window_scale, height * window_scale, SDL_WINDOW_SHOWN);
}