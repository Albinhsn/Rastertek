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
// Multiple point lights
bool SetShaderParameters11(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                           float *diffuseColorArray, float *lightPositionArray, int numLights) {

    float tpWorldMatrix[16], tpViewMatrix[16], tpProjectionMatrix[16];

    MatrixTranspose(tpWorldMatrix, worldMatrix);
    MatrixTranspose(tpViewMatrix, viewMatrix);
    MatrixTranspose(tpProjectionMatrix, projectionMatrix);
    glUseProgram(shader.shaderProgram);
    int location = glGetUniformLocation(shader.shaderProgram, "worldMatrix");
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpWorldMatrix);

    // Set the view matrix in the vertex shader.
    location = glGetUniformLocation(shader.shaderProgram, "viewMatrix");
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpViewMatrix);

    // Set the projection matrix in the vertex shader.
    location = glGetUniformLocation(shader.shaderProgram, "projectionMatrix");
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpProjectionMatrix);

    // Set the light position array in the vertex shader.
    location = glGetUniformLocation(shader.shaderProgram, "lightPosition");
    if (location == -1) {
        return false;
    }
    glUniform3fv(location, numLights, lightPositionArray);

    // Set the texture in the pixel shader to use the data from the first texture
    // unit.
    location = glGetUniformLocation(shader.shaderProgram, "shaderTexture");
    if (location == -1) {
        return false;
    }
    glUniform1i(location, 0);

    // Set the diffuse light color array in the pixel shader.
    location = glGetUniformLocation(shader.shaderProgram, "diffuseColor");
    if (location == -1) {
        return false;
    }
    glUniform4fv(location, numLights, diffuseColorArray);

    return true;
}
// Specular Lighting
bool SetShaderParameters10(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                           float *lightDirection, float *diffuseLightColor, float *ambientLight, float *cameraPosition,
                           float *specularColor, float specularPower) {

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
    if (!Move3fvToShader("cameraPosition", shader.shaderProgram, cameraPosition, 1)) {
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
    if (!Move1fToShader("specularPower", shader.shaderProgram, specularPower)) {
        return false;
    }
    if (!Move4fvToShader("specularColor", shader.shaderProgram, specularColor, 1)) {
        return false;
    }

    return true;
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
