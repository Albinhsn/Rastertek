#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "vector.h"

struct Camera {
        Vector3 position;
        Vector3 rotation;
        float viewMatrix[16];
};
void SetPosition(Camera *camera, float, float, float);
void SetRotation(Camera *camera, float, float, float);
void Render(Camera *camera);
void MatrixRotationYawPitchRoll(float *, float , float , float );
void TransformCoord(Vector3 &, float *);
void BuildViewMatrix(float*, Vector3, Vector3, Vector3);

#endif
