#ifndef GRAPHIC
#define GRAPHIC

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

SDL_Surface *loadSurface(char *path, SDL_Surface *screen_surface);
SDL_Texture *loadTexture(char *path, SDL_Renderer *gRenderer);
SDL_Point getsize(SDL_Texture *texture);

#endif


