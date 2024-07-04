#ifndef BASEFUNCTIONS_H
#define BASEFUNCTIONS_H

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <bits/stdint-uintn.h>

#include "Structs.h"
#include "Constants.h"

uint8_t libInit(State* state)
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

Object* objInit()
{
    Object* cube1;
    cube1 = (Object*)malloc(sizeof(Object));
    cube1->vertices = (Vertex*)malloc(sizeof(Vertex) * 8);
    
    initVertex(&cube1->vertices[0], -1.0f, -1.0f, -1.0f);
    initVertex(&cube1->vertices[1],  1.0f, -1.0f, -1.0f);
    initVertex(&cube1->vertices[2],  1.0f,  1.0f, -1.0f);
    initVertex(&cube1->vertices[3], -1.0f,  1.0f, -1.0f);
    initVertex(&cube1->vertices[4], -1.0f, -1.0f,  1.0f);
    initVertex(&cube1->vertices[5],  1.0f, -1.0f,  1.0f);
    initVertex(&cube1->vertices[6],  1.0f,  1.0f,  1.0f);
    initVertex(&cube1->vertices[7], -1.0f,  1.0f,  1.0f);

    return cube1;
}

uint8_t mainLoop(State* state)
{

    while (!state->quit) 
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                state->quit = true;
            break;
        }

        SDL_UpdateTexture(state->texture, NULL, state->pixels, WIDTH * 4);
        SDL_RenderClear(state->renderer);
        SDL_RenderCopy(state->renderer, state->texture, NULL, NULL);
        SDL_RenderPresent(state->renderer);
    }

    return 0;
}

uint32_t cleanup(State* state, Object* object)
{
    free(state->pixels);
    free(object->vertices);
    free(object);
    return 0;
}

#endif
