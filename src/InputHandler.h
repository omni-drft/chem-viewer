#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <stdio.h>

#include "Structs.h"

void HandleInput(SDL_Event* e, State* state)
{
    if (e->type == SDL_KEYDOWN)
        switch (e->key.keysym.sym) 
        {
            case SDLK_ESCAPE:
                state->quit = true;
                break;
            case SDLK_a:
                printf("'a' pressed\n");
                break;
            case SDLK_b:
                printf("'b' pressed\n");
                break;
            case SDLK_c:
                printf("'c' pressed\n");
                break;
            case SDLK_d:
                printf("'d' pressed\n");
                break;
        }
}

#endif
