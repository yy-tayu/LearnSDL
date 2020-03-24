#include <iostream>
#include "SDL2/include/SDL.h"

const int screen_width = 800;
const int screen_height = 600;

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("YourGame",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        screen_width, screen_height,
        SDL_WINDOW_SHOWN);
    SDL_Surface* window_surface = SDL_GetWindowSurface(window);
    SDL_Event sdl_event;
    bool sdl_quit = false;
    while (!sdl_quit)
    {
        while (SDL_PollEvent(&sdl_event))
        {
            if (sdl_event.type == SDL_QUIT)
            {
                std::cout << "SDL QUIT ENENT!" << std::endl;
                sdl_quit = true;
            }
            else if (sdl_event.type == SDL_MOUSEBUTTONDOWN)
            {
                auto button_type = sdl_event.button.button == SDL_BUTTON_LEFT ? "Left" : "Right";
                std::cout << "Button is " << button_type << " Down" << std::endl;
            }
            else if (sdl_event.type == SDL_KEYDOWN)
            {
                std::cout << "Keyboard is " << sdl_event.key.keysym.sym << " Down" << std::endl;
                std::cout << "Keyboard is " << sdl_event.key.keysym.scancode << " Down" << std::endl;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}