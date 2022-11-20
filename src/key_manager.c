#include "../inc/window.h"

bool just_pressed_key(SDL_Event *windowEvent, SDL_Keycode keyEvent)
{
    if (windowEvent->key.keysym.sym == keyEvent && windowEvent->type == SDL_KEYDOWN)
        return true;

    return false;
}

bool just_pressed_any_key(SDL_Event *windowEvent)
{
    if (windowEvent->type == SDL_KEYDOWN)
        return true;

    return false;
}
