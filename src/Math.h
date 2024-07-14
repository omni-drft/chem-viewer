#ifndef MATH_H
#define MATH_H

#include <stdint.h>
#include <math.h>
#include <xmmintrin.h>

#include "Structs.h"
#include "Constants.h"

typedef struct 
{
    float comps[16];
} Matrix4;

typedef struct
{
    int x;
    int y;
} Point;

Matrix4 translationMat(float tx, float ty, float tz)
{
    Matrix4 mat;
    
    int_fast8_t i;
    for (i = 0; i < 16; ++i) 
        mat.comps[i] = 0.0f;    
    
    mat.comps[3]  = tx;
    mat.comps[7]  = ty;
    mat.comps[11] = tz;
    mat.comps[15] = 1.0f;

    return mat;
}

Matrix4 rotationMatX(float angle)
{
    Matrix4 mat;
    
    int_fast8_t i;
    for (i = 0; i < 16; ++i)
        mat.comps[i] = 0.0f;

    mat.comps[0]  = 1.0f;
    mat.comps[5]  = cosf(angle);
    mat.comps[6]  = -1 * sinf(angle);
    mat.comps[9]  = sinf(angle);
    mat.comps[10] = cosf(angle);
    mat.comps[15] = 1.0f;

    return mat;
}

Matrix4 rotationMatY(float angle)
{
    Matrix4 mat;

    int_fast8_t i;
    for (i = 0; i < 16; ++i)
        mat.comps[i] = 0.0f;

    mat.comps[0]  = cosf(angle);
    mat.comps[2]  = sinf(angle);
    mat.comps[5]  = 1.0f;
    mat.comps[8]  = -1 * sinf(angle);
    mat.comps[10] = cosf(angle);
    mat.comps[15] = 1.0f;

    return mat;
}

Matrix4 rotationMatZ(float angle)
{
    Matrix4 mat;

    int_fast8_t i;
    for (i = 0; i < 16; ++i)
        mat.comps[i] = 0.0f;
    mat.comps[0]  = cosf(angle);
    mat.comps[1]  = -1 * sinf(angle);
    mat.comps[4]  = sinf(angle);
    mat.comps[5]  = cosf(angle);
    mat.comps[10] = 1.0f;
    mat.comps[15] = 1.0f;
    
    return mat;
}


Matrix4 scalingMat(float sx, float sy, float sz)
{
    Matrix4 mat;

    int_fast8_t i;
    for (i = 0; i < 16; ++i)
        mat.comps[i] = 0.0f;

    mat.comps[0]  = sx;
    mat.comps[5]  = sy;
    mat.comps[10] = sz;
    mat.comps[15] = 1.0f;

    return mat;
}

Matrix4 identityMat()
{
    Matrix4 mat;

    int_fast8_t i;
    for (i = 0; i < 16; ++i)
        mat.comps[i] = 0.0f;

    mat.comps[0]  = 1.0f;
    mat.comps[5]  = 1.0f;
    mat.comps[10] = 1.0f;
    mat.comps[15] = 1.0f;

    return mat;
}

void matXMat(float* A, float* B, float* C)
{
    __m128 row1 = _mm_load_ps(&B[0]);
    __m128 row2 = _mm_load_ps(&B[4]);
    __m128 row3 = _mm_load_ps(&B[8]);
    __m128 row4 = _mm_load_ps(&B[12]);

    int_fast8_t i;
    for(i=0; i<4; ++i) {
        __m128 brod1 = _mm_set1_ps(A[4*i + 0]);
        __m128 brod2 = _mm_set1_ps(A[4*i + 1]);
        __m128 brod3 = _mm_set1_ps(A[4*i + 2]);
        __m128 brod4 = _mm_set1_ps(A[4*i + 3]);
        __m128 row = _mm_add_ps(
                    _mm_add_ps(
                        _mm_mul_ps(brod1, row1),
                        _mm_mul_ps(brod2, row2)),
                    _mm_add_ps(
                        _mm_mul_ps(brod3, row3),
                        _mm_mul_ps(brod4, row4)));
        _mm_store_ps(&C[4*i], row);
    }
}

Matrix4 combinedTransformation(Matrix4* translation, Matrix4* rotationX, Matrix4* rotationY, Matrix4* rotationZ, Matrix4* scaling)
{
    Matrix4 result1;
    matXMat(translation->comps, rotationX->comps, result1.comps);

    Matrix4 result2;
    matXMat(result1.comps, rotationY->comps, result2.comps);

    matXMat(result2.comps, rotationZ->comps, result1.comps);
    matXMat(result1.comps, scaling->comps, result2.comps);

    return result2;
}

Vertex vertByMat(Vertex* vertex, Matrix4* matrix)
{
    Vertex result;
    
    result.x = matrix->comps[0] * vertex->x 
             + matrix->comps[1] * vertex->y
             + matrix->comps[2] * vertex->z
             + matrix->comps[3] * vertex->w;
    
    result.y = matrix->comps[4] * vertex->x 
             + matrix->comps[5] * vertex->y
             + matrix->comps[6] * vertex->z
             + matrix->comps[7] * vertex->w;

    result.z = matrix->comps[8] * vertex->x 
             + matrix->comps[9] * vertex->y
             + matrix->comps[10] * vertex->z
             + matrix->comps[11] * vertex->w;
    
    result.w = matrix->comps[12] * vertex->x 
             + matrix->comps[13] * vertex->y
             + matrix->comps[14] * vertex->z
             + matrix->comps[15] * vertex->w;

    return result;
}

void perspectiveProjection(Vertex* vertex)
{
    float xScreen = vertex->x / vertex->z;
    float yScreen = vertex->y / vertex->z;
    
    vertex->x = xScreen;
    vertex->y = yScreen;
}

void viewportTransformation(Vertex* vertex)
{
    float xScreen = vertex->x;
    float yScreen = vertex->y;
    float       z = vertex->z;

    float xPixel = (xScreen + 1) * WIDTH / 2;
    float yPixel = (1 - yScreen) * HEIGHT / 2;

    vertex->x = xPixel;
    vertex->y = yPixel;
    vertex->z = z;
}

void setPixel(State* state, int x, int y)
{
    if (x >= 0 && x <= WIDTH && y <= HEIGHT && y >= 0)
        state->pixels[y * WIDTH + x] = 0x43ff64d9;
}

void drawLine(float x0, float y0, float x1, float y1, State* state)
{
    int castX0 = (int)x0;
    int castX1 = (int)x1;
    int castY0 = (int)y0;
    int castY1 = (int)y1;

    int dx = abs(castX1 - castX0);
    int dy = abs(castY1 - castY0);

    int sx = (castX0 < castX1) ? 1 : -1;
    int sy = (castY0 < castY1) ? 1 : -1;

    int err = dx - dy;

    while (1) 
    {
        setPixel(state, castX0, castY0);
        if (castX0 >= castX1 && castY0 >= castY1) 
        {
            printf("Loop stopped!\n");
            break;
        }
        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            castX0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            castY0 += sy;
        }
    }
}

void rasterize(Object* object, State* state)
{
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    int i;
    for (i = 0; i < 12; ++i)
    {
        int v0Index = edges[i][0];
        int v1Index = edges[i][1];

        Point p0;
        p0.x = (int)object->vertices[v0Index].x;
        p0.y = (int)object->vertices[v0Index].y;

        Point p1;
        p1.x = (int)object->vertices[v1Index].x;
        p1.x = (int)object->vertices[v1Index].x;

        drawLine(p0.x, p0.y, p1.x, p1.y, state);
    }
}


#endif
