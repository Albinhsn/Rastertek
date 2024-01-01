#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
struct Vector3 {
    float x;
    float y;
    float z;
};

void MatrixRotationX(float *, float);
void MatrixRotationY(float *, float);
void MatrixRotationZ(float *, float);
void MatrixTranslation(float *, float, float, float);
void MatrixScale(float *, float, float, float);
void MatrixTranspose(float *, float *);
void MatrixMultiply(float *, float *, float *);
void BuildIdentityMatrix(float *);
void BuildPerspectiveFovMatrix(float *, float, float, float, float);
void BuildOrthoMatrix(float *, float, float, float, float);
void DebugPrint4x4Matrix(float *matrix);

void Get4x4Matrix(float *dest, float *source);

#endif
