#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <bits/stdint-uintn.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Structs.h"
#include "BaseFunctions.h"

#define WIDTH    800 
#define HEIGHT   600
#define PIX_NUM  (WIDTH * HEIGHT)

#define FRAMERATE 1

int main()
{
    State state;

    baseInit(&state);

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


    free(state.pixels);

    printf("ChemViewer closed without errors!\n");
    return 0;
}
