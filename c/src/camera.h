#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "vector.h"

struct Camera {
        Vector3 position;
        Vector3 rotation;
        float viewMatrix[16];
};
void SetPosition(float, float, float);
void SetRotation(float, float, float);

void GetPosition(float *);
void GetRotation(float *);

void Render();

void MatrixRotationYawPitchRoll(float *, float, float, float);
void TransformCoord(Vector3 &, float *);
void BuildViewMatrix(float*, Vector3, Vector3, Vector3);

#endif
