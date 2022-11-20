#ifndef WINDOW
#define WINDOW

#define WIDTH_SCREEN 1280
#define HEIGHT_SCREEN 720

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>

SDL_Window *window_init(int WIDTH, int HEIGHT, SDL_Surface *screen_surface);

bool just_pressed_key(SDL_Event *windowEvent, SDL_Keycode keyEvent);
bool just_pressed_any_key(SDL_Event *windowEvent);

#endif

