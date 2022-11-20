#include "../inc/window.h"

SDL_Window *window_init(int WIDTH, int HEIGHT, SDL_Surface *screen_surface)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Neon flow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    
    // Check that the window was successfully created
    if (window == NULL)
    {
        // In the case that the window could not be made...
        printf("Could not create window: %s", SDL_GetError());
        return NULL; // exit
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }
    else
    {
        // Get window surface
        screen_surface = SDL_GetWindowSurface(window);
    }

    return window;
}
