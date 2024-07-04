#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <bits/stdint-uintn.h>
#include <stdio.h>
#include <stdbool.h>

#include "Structs.h"
#include "BaseFunctions.h"
#include "Constants.h"

int main()
{
    State state;

    if (libInit(&state)) printf("Error has occured during SDL initialisation\n");

    Object* cube1 = objInit();

    if (mainLoop(&state)) printf("Error has occured during main loop execution\n");

    if (cleanup(&state, cube1)) printf("Error has occured during cleanup\n");

    printf("ChemViewer closed without errors!\n");
    return 0;
}
