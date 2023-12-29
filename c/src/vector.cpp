#include "vector.h"
#include "math.h"

void MatrixRotationX(float *matrix, float angle) {
    float cos_angle = cosf(angle);
    float sin_angle = sinf(angle);
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = cos_angle;
    matrix[6] = sin_angle;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = -sin_angle;
    matrix[10] = cos_angle;
    matrix[11] = 0.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;

    return;
}
void MatrixRotationY(float *matrix, float angle) {
    matrix[0] = cosf(angle);
    matrix[1] = 0.0f;
    matrix[2] = -sinf(angle);
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = 1.0f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = sinf(angle);
    matrix[9] = 0.0f;
    matrix[10] = cosf(angle);
    matrix[11] = 0.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;

    return;
}
void MatrixRotationZ(float *matrix, float angle) {
    matrix[0] = cosf(angle);
    matrix[1] = sinf(angle);
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = -sinf(angle);
    matrix[5] = cosf(angle);
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;
    matrix[11] = 0.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}
void MatrixTranslation(float *matrix, float x, float y, float z) {
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = 1.0f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;
    matrix[11] = 0.0f;

    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
    matrix[15] = 1.0f;

    return;
}
void MatrixScale(float *matrix, Vector3 vec) {
    matrix[0] = vec.x;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = vec.y;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = vec.z;
    matrix[11] = 0.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

void MatrixScale(float *matrix, float x, float y, float z) {
    matrix[0] = x;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = y;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = z;
    matrix[11] = 0.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}
void MatrixTranspose(float *result, float *matrix) {
    result[0] = matrix[0];
    result[1] = matrix[4];
    result[2] = matrix[8];
    result[3] = matrix[12];

    result[4] = matrix[1];
    result[5] = matrix[5];
    result[6] = matrix[9];
    result[7] = matrix[13];

    result[8] = matrix[2];
    result[9] = matrix[6];
    result[10] = matrix[10];
    result[11] = matrix[14];

    result[12] = matrix[3];
    result[13] = matrix[7];
    result[14] = matrix[11];
    result[15] = matrix[15];
}
void MatrixMultiply(float *result, float *m1, float *m2) {

    result[0] = (m1[0] * m2[0]) + (m1[1] * m2[4]) + (m1[2] * m2[8]) + (m1[3] * m2[12]);
    result[1] = (m1[0] * m2[1]) + (m1[1] * m2[5]) + (m1[2] * m2[9]) + (m1[3] * m2[13]);
    result[2] = (m1[0] * m2[2]) + (m1[1] * m2[6]) + (m1[2] * m2[10]) + (m1[3] * m2[14]);
    result[3] = (m1[0] * m2[3]) + (m1[1] * m2[7]) + (m1[2] * m2[11]) + (m1[3] * m2[15]);

    result[4] = (m1[4] * m2[0]) + (m1[5] * m2[4]) + (m1[6] * m2[8]) + (m1[7] * m2[12]);
    result[5] = (m1[4] * m2[1]) + (m1[5] * m2[5]) + (m1[6] * m2[9]) + (m1[7] * m2[13]);
    result[6] = (m1[4] * m2[2]) + (m1[5] * m2[6]) + (m1[6] * m2[10]) + (m1[7] * m2[14]);
    result[7] = (m1[4] * m2[3]) + (m1[5] * m2[7]) + (m1[6] * m2[11]) + (m1[7] * m2[15]);

    result[8] = (m1[8] * m2[0]) + (m1[9] * m2[4]) + (m1[10] * m2[8]) + (m1[11] * m2[12]);
    result[9] = (m1[8] * m2[1]) + (m1[9] * m2[5]) + (m1[10] * m2[9]) + (m1[11] * m2[13]);
    result[10] = (m1[8] * m2[2]) + (m1[9] * m2[6]) + (m1[10] * m2[10]) + (m1[11] * m2[14]);
    result[11] = (m1[8] * m2[3]) + (m1[9] * m2[7]) + (m1[10] * m2[11]) + (m1[11] * m2[15]);

    result[12] = (m1[12] * m2[0]) + (m1[13] * m2[4]) + (m1[14] * m2[8]) + (m1[15] * m2[12]);
    result[13] = (m1[12] * m2[1]) + (m1[13] * m2[5]) + (m1[14] * m2[9]) + (m1[15] * m2[13]);
    result[14] = (m1[12] * m2[2]) + (m1[13] * m2[6]) + (m1[14] * m2[10]) + (m1[15] * m2[14]);
    result[15] = (m1[12] * m2[3]) + (m1[13] * m2[7]) + (m1[14] * m2[11]) + (m1[15] * m2[15]);
}
void BuildIdentityMatrix(float *matrix) {
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = 1.0f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;
    matrix[11] = 0.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

void BuildPerspectiveFovMatrix(float *matrix, float fieldOfView, float screenAspect, float screenNear,
                               float screenDepth) {
    matrix[0] = 1.0f / (screenAspect * tan(fieldOfView * 0.5f));
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = 1.0f / tan(fieldOfView * 0.5f);
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = screenDepth / (screenDepth - screenNear);
    matrix[11] = 1.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = (-screenNear * screenDepth) / (screenDepth - screenNear);
    matrix[15] = 0.0f;

    return;
}
void BuildOrthoMatrix(float *matrix, float screenWidth, float screenHeight, float screenNear, float screenDepth) {
    matrix[0] = 2.0f / screenWidth;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = 2.0f / screenHeight;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f / (screenDepth - screenNear);
    matrix[11] = 0.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = screenNear / (screenNear - screenDepth);
    matrix[15] = 1.0f;
}

void Get4x4Matrix(float *dest, float *source) {
    dest[0] = source[0];
    dest[1] = source[1];
    dest[2] = source[2];
    dest[3] = source[3];

    dest[4] = source[4];
    dest[5] = source[5];
    dest[6] = source[6];
    dest[7] = source[7];

    dest[8] = source[8];
    dest[9] = source[9];
    dest[10] = source[10];
    dest[11] = source[11];

    dest[12] = source[12];
    dest[13] = source[13];
    dest[14] = source[14];
    dest[15] = source[15];
}
