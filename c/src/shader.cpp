#include "shader.h"

bool InitializeShader(Shader &shader, const char *vsFilename, const char *fsFilename, const char **variables,
                      int variableLength) {

    const char *vertexShaderBuffer;
    const char *fragmentShaderBuffer;

    int status;

    vertexShaderBuffer = ReadFile(vsFilename);
    if (!vertexShaderBuffer) {
        return false;
    }

    fragmentShaderBuffer = ReadFile(fsFilename);
    if (!fragmentShaderBuffer) {
        return false;
    }

    // Create a vertex and fragment shader object.
    shader.vertexShader = CreateShader(GL_VERTEX_SHADER);
    shader.fragmentShader = CreateShader(GL_FRAGMENT_SHADER);

    // Copy the shader source code strings into the vertex and fragment shader
    // objects.
    glShaderSource(shader.vertexShader, vertexShaderBuffer);
    glShaderSource(shader.fragmentShader, fragmentShaderBuffer);

    // Release the vertex and fragment shader buffers.
    delete[] vertexShaderBuffer;
    vertexShaderBuffer = 0;

    delete[] fragmentShaderBuffer;
    fragmentShaderBuffer = 0;

    // Compile the shaders.
    glCompileShader(shader.vertexShader);
    glCompileShader(shader.fragmentShader);

    // Check to see if the vertex shader compiled successfully.
    glGetShaderiv(shader.vertexShader, GL_COMPILE_STATUS, &status);
    if (status != 1) {
        // If it did not compile then write the syntax error message out to a text
        // file for review.
        OutputShaderErrorMessage(shader.vertexShader, vsFilename);
        return false;
    }

    // Check to see if the fragment shader compiled successfully.
    glGetShaderiv(shader.fragmentShader, GL_COMPILE_STATUS, &status);
    if (status != 1) {
        // If it did not compile then write the syntax error message out to a text
        // file for review.
        OutputShaderErrorMessage(shader.fragmentShader, fsFilename);
        return false;
    }

    // Create a shader program object.
    shader.shaderProgram = CreateProgram();

    // Attach the vertex and fragment shader to the program object.
    AttachShaders(shader.shaderProgram, shader.vertexShader, shader.fragmentShader);

    // ToDo, this should be a function ptr or smth we send to this
    for (int i = 0; i < variableLength; i++) {
        BindAttribLocation(shader.shaderProgram, i, variables[i]);
    }

    LinkProgram(shader.shaderProgram);

    GetProgramiv(shader.shaderProgram, GL_LINK_STATUS, &status);

    if (status != 1) {
        OutputLinkerErrorMessage(shader.shaderProgram);
        return false;
    }

    return true;
}

void ShutdownShaders(uint shaderProgram, uint *shaders, int length) {
    // Detach the vertex and fragment shaders from the program.
    for (int i = 0; i < length; i++) {
        DetachShader(shaderProgram, shaders[i]);
        DeleteShader(shaders[i]);
    }
    DeleteProgram(shaderProgram);
}

bool SetShaderParameters(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix) {

    float tpWorldMatrix[16], tpViewMatrix[16], tpProjectionMatrix[16];
    int location;

    // Transpose the matrices to prepare them for the shader.
    MatrixTranspose(tpWorldMatrix, worldMatrix);
    MatrixTranspose(tpViewMatrix, viewMatrix);
    MatrixTranspose(tpProjectionMatrix, projectionMatrix);

    // Install the shader program as part of the current rendering state.
    UseProgram(shader.shaderProgram);

    // Set the world matrix in the vertex shader.
    location = GetUniformLocation(shader.shaderProgram, "worldMatrix");
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpWorldMatrix);

    // Set the view matrix in the vertex shader.
    location = GetUniformLocation(shader.shaderProgram, "viewMatrix");
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpViewMatrix);

    // Set the projection matrix in the vertex shader.
    location = GetUniformLocation(shader.shaderProgram, "projectionMatrix");
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, tpProjectionMatrix);

    location = GetUniformLocation(shader.shaderProgram, "shaderTexture");
    if (location == -1) {
        return false;
    }

    glUniform1i(location, 0);

    return true;
}
