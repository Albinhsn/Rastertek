#ifndef VECTOR_H
#define VECTOR_H

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

void GetWorldMatrix(float *);
void GetProjectionMatrix(float *, float *);
void GetOrthoMatrix(float *);

#endif
