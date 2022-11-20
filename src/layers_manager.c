#include "../inc/game.h"

static void swap_size(t_layer *layers, SDL_Renderer *gRenderer, SDL_Texture **textures, const t_layer *initial_layers, const int amount_layers)
{
    if (layers[amount_layers - 1].texture == textures[2])
    {
        SDL_DestroyTexture(layers[amount_layers - 1].texture);
    }

    for (int i = amount_layers - 1; i > 0; i--)
    {
        layers[i] = layers[i - 1];
    }

    layers[0] = initial_layers[rand() % 5];

    if (layers[0].texture == textures[2])
    {
        layers[0].texture = loadTexture("./resource/Barrier.png", gRenderer);
    }

    if (layers[1].is_interact_layer)
    {
        layers[0] = initial_layers[0];
    }

    if (layers[1].rotation_angle != 0 || rand() % 100 > 95)
    {
        int angle = (layers[1].rotation_angle > 0 ? 5 : -5);

        if (layers[1].rotation_angle == 0 && rand() % 10 > 5)
        {
            angle = 5;
        }

        layers[0].rotation_angle += angle + layers[1].rotation_angle;

        if (layers[0].rotation_angle >= 360 || layers[0].rotation_angle <= -360)
        {
            layers[0].rotation_angle = 0;
        }
    }

    layers[0].slide_size = START_LAYER_SIZE;
}

t_layer *initial_init_layers(SDL_Texture **textures)
{
    t_layer *initial_layers = malloc(sizeof(t_layer) * 5);
    t_layer simple_layer = {0, 255, 0, textures[5], false, false, SDLK_UNKNOWN};
    t_layer square_layer = {0, 255, 0, textures[0], false, true, SDLK_q};
    t_layer triangle_layer = {0, 255, 0, textures[1], false, true, SDLK_w};
    t_layer circle_layer = {0, 255, 0, textures[6], false, true, SDLK_e};
    t_layer barrier_layer = {0, 255, 0, textures[2], true, true, SDLK_UNKNOWN};
    initial_layers[0] = simple_layer;
    initial_layers[1] = square_layer;
    initial_layers[2] = triangle_layer;
    initial_layers[3] = circle_layer;
    initial_layers[4] = barrier_layer;

    return initial_layers;
}

t_layer *init_layers(const t_layer *initial_layers, const int amount_layers)
{
    t_layer *layers = malloc(amount_layers * sizeof(t_layer));

    int size = START_LAYER_SIZE;
    for (int i = 0; i < amount_layers; i++)
    {
        layers[i] = initial_layers[0];
        layers[i].slide_size = size;

        size += ((size + 50) / 4);
    }

    return layers;
}

bool is_barrier(t_layer *layer)
{
    return (layer->is_interact_layer && layer->key == SDLK_UNKNOWN);
}

bool layers_animation(bool scroll, SDL_Renderer *gRenderer, SDL_Texture **textures, t_layer *layers, const t_layer *initial_layers, const int amount_layers)
{
    float speed = 0.3;

    for (int i = 0, c = (255 / amount_layers); i < amount_layers; i++, c += (255 / amount_layers))
    {
        SDL_FRect imagePos = {(WIDTH_SCREEN - layers[i].slide_size) / 2.0f, (HEIGHT_SCREEN - layers[i].slide_size) / 2.0f, layers[i].slide_size, layers[i].slide_size};

        if (i >= 4 && is_barrier(&layers[i]) && layers[i].alpha_color > 0)
        {
            SDL_SetTextureAlphaMod(layers[i].texture, layers[i].alpha_color -= 3);
        }

        SDL_SetTextureColorMod(layers[i].texture, c, c, c);
        SDL_RenderCopyExF(gRenderer, layers[i].texture, NULL, &imagePos, layers[i].rotation_angle, NULL, SDL_FLIP_NONE);

        if (i >= 3 && layers[i].is_interact_layer)
        {
            SDL_FRect imagePos2 = {(WIDTH_SCREEN - layers[i].slide_size) / 2.0f, (HEIGHT_SCREEN - layers[i].slide_size / 1.1) / 2.0f, layers[i].slide_size, layers[i].slide_size};

            if (!layers[i].is_press)
            {
                SDL_RenderCopyExF(gRenderer, textures[3], NULL, &imagePos2, layers[i].rotation_angle, NULL, SDL_FLIP_NONE);
            }
            else
            {
                SDL_RenderCopyExF(gRenderer, textures[4], NULL, &imagePos2, layers[i].rotation_angle, NULL, SDL_FLIP_NONE);
            }
        }

        if (scroll)
        {
            layers[i].slide_size += speed;
            speed += speed;
        }
    }

    if (layers[amount_layers - 1].slide_size >= 4000)
    {
        swap_size(layers, gRenderer, textures, initial_layers, amount_layers);
        return true;
    }

    return false;
}
