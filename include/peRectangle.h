#ifndef PERECTANGLE_H
#define PERECTANGLE_H

#include <bits/stdint-uintn.h>

#include "peMath.h"
#include "peBase.h"

typedef struct {
    pePoint x1, x2, x3, x4;
    uint32_t color;
} peRectangle;

void peRecScale(peRectangle*, float, float);

void pePrintRec(peRectangle*, peState*);



#endif


