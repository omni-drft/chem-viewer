#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <bits/stdint-uintn.h>
#include <stdio.h>
#include <stdbool.h>

#define WIDTH    800 
#define HEIGHT   600
#define PIX_NUM  (WIDTH * HEIGHT)

#define FRAMERATE 1

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    uint32_t* pixels;

    bool quit;
} State;

int main()
{
    State state;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        const char* error = SDL_GetError();
        printf("ERROR:%s\n", error);
        return 1;
    }

    state.window = SDL_CreateWindow("ChemViewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (state.window == NULL)
    {
        const char* error = SDL_GetError();
        printf("ERROR:%s\n", error);
        SDL_Quit();
        return 1;
    }

    state.renderer = SDL_CreateRenderer(state.window, -1, 0);

    if (state.renderer == NULL)
    {
        const char* error = SDL_GetError();
        printf("Error:%s\n", error);
        SDL_Quit();
        return 1;
    }

    state.texture = SDL_CreateTexture(state.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    if (state.texture == NULL)
    {
        const char* error = SDL_GetError();
        printf("Error:%s\n", error);
        SDL_Quit();
        return 1;
    }

    state.pixels = malloc(PIX_NUM * 4);

    state.quit = false;

    int i;
    for (i = 0; i < PIX_NUM; ++i)
        state.pixels[i] = 0xFF5733FF;
    
    while (!state.quit) 
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                state.quit = true;
            break;
        }

        SDL_UpdateTexture(state.texture, NULL, state.pixels, WIDTH * 4);
        SDL_RenderClear(state.renderer);
        SDL_RenderCopy(state.renderer, state.texture, NULL, NULL);
        SDL_RenderPresent(state.renderer);

    }



    printf("ChemViewer closed without errors!\n");
    return 0;
}
