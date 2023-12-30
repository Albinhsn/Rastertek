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

    shader.program = glCreateProgram();
    glAttachShaders(shader.program, shader.vertexShader, shader.fragmentShader);

    for (int i = 0; i < variableLength; i++) {
        glBindAttribLocation(shader.program, i, variables[i]);
    }

    glLinkProgram(shader.program);

    int status;
    glGetProgramiv(shader.program, GL_LINK_STATUS, &status);
    if (status != 1) {
        OutputLinkerErrorMessage(shader.program);
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
    glUseProgram(shader.program);
    int location = glGetUniformLocation(shader.program, "worldMatrix");
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpWorldMatrix);

    // Set the view matrix in the vertex shader.
    location = glGetUniformLocation(shader.program, "viewMatrix");
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpViewMatrix);

    // Set the projection matrix in the vertex shader.
    location = glGetUniformLocation(shader.program, "projectionMatrix");
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpProjectionMatrix);

    // Set the light position array in the vertex shader.
    location = glGetUniformLocation(shader.program, "lightPosition");
    if (location == -1) {
        return false;
    }
    glUniform3fv(location, numLights, lightPositionArray);

    // Set the texture in the pixel shader to use the data from the first texture
    // unit.
    location = glGetUniformLocation(shader.program, "shaderTexture");
    if (location == -1) {
        return false;
    }
    glUniform1i(location, 0);

    // Set the diffuse light color array in the pixel shader.
    location = glGetUniformLocation(shader.program, "diffuseColor");
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
    glUseProgram(shader.program);
    if (!MoveMatrix4fvToShader("worldMatrix", shader.program, tpWorldMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("viewMatrix", shader.program, tpViewMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("projectionMatrix", shader.program, tpProjectionMatrix)) {
        return false;
    }
    if (!Move3fvToShader("cameraPosition", shader.program, cameraPosition, 1)) {
        return false;
    }
    if (!Move1iToShader("shaderTexture", shader.program, 0)) {
        return false;
    }
    if (!Move3fvToShader("lightDirection", shader.program, lightDirection, 1)) {
        return false;
    }
    if (!Move4fvToShader("diffuseLightColor", shader.program, diffuseLightColor, 1)) {
        return false;
    }
    if (!Move4fvToShader("ambientLight", shader.program, ambientLight, 1)) {
        return false;
    }
    if (!Move1fToShader("specularPower", shader.program, specularPower)) {
        return false;
    }
    if (!Move4fvToShader("specularColor", shader.program, specularColor, 1)) {
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
    glUseProgram(shader.program);
    if (!MoveMatrix4fvToShader("worldMatrix", shader.program, tpWorldMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("viewMatrix", shader.program, tpViewMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("projectionMatrix", shader.program, tpProjectionMatrix)) {
        return false;
    }
    if (!Move1iToShader("shaderTexture", shader.program, 0)) {
        return false;
    }
    if (!Move3fvToShader("lightDirection", shader.program, lightDirection, 1)) {
        return false;
    }
    if (!Move4fvToShader("diffuseLightColor", shader.program, diffuseLightColor, 1)) {
        return false;
    }
    if (!Move4fvToShader("ambientLight", shader.program, ambientLight, 1)) {
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
    glUseProgram(shader.program);
    if (!MoveMatrix4fvToShader("worldMatrix", shader.program, tpWorldMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("viewMatrix", shader.program, tpViewMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("projectionMatrix", shader.program, tpProjectionMatrix)) {
        return false;
    }
    if (!Move1iToShader("shaderTexture", shader.program, 0)) {
        return false;
    }
    if (!Move3fvToShader("lightDirection", shader.program, lightDirection, 1)) {
        return false;
    }
    if (!Move4fvToShader("diffuseLightColor", shader.program, diffuseLightColor, 1)) {
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

    glUseProgram(shader.program);
    if (!MoveMatrix4fvToShader("worldMatrix", shader.program, tpWorldMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("viewMatrix", shader.program, tpViewMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("projectionMatrix", shader.program, tpProjectionMatrix)) {
        return false;
    }
    if (!Move1iToShader("shaderTexture", shader.program, 0)) {
        return false;
    }

    return true;
}
bool SetShaderParameters12(Shader shader, float *worldMatrix, float *viewMatrix, float *orthoMatrix) {
    float tpWorldMatrix[16], tpViewMatrix[16], tpOrthoMatrix[16];

    MatrixTranspose(tpWorldMatrix, worldMatrix);
    MatrixTranspose(tpViewMatrix, viewMatrix);
    MatrixTranspose(tpOrthoMatrix, orthoMatrix);

    glUseProgram(shader.program);
    if (!MoveMatrix4fvToShader("worldMatrix", shader.program, tpWorldMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("viewMatrix", shader.program, tpViewMatrix)) {
        return false;
    }
    if (!MoveMatrix4fvToShader("projectionMatrix", shader.program, tpOrthoMatrix)) {
        return false;
    }

    if (!Move1iToShader("shaderTexture", shader.program, 0)) {
        return false;
    }

    return true;
}
bool SetShaderParameters14(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                           float *pixelColor) {
    float tpWorldMatrix[16], tpViewMatrix[16], tpProjectionMatrix[16];
    int location;

    // Transpose the matrices to prepare them for the shader.
    MatrixTranspose(tpWorldMatrix, worldMatrix);
    MatrixTranspose(tpViewMatrix, viewMatrix);
    MatrixTranspose(tpProjectionMatrix, projectionMatrix);

    // Install the shader program as part of the current rendering state.
    glUseProgram(shader.program);

    // Set the world matrix in the vertex shader.
    location = glGetUniformLocation(shader.program, "worldMatrix");
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpWorldMatrix);

    // Set the view matrix in the vertex shader.
    location = glGetUniformLocation(shader.program, "viewMatrix");
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpViewMatrix);

    // Set the projection matrix in the vertex shader.
    location = glGetUniformLocation(shader.program, "projectionMatrix");
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpProjectionMatrix);

    // Set the texture in the pixel shader to use the data from the first texture unit.
    location = glGetUniformLocation(shader.program, "shaderTexture");
    if (location == -1) {
        return false;
    }
    glUniform1i(location, 0);

    // Set the font pixel color in the pixel shader.
    location = glGetUniformLocation(shader.program, "pixelColor");
    if (location == -1) {
        return false;
    }
    glUniform4fv(location, 1, pixelColor);

    return true;
}
