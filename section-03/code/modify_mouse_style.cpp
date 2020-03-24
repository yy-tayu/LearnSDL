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
    SDL_Surface* mouse_style1 = SDL_LoadBMP("mouse style1.bmp");
    SDL_Surface* mouse_style2 = SDL_LoadBMP("mouse style2.bmp");
    SDL_Surface *mouse_style3 = SDL_LoadBMP("mouse style3.bmp");
    SDL_SetColorKey(mouse_style1, SDL_TRUE, SDL_MapRGB(mouse_style1->format, 255, 241, 241));
    SDL_SetColorKey(mouse_style2, SDL_TRUE, SDL_MapRGB(mouse_style2->format, 255, 241, 241));
    SDL_SetColorKey(mouse_style3, SDL_TRUE, SDL_MapRGB(mouse_style3->format, 255, 241, 241));
    SDL_Surface* mouse_array[3]{ mouse_style1 ,mouse_style2 ,mouse_style3 };
    SDL_Surface* current_mouse_style = mouse_style1;
    SDL_Event sdl_event;
    bool sdl_quit = false;
    SDL_Rect mouse_picture_dest{};
    auto draw_mouse = [&]()
    {
        if (sdl_event.motion.x !=0 && sdl_event.motion.y != 0)
        {
            mouse_picture_dest.x = sdl_event.motion.x - current_mouse_style->w / 3.5;
            mouse_picture_dest.y = sdl_event.motion.y - current_mouse_style->h / 4;
            std::cout << "x: " << mouse_picture_dest.x << "   y: " << mouse_picture_dest.y << std::endl;
        }
        SDL_FillRect(window_surface, NULL, 0);
        SDL_BlitSurface(current_mouse_style, NULL, window_surface, &mouse_picture_dest);
        SDL_UpdateWindowSurface(window);
    };
    SDL_ShowCursor(false);
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
            else if (sdl_event.type == SDL_MOUSEMOTION)
            {
                draw_mouse();
            }
            else if(sdl_event.type ==SDL_MOUSEWHEEL)
            {
                static int i = 0;
                if (sdl_event.wheel.y > 0)
                {
                    i = ++i>2? 0:i;
                    current_mouse_style = mouse_array[i];
                    draw_mouse();
                }
                else if (sdl_event.wheel.y < 0)
                {
                    i = --i < 0 ? 2 : i;
                    current_mouse_style = mouse_array[i];
                    draw_mouse();
                }

            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}