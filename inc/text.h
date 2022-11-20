#ifndef TEXT
#define TEXT

#include "graphic.h"
#include "window.h"

#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Texture *drawText(SDL_Renderer *gRenderer, int x, int y, char *string, int size, SDL_Color fgC);

char *concat(char *s1, char *s2);
char *mx_itoa(int number);

void init_text();

#endif
