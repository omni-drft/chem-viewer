#include "peRectangle.h"
#include "peMath.h"
#include <SDL_video.h>

void peRecScale(peRectangle* rec, float x, float y)
{
    peMat2x2 scalingMat;

    scalingMat.components[0] = x;
    scalingMat.components[1] = 0;
    scalingMat.components[2] = 0;
    scalingMat.components[3] = y;

    rec->x1 = peMat2xPoint(scalingMat, rec->x1);
    rec->x2 = peMat2xPoint(scalingMat, rec->x2);
    rec->x3 = peMat2xPoint(scalingMat, rec->x3);
    rec->x4 = peMat2xPoint(scalingMat, rec->x4);
}

void pePrintRec(peRectangle* rec, peState* state)
{
    int width, height;
    SDL_GetWindowSize(state->window, &width, &height);
    state->framebuffer[(width * ((height / 2) - rec->x1.y)) + (width / 2) + rec->x1.x] = rec->color;



}
