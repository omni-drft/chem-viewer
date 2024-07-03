#ifndef STRUCTS_H
#define STRUCTS_H 

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct 
{
    float x, y, z;
} Vertex;

typedef struct 
{
    Vertex* vertices;
} Object;

typedef struct 
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    uint32_t* pixels;

    bool quit;
} State;

#endif
