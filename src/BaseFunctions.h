#ifndef BASEFUNCTIONS_H
#define BASEFUNCTIONS_H

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <bits/stdint-uintn.h>

#include "Structs.h"
#include "Constants.h"

uint8_t baseInit(State* state)
{
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        const char* error = SDL_GetError();
        printf("ERROR:%s\n", error);
        return 1;
    }
    
    state->window = SDL_CreateWindow("ChemViewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (state->window == NULL)
    {
        const char* error = SDL_GetError();
        printf("ERROR:%s\n", error);
        SDL_Quit();
        return 1;
    }

    state->renderer = SDL_CreateRenderer(state->window, -1, 0);

    if (state->renderer == NULL)
    {
        const char* error = SDL_GetError();
        printf("Error:%s\n", error);
        SDL_Quit();
        return 1;
    }

    state->texture = SDL_CreateTexture(state->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    if (state->texture == NULL)
    {
        const char* error = SDL_GetError();
        printf("Error:%s\n", error);
        SDL_Quit();
        return 1;
    }

    state->pixels = (uint32_t*)malloc(PIX_NUM * 4);

    state->quit = false;

    int i;
    for (i = 0; i < PIX_NUM; ++i)
        state->pixels[i] = 0xFF5733FF;
    

    return 0;
}

#endif
