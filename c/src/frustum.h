#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "math.h"
#include "opengl.h"
#include "vector.h"
struct Frustum {
    float planes[6][4];
};

void ConstructFrustum(Frustum &frustum, float, float *, float *);
bool CheckPoint(Frustum frustum, float, float, float);
bool CheckCube(Frustum frustum, float, float, float, float);
bool CheckSphere(Frustum frustum, float, float, float, float);
bool CheckRectangle(Frustum frustum, float, float, float, float, float, float);

#endif
