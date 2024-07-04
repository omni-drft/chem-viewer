#ifndef MATH_H
#define MATH_H

#include <stdint.h>
#include <math.h>
#include <xmmintrin.h>

typedef struct 
{
    float comps[16];
} Matrix4;


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




#endif
