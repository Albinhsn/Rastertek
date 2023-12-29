#include "shader.h"
#include "opengl.h"
#include <stdio.h>

bool InitializeShader(Shader &shader, const char *vsFilename, const char *fsFilename, const char **variables,
                      int variableLength) {

    shader.vertexShader = CreateAndCompileShader(vsFilename, GL_VERTEX_SHADER);
    if (!shader.vertexShader) {
        printf("ERROR: Failed to create and compile vertexShader\n");
        return false;
    }
    shader.fragmentShader = CreateAndCompileShader(fsFilename, GL_FRAGMENT_SHADER);
    if (!shader.fragmentShader) {
        printf("ERROR: Failed to create and compile fragmentShader\n");
        return false;
    }

    shader.shaderProgram = glCreateProgram();
    glAttachShaders(shader.shaderProgram, shader.vertexShader, shader.fragmentShader);

    for (int i = 0; i < variableLength; i++) {
        glBindAttribLocation(shader.shaderProgram, i, variables[i]);
    }

    glLinkProgram(shader.shaderProgram);

    int status;
    glGetProgramiv(shader.shaderProgram, GL_LINK_STATUS, &status);
    if (status != 1) {
        OutputLinkerErrorMessage(shader.shaderProgram);
        return false;
    }

    return true;
}

void ShutdownShaders(uint shaderProgram, uint *shaders, int length) {
    // Detach the vertex and fragment shaders from the program.
    for (int i = 0; i < length; i++) {
        glDetachShader(shaderProgram, shaders[i]);
        glDeleteShader(shaders[i]);
    }
    glDeleteProgram(shaderProgram);
}
// Ambient lighting
bool SetShaderParameters9(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                          float *lightDirection, float *diffuseLightColor, float *ambientLight) {

    float tpWorldMatrix[16], tpViewMatrix[16], tpProjectionMatrix[16];

    MatrixTranspose(tpWorldMatrix, worldMatrix);
    MatrixTranspose(tpViewMatrix, viewMatrix);
    MatrixTranspose(tpProjectionMatrix, projectionMatrix);
    glUseProgram(shader.shaderProgram);
    if (!MoveMatrix4fvToShader("worldMatrix", shader.shaderProgram, tpWorldMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("viewMatrix", shader.shaderProgram, tpViewMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("projectionMatrix", shader.shaderProgram, tpProjectionMatrix)) {
        return false;
    }
    if (!Move1iToShader("shaderTexture", shader.shaderProgram, 0)) {
        return false;
    }
    if (!Move3fvToShader("lightDirection", shader.shaderProgram, lightDirection, 1)) {
        return false;
    }
    if (!Move4fvToShader("diffuseLightColor", shader.shaderProgram, diffuseLightColor, 1)) {
        return false;
    }
    if (!Move4fvToShader("ambientLight", shader.shaderProgram, ambientLight, 1)) {
        return false;
    }

    return true;
}
// LightShader
bool SetShaderParameters6(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                          float *lightDirection, float *diffuseLightColor) {

    float tpWorldMatrix[16], tpViewMatrix[16], tpProjectionMatrix[16];

    MatrixTranspose(tpWorldMatrix, worldMatrix);
    MatrixTranspose(tpViewMatrix, viewMatrix);
    MatrixTranspose(tpProjectionMatrix, projectionMatrix);
    glUseProgram(shader.shaderProgram);
    if (!MoveMatrix4fvToShader("worldMatrix", shader.shaderProgram, tpWorldMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("viewMatrix", shader.shaderProgram, tpViewMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("projectionMatrix", shader.shaderProgram, tpProjectionMatrix)) {
        return false;
    }
    if (!Move1iToShader("shaderTexture", shader.shaderProgram, 0)) {
        return false;
    }
    if (!Move3fvToShader("lightDirection", shader.shaderProgram, lightDirection, 1)) {
        return false;
    }
    if (!Move4fvToShader("diffuseLightColor", shader.shaderProgram, diffuseLightColor, 1)) {
        return false;
    }

    return true;
}

// Texture shader?
bool SetShaderParameters5(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix) {

    float tpWorldMatrix[16], tpViewMatrix[16], tpProjectionMatrix[16];

    MatrixTranspose(tpWorldMatrix, worldMatrix);
    MatrixTranspose(tpViewMatrix, viewMatrix);
    MatrixTranspose(tpProjectionMatrix, projectionMatrix);

    glUseProgram(shader.shaderProgram);
    if (!MoveMatrix4fvToShader("worldMatrix", shader.shaderProgram, tpWorldMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("viewMatrix", shader.shaderProgram, tpViewMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("projectionMatrix", shader.shaderProgram, tpProjectionMatrix)) {
        return false;
    }
    if (!Move1iToShader("shaderTexture", shader.shaderProgram, 0)) {
        return false;
    }

    return true;
}
