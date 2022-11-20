#ifndef GAME
#define GAME

#define START_LAYER_SIZE 200

#include "window.h"
#include "graphic.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

typedef struct s_layer
{
    float slide_size;
    short int alpha_color;
    short int rotation_angle;
    SDL_Texture *texture;

    bool is_press;
    bool is_interact_layer;
    SDL_Keycode key;
} t_layer;

bool layers_animation(bool scroll, SDL_Renderer *gRenderer, SDL_Texture **textures, t_layer *layers, const t_layer *initial_layers, const int amount_layers);
bool is_barrier(t_layer *layer);

void ambient_music(Mix_Music *gMusic);
void init_music();

t_layer *init_layers(const t_layer *initial_layers, const int amount_layers);
t_layer *initial_init_layers(SDL_Texture **textures);

#endif
