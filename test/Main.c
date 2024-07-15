#include <stdbool.h>

#include "peBase.h"


int main()
{
    peState state;
    peInit(&state, "Testowe Okno", 400, 400);

    while (!state.quit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                state.quit = true;
            break;

        }
    }
}
