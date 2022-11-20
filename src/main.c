#include "../inc/game.h"
#include "../inc/graphic.h"
#include "../inc/text.h"
#include <time.h>

int main(void)
{
    srand(time(NULL));

    SDL_Surface *screen_surface = NULL;
    SDL_Event windowEvent;

    SDL_Window *window = window_init(WIDTH_SCREEN, HEIGHT_SCREEN, screen_surface);
    SDL_Renderer *gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *bgTexture[7];
    bgTexture[0] = loadTexture("./resource/Quadrate.png", gRenderer);
    bgTexture[1] = loadTexture("./resource/Triangle.png", gRenderer);
    bgTexture[2] = loadTexture("./resource/Barrier.png", gRenderer);
    bgTexture[3] = loadTexture("./resource/Bad.png", gRenderer);
    bgTexture[4] = loadTexture("./resource/Good.png", gRenderer);
    bgTexture[5] = loadTexture("./resource/Underline.png", gRenderer);
    bgTexture[6] = loadTexture("./resource/Round.png", gRenderer);

    init_music();
    init_text();

    Mix_Music *ambient = Mix_LoadMUS("./resource/Ambient.wav");

    t_layer *initial_layers = initial_init_layers(bgTexture);
    t_layer *layers = init_layers(initial_layers, 8);

    int score = 0;
    int lifes = 10;

    bool is_lose = false;

    SDL_Color fgC1 = {255, 255, 255, 255};

    while (true)
    {
        SDL_RenderClear(gRenderer);

        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
            else
            {
                ambient_music(ambient);
            }
        }

        if (layers[3].is_interact_layer && !layers[3].is_press)
        {
            if (just_pressed_key(&windowEvent, layers[3].key))
            {
                layers[3].is_press = true;
                score += 5;
            }
        }

        if (is_barrier(&layers[3]) && layers[3].is_press)
        {
            if (just_pressed_any_key(&windowEvent))
            {
                layers[3].is_press = false;
            }
        }

        bool is_scrolled = layers_animation(!is_lose, gRenderer, bgTexture, layers, initial_layers, 8);

        if (is_scrolled)
        {
            if (is_barrier(&layers[4]))
            {
                if (layers[4].is_press)
                {
                    score += 5;
                }
                else
                {
                    lifes--;
                }
            }

            if (layers[4].is_interact_layer && !layers[4].is_press)
            {
                lifes--;

                if (lifes <= 0)
                {
                    is_lose = true;
                }
            }
        }

        char *score_text = mx_itoa(score);
        char *score_all_text = concat("score: ", score_text);
        char *lifes_text = mx_itoa(lifes);
        char *lifes_all_text = concat("lifes: ", lifes_text);
        SDL_Texture *score_textute = drawText(gRenderer, -(WIDTH_SCREEN / 2.3), -(HEIGHT_SCREEN / 2.2), score_all_text, 15, fgC1);
        SDL_Texture *lifes_texture = drawText(gRenderer, -(WIDTH_SCREEN / 2.3), -(HEIGHT_SCREEN / 2.4), lifes_all_text, 15, fgC1);

        SDL_DestroyTexture(score_textute);
        SDL_DestroyTexture(lifes_texture);
        free(score_text);
        free(score_all_text);
        free(lifes_text);
        free(lifes_all_text);

        SDL_RenderPresent(gRenderer);
    }

    free(initial_layers);
    free(layers);

    SDL_DestroyWindow(window);
    Mix_FreeMusic(ambient);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
