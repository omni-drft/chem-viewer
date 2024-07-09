#ifndef STRUCTS_H
#define STRUCTS_H 

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct 
{
    float x, y, z, w;
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

void initVertex(Vertex* vertex, float _x, float _y, float _z, float _w)
{
    vertex->x = _x;
    vertex->y = _y;
    vertex->z = _z;
    vertex->w = _w;
}

#endif
