#include "peBase.h"
#include <SDL_error.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdbool.h>

unsigned int peInit(peState* state, const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        const char* error = SDL_GetError();
        printf("ProcekEngine error: %s\n", error);
        return 1;
    }

    state->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width , height, SDL_WINDOW_SHOWN);
    if (state->window == NULL)
    {
        const char* error = SDL_GetError();
        printf("ProcekEngine error: %s\n", error);
        return 2;
    }

    state->renderer = SDL_CreateRenderer(state->window, -1, 0);
    if(state->renderer == NULL)
    {
        const char* error = SDL_GetError();
        printf("ProcekEngine error: %s\n", error);
        return 3;
    }

    state->texture = SDL_CreateTexture(state->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (state->texture == NULL)
    {
        const char* error = SDL_GetError();
        printf("ProcekEngine error: %s\n", error);
        return 4;
    }

    state->framebuffer = (uint32_t*)malloc(width * height * 4);
    state->quit = 0;

    int i;
    for (i = 0; i < width * height; ++i)
        state->framebuffer[i] = 0x000000FF;

    return 0;
}

unsigned int peCleanup(peState* state)
{

    free(state->framebuffer);
    free(state->window);
    free(state->renderer);
    free(state->texture);
    return 0;

}

void peUpdateRenderer(peState* state)
{
    int width;
    SDL_GetWindowSize(state->window, &width, NULL);
    SDL_UpdateTexture(state->texture, NULL, state->framebuffer, width * 4);
    SDL_RenderClear(state->renderer);
    SDL_RenderCopy(state->renderer, state->texture, NULL, NULL);
    SDL_RenderPresent(state->renderer);
}

void peDetectClose(peState* state)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            state->quit = true;
        break;
    }
}
