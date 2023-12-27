#include "camera.h"

void initializeCamera(Camera *camera) {


    camera->position.x = 0.0f;
    camera->position.y = 0.0f;
    camera->position.z = 0.0f;

    camera->rotation.x = 0.0f;
    camera->rotation.y = 0.0f;
    camera->rotation.z = 0.0f;
}

void SetPosition(Camera *camera, float x, float y, float z) {

    camera->position.x = x;
    camera->position.y = y;
    camera->position.z = z;
}
void SetRotation(Camera *camera, float x, float y, float z) {
    camera->rotation.x = x;
    camera->rotation.y = y;
    camera->rotation.z = z;
}

void Render(Camera *camera) {
    Vector3 up, position, lookAt;
    float yaw, pitch, roll;
    float rotationMatrix[9];

    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;

    position.x = camera->position.x;
    position.y = camera->position.y;
    position.z = camera->position.z;

    lookAt.x = 0.0f;
    lookAt.y = 0.0f;
    lookAt.z = 1.0f;

    pitch = camera->rotation.x * 0.0174532925f;
    yaw = camera->rotation.y * 0.0174532925f;
    roll = camera->rotation.z * 0.0174532925f;

    MatrixRotationYawPitchRoll(rotationMatrix, yaw, pitch, roll);

    TransformCoord(lookAt, rotationMatrix);
    TransformCoord(up, rotationMatrix);

    lookAt.x += position.x;
    lookAt.y += position.y;
    lookAt.z += position.z;

    BuildViewMatrix(camera->viewMatrix, position, lookAt, up);
}
void MatrixRotationYawPitchRoll(float *matrix, float yaw, float pitch, float roll) {
    float cYaw, cPitch, cRoll, sYaw, sPitch, sRoll;

    cYaw = cosf(yaw);
    cPitch = cosf(pitch);
    cRoll = cosf(roll);

    sYaw = sinf(yaw);
    sPitch = sinf(pitch);
    sRoll = sinf(roll);

    // Calculate the yaw, pitch, roll rotation matrix.
    matrix[0] = (cRoll * cYaw) + (sRoll * sPitch * sYaw);
    matrix[1] = (sRoll * cPitch);
    matrix[2] = (cRoll * -sYaw) + (sRoll * sPitch * cYaw);

    matrix[3] = (-sRoll * cYaw) + (cRoll * sPitch * sYaw);
    matrix[4] = (cRoll * cPitch);
    matrix[5] = (sRoll * sYaw) + (cRoll * sPitch * cYaw);

    matrix[6] = (cPitch * sYaw);
    matrix[7] = -sPitch;
    matrix[8] = (cPitch * cYaw);
}
void TransformCoord(Vector3 &vector, float *matrix) {
    float x, y, z;

    // Transform the vector by the 3x3 matrix.
    x = (vector.x * matrix[0]) + (vector.y * matrix[3]) + (vector.z * matrix[6]);
    y = (vector.x * matrix[1]) + (vector.y * matrix[4]) + (vector.z * matrix[7]);
    z = (vector.x * matrix[2]) + (vector.y * matrix[5]) + (vector.z * matrix[8]);

    // Store the result in the reference.
    vector.x = x;
    vector.y = y;
    vector.z = z;
}

void BuildViewMatrix(float *viewMatrix, Vector3 position, Vector3 lookAt, Vector3 up) {

    Vector3 zAxis, xAxis, yAxis;
    float length, result1, result2, result3;

    // zAxis = normal(lookAt - position)
    zAxis.x = lookAt.x - position.x;
    zAxis.y = lookAt.y - position.y;
    zAxis.z = lookAt.z - position.z;
    length = sqrt((zAxis.x * zAxis.x) + (zAxis.y * zAxis.y) + (zAxis.z * zAxis.z));
    zAxis.x = zAxis.x / length;
    zAxis.y = zAxis.y / length;
    zAxis.z = zAxis.z / length;

    // xAxis = normal(cross(up, zAxis))
    xAxis.x = (up.y * zAxis.z) - (up.z * zAxis.y);
    xAxis.y = (up.z * zAxis.x) - (up.x * zAxis.z);
    xAxis.z = (up.x * zAxis.y) - (up.y * zAxis.x);
    length = sqrt((xAxis.x * xAxis.x) + (xAxis.y * xAxis.y) + (xAxis.z * xAxis.z));
    xAxis.x = xAxis.x / length;
    xAxis.y = xAxis.y / length;
    xAxis.z = xAxis.z / length;

    // yAxis = cross(zAxis, xAxis)
    yAxis.x = (zAxis.y * xAxis.z) - (zAxis.z * xAxis.y);
    yAxis.y = (zAxis.z * xAxis.x) - (zAxis.x * xAxis.z);
    yAxis.z = (zAxis.x * xAxis.y) - (zAxis.y * xAxis.x);

    // -dot(xAxis, position)
    result1 = ((xAxis.x * position.x) + (xAxis.y * position.y) + (xAxis.z * position.z)) * -1.0f;

    // -dot(yaxis, eye)
    result2 = ((yAxis.x * position.x) + (yAxis.y * position.y) + (yAxis.z * position.z)) * -1.0f;

    // -dot(zaxis, eye)
    result3 = ((zAxis.x * position.x) + (zAxis.y * position.y) + (zAxis.z * position.z)) * -1.0f;

    // Set the computed values in the view matrix.
    viewMatrix[0] = xAxis.x;
    viewMatrix[1] = yAxis.x;
    viewMatrix[2] = zAxis.x;
    viewMatrix[3] = 0.0f;

    viewMatrix[4] = xAxis.y;
    viewMatrix[5] = yAxis.y;
    viewMatrix[6] = zAxis.y;
    viewMatrix[7] = 0.0f;

    viewMatrix[8] = xAxis.z;
    viewMatrix[9] = yAxis.z;
    viewMatrix[10] = zAxis.z;
    viewMatrix[11] = 0.0f;

    viewMatrix[12] = result1;
    viewMatrix[13] = result2;
    viewMatrix[14] = result3;
    viewMatrix[15] = 1.0f;
}
