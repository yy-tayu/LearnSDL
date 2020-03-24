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
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(rend);
    SDL_Surface* mouse_style1 = SDL_LoadBMP("mouse style1.bmp");
    SDL_SetColorKey(mouse_style1, SDL_TRUE, SDL_MapRGB(mouse_style1->format, 255, 241, 241));
    SDL_Texture* mouse_style1_texture = SDL_CreateTextureFromSurface(rend,mouse_style1);
    SDL_Surface* mouse_style2 = SDL_LoadBMP("mouse style2.bmp");
    SDL_SetColorKey(mouse_style2, SDL_TRUE, SDL_MapRGB(mouse_style2->format, 255, 241, 241));
    SDL_Texture* mouse_style2_texture = SDL_CreateTextureFromSurface(rend, mouse_style2);
    SDL_Surface* mouse_style3 = SDL_LoadBMP("mouse style3.bmp");
    SDL_SetColorKey(mouse_style3, SDL_TRUE, SDL_MapRGB(mouse_style3->format, 255, 241, 241));
    SDL_Texture* mouse_style3_texture = SDL_CreateTextureFromSurface(rend, mouse_style3);
    SDL_Texture* texture_array[3]{ mouse_style1_texture ,mouse_style2_texture ,mouse_style3_texture };
    SDL_Texture* current_texture = mouse_style1_texture;
    SDL_Event sdl_event;
    bool sdl_quit = false; 
    SDL_Rect mouse_picture_dest{};
    mouse_picture_dest.x = 0;
    mouse_picture_dest.y = 0;
    mouse_picture_dest.w = mouse_style1->w;
    mouse_picture_dest.h = mouse_style1->h;

    auto draw_mouse = [&]()
    {
        if (sdl_event.motion.x != 0 && sdl_event.motion.y != 0)
        {
            mouse_picture_dest.x = sdl_event.motion.x - mouse_picture_dest.w / 3.5;
            mouse_picture_dest.y = sdl_event.motion.y - mouse_picture_dest.h / 4;
            std::cout << "x: " << mouse_picture_dest.x << "   y: " << mouse_picture_dest.y << std::endl;
        }
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, current_texture, NULL, &mouse_picture_dest);
        SDL_RenderPresent(rend);
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
                mouse_picture_dest.x = sdl_event.motion.x;
                mouse_picture_dest.y = sdl_event.motion.y;
                draw_mouse();
            }
            else if (sdl_event.type == SDL_MOUSEWHEEL)
            {
                static int i = 0;
                if (sdl_event.wheel.y > 0)
                {
                    i = ++i > 2 ? 0 : i;
                    current_texture = texture_array[i];
                    draw_mouse();
                }
                else if (sdl_event.wheel.y < 0)
                {
                    i = --i < 0 ? 2 : i;
                    current_texture = texture_array[i];
                    draw_mouse();
                }
            }
        }
        SDL_Delay(10);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}