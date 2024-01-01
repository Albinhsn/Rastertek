#include "frustum.h"

void ConstructFrustum(Frustum &frustum, float screenDepth, float *viewMatrix, float *projectionMatrix) {
    float zMinimum, r, t;
    float matrix[16];

    // Calculate the minimum Z distance in the frustum.
    zMinimum = -projectionMatrix[14] / projectionMatrix[10];
    r = screenDepth / (screenDepth - zMinimum);
    projectionMatrix[10] = r;
    projectionMatrix[14] = -r * zMinimum;

    // Create the frustum matrix from the view matrix and updated projection matrix.
    MatrixMultiply(matrix, viewMatrix, projectionMatrix);

    // Get the near plane of the frustum.
    frustum.planes[0][0] = matrix[2];
    frustum.planes[0][1] = matrix[6];
    frustum.planes[0][2] = matrix[10];
    frustum.planes[0][3] = matrix[14];

    // Normalize it.
    t = (float)sqrt((frustum.planes[0][0] * frustum.planes[0][0]) + (frustum.planes[0][1] * frustum.planes[0][1]) +
                    (frustum.planes[0][2] * frustum.planes[0][2]));
    frustum.planes[0][0] /= t;
    frustum.planes[0][1] /= t;
    frustum.planes[0][2] /= t;
    frustum.planes[0][3] /= t;

    // Calculate the far plane of the frustum.
    frustum.planes[1][0] = matrix[3] - matrix[2];
    frustum.planes[1][1] = matrix[7] - matrix[6];
    frustum.planes[1][2] = matrix[11] - matrix[10];
    frustum.planes[1][3] = matrix[15] - matrix[14];

    // Normalize it.
    t = (float)sqrt((frustum.planes[1][0] * frustum.planes[1][0]) + (frustum.planes[1][1] * frustum.planes[1][1]) +
                    (frustum.planes[1][2] * frustum.planes[1][2]));
    frustum.planes[1][0] /= t;
    frustum.planes[1][1] /= t;
    frustum.planes[1][2] /= t;
    frustum.planes[1][3] /= t;

    // Calculate the left plane of the frustum.
    frustum.planes[2][0] = matrix[3] + matrix[0];
    frustum.planes[2][1] = matrix[7] + matrix[4];
    frustum.planes[2][2] = matrix[11] + matrix[8];
    frustum.planes[2][3] = matrix[15] + matrix[12];

    // Normalize it.
    t = (float)sqrt((frustum.planes[2][0] * frustum.planes[2][0]) + (frustum.planes[2][1] * frustum.planes[2][1]) +
                    (frustum.planes[2][2] * frustum.planes[2][2]));
    frustum.planes[2][0] /= t;
    frustum.planes[2][1] /= t;
    frustum.planes[2][2] /= t;
    frustum.planes[2][3] /= t;

    // Calculate the right plane of the frustum.
    frustum.planes[3][0] = matrix[3] - matrix[0];
    frustum.planes[3][1] = matrix[7] - matrix[4];
    frustum.planes[3][2] = matrix[11] - matrix[8];
    frustum.planes[3][3] = matrix[15] - matrix[12];

    // Normalize it.
    t = (float)sqrt((frustum.planes[3][0] * frustum.planes[3][0]) + (frustum.planes[3][1] * frustum.planes[3][1]) +
                    (frustum.planes[3][2] * frustum.planes[3][2]));
    frustum.planes[3][0] /= t;
    frustum.planes[3][1] /= t;
    frustum.planes[3][2] /= t;
    frustum.planes[3][3] /= t;

    // Calculate the top plane of the frustum.
    frustum.planes[4][0] = matrix[3] - matrix[1];
    frustum.planes[4][1] = matrix[7] - matrix[5];
    frustum.planes[4][2] = matrix[11] - matrix[9];
    frustum.planes[4][3] = matrix[15] - matrix[13];

    // Normalize it.
    t = (float)sqrt((frustum.planes[4][0] * frustum.planes[4][0]) + (frustum.planes[4][1] * frustum.planes[4][1]) +
                    (frustum.planes[4][2] * frustum.planes[4][2]));
    frustum.planes[4][0] /= t;
    frustum.planes[4][1] /= t;
    frustum.planes[4][2] /= t;
    frustum.planes[4][3] /= t;

    // Calculate the bottom plane of the frustum.
    frustum.planes[5][0] = matrix[3] + matrix[1];
    frustum.planes[5][1] = matrix[7] + matrix[5];
    frustum.planes[5][2] = matrix[11] + matrix[9];
    frustum.planes[5][3] = matrix[15] + matrix[13];

    // Normalize it.
    t = (float)sqrt((frustum.planes[5][0] * frustum.planes[5][0]) + (frustum.planes[5][1] * frustum.planes[5][1]) +
                    (frustum.planes[5][2] * frustum.planes[5][2]));
    frustum.planes[5][0] /= t;
    frustum.planes[5][1] /= t;
    frustum.planes[5][2] /= t;
    frustum.planes[5][3] /= t;
}

bool CheckPoint(Frustum frustum, float x, float y, float z) {
    for (int i = 0; i < 6; i++) {
        if (((frustum.planes[i][0] * x) + (frustum.planes[i][1] * y) + (frustum.planes[i][2] * z) +
             frustum.planes[i][3]) < 0.0f) {
            return false;
        }
    }

    return true;
}
bool CheckCube(Frustum frustum, float xCenter, float yCenter, float zCenter, float radius) {
    int i;

    // Check if any one point of the cube is in the view frustum.
    for (i = 0; i < 6; i++) {
        if (frustum.planes[i][0] * (xCenter - radius) + frustum.planes[i][1] * (yCenter - radius) +
                frustum.planes[i][2] * (zCenter - radius) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter + radius) + frustum.planes[i][1] * (yCenter - radius) +
                frustum.planes[i][2] * (zCenter - radius) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter - radius) + frustum.planes[i][1] * (yCenter + radius) +
                frustum.planes[i][2] * (zCenter - radius) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter + radius) + frustum.planes[i][1] * (yCenter + radius) +
                frustum.planes[i][2] * (zCenter - radius) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter - radius) + frustum.planes[i][1] * (yCenter - radius) +
                frustum.planes[i][2] * (zCenter + radius) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter + radius) + frustum.planes[i][1] * (yCenter - radius) +
                frustum.planes[i][2] * (zCenter + radius) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter - radius) + frustum.planes[i][1] * (yCenter + radius) +
                frustum.planes[i][2] * (zCenter + radius) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter + radius) + frustum.planes[i][1] * (yCenter + radius) +
                frustum.planes[i][2] * (zCenter + radius) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        return false;
    }

    return true;
}

bool CheckSphere(Frustum frustum, float xCenter, float yCenter, float zCenter, float radius) {
    int i;

    // Check if the radius of the sphere is inside the view frustum.
    for (i = 0; i < 6; i++) {
        if (((frustum.planes[i][0] * xCenter) + (frustum.planes[i][1] * yCenter) + (frustum.planes[i][2] * zCenter) +
             frustum.planes[i][3]) < -radius) {
            return false;
        }
    }

    return true;
}
bool CheckRectangle(Frustum frustum, float xCenter, float yCenter, float zCenter, float xSize, float ySize,
                    float zSize) {
    int i;

    // Check if any of the 6 planes of the rectangle are inside the view frustum.
    for (i = 0; i < 6; i++) {
        if (frustum.planes[i][0] * (xCenter - xSize) + frustum.planes[i][1] * (yCenter - ySize) +
                frustum.planes[i][2] * (zCenter - zSize) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter + xSize) + frustum.planes[i][1] * (yCenter - ySize) +
                frustum.planes[i][2] * (zCenter - zSize) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter - xSize) + frustum.planes[i][1] * (yCenter + ySize) +
                frustum.planes[i][2] * (zCenter - zSize) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter - xSize) + frustum.planes[i][1] * (yCenter - ySize) +
                frustum.planes[i][2] * (zCenter + zSize) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter + xSize) + frustum.planes[i][1] * (yCenter + ySize) +
                frustum.planes[i][2] * (zCenter - zSize) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter + xSize) + frustum.planes[i][1] * (yCenter - ySize) +
                frustum.planes[i][2] * (zCenter + zSize) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter - xSize) + frustum.planes[i][1] * (yCenter + ySize) +
                frustum.planes[i][2] * (zCenter + zSize) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        if (frustum.planes[i][0] * (xCenter + xSize) + frustum.planes[i][1] * (yCenter + ySize) +
                frustum.planes[i][2] * (zCenter + zSize) + frustum.planes[i][3] >=
            0.0f) {
            continue;
        }

        return false;
    }

    return true;
}
