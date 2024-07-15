#ifndef PESTRUCTS_H
#define PESTRUCTS_H

typedef struct {
    int x, y;
} pePoint;

typedef struct {
    float components[4];
} peMat2x2;

pePoint peMat2xPoint(peMat2x2, pePoint);

peMat2x2 peMat2xMat2(peMat2x2, peMat2x2);

#endif
