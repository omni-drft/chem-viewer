#include "peMath.h"

#include <math.h>

pePoint peMat2xPoint(peMat2x2 mat, pePoint point)
{
    pePoint result;
    result.x = roundf(mat.components[0] * point.x + mat.components[1] * point.y);
    result.y = roundf(mat.components[2] * point.x + mat.components[3] * point.y);
    return result;
}

peMat2x2 peMat2xMat2(peMat2x2 mat1, peMat2x2 mat2)
{
    peMat2x2 result;

    result.components[0] = mat1.components[0] * mat2.components[0] + mat1.components[1] * mat2.components[2];
    result.components[1] = mat1.components[0] * mat2.components[1] + mat1.components[1] * mat2.components[3];
    result.components[2] = mat1.components[2] * mat2.components[0] + mat1.components[3] * mat2.components[2];
    result.components[3] = mat1.components[2] * mat2.components[1] + mat1.components[3] * mat2.components[3];

    return result;
}
