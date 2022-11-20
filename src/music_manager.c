#include "../inc/game.h"

void init_music()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) > 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void ambient_music(Mix_Music *ambient)
{
    if (!Mix_PlayingMusic())
    {
        Mix_PlayMusic(ambient, -1);
    }
    else if (Mix_PausedMusic())
    {
        Mix_ResumeMusic();
    }
}

void play_sound()
{
    
}
