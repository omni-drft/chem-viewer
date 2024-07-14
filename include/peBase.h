#ifndef PEBASE_H
#define PEBASE_H

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <SDL_error.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    uint32_t* framebuffer;
    unsigned short int quit;
} peState;

unsigned int peInit(peState*, const char*, int, int);

#endif
