#include "textureshader.h"
#include "opengl.h"
#include "utils.h"
#include "vector.h"
#include <cstring>
#include <iostream>

bool SetShaderParameters(TextureShader *textureShader, float *worldMatrix, float *viewMatrix, float *projectionMatrix) {

    float tpWorldMatrix[16], tpViewMatrix[16], tpProjectionMatrix[16];
    int location;

    // Transpose the matrices to prepare them for the shader.
    MatrixTranspose(tpWorldMatrix, worldMatrix);
    MatrixTranspose(tpViewMatrix, viewMatrix);
    MatrixTranspose(tpProjectionMatrix, projectionMatrix);

    // Install the shader program as part of the current rendering state.
    UseProgram(textureShader->shaderProgram);

    // Set the world matrix in the vertex shader.
    char worldMatrixStr[12] = "worldMatrix";

    location = GetUniformLocation(textureShader->shaderProgram, worldMatrixStr);
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpWorldMatrix);

    // Set the view matrix in the vertex shader.
    char viewMatrixStr[11] = "viewMatrix";
    location = GetUniformLocation(textureShader->shaderProgram, viewMatrixStr);
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpViewMatrix);

    // Set the projection matrix in the vertex shader.
    char projectionMatrixStr[17] = "projectionMatrix";
    location = GetUniformLocation(textureShader->shaderProgram, projectionMatrixStr);
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpProjectionMatrix);

    char shaderTextureStr[14] = "shaderTexture";
    location = GetUniformLocation(textureShader->shaderProgram, shaderTextureStr);
    if (location == -1) {
        return false;
    }

    glUniform1i(location, 0);

    return true;
}
void ShutdownShader(TextureShader *textureShader) {
    // Detach the vertex and fragment shaders from the program.
    DetachShader(textureShader->shaderProgram, textureShader->vertexShader);
    DetachShader(textureShader->shaderProgram, textureShader->fragmentShader);

    // Delete the vertex and fragment shaders.
    DeleteShader(textureShader->vertexShader);
    DeleteShader(textureShader->fragmentShader);

    // Delete the shader program.
    DeleteProgram(textureShader->shaderProgram);
}
void Shutdown(TextureShader *textureShader) {
    ShutdownShader(textureShader);
}

bool InitializeTextureShader(TextureShader *textureShader) {
    char vsFilename[128];
    char psFilename[128];

    bool result;

    strcpy(vsFilename, "./shaders/texture.vs");
    strcpy(psFilename, "./shaders/texture.ps");

    result = InitializeShader(textureShader, vsFilename, psFilename);
    if (!result) {
        return false;
    }

    return true;
}
