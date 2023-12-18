#include "textureshader.h"
#include "utils.h"
#include "vector.h"
#include <cstring>
#include <iostream>

void OutputShaderErrorMessage(OpenGL *openGL, unsigned int shaderId, char *shaderFilename) {
    long count;
    int logSize, error;
    char *infoLog;
    FILE *filePtr;

    // Get the size of the string containing the information log for the failed
    // shader compilation message.
    openGL->glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

    // Increment the size by one to handle also the null terminator.
    logSize++;

    // Create a char buffer to hold the info log.
    infoLog = new char[logSize];

    // Now retrieve the info log.
    openGL->glGetShaderInfoLog(shaderId, logSize, NULL, infoLog);

    // Open a text file to write the error message to.
    filePtr = fopen("shader-error.txt", "w");
    if (filePtr == NULL) {
        std::cout << "Error opening shader error message output file." << std::endl;
        return;
    }

    // Write out the error message.
    count = fwrite(infoLog, sizeof(char), logSize, filePtr);
    if (count != logSize) {
        std::cout << "Error writing shader error message output file." << std::endl;
        return;
    }

    // Close the file.
    error = fclose(filePtr);
    if (error != 0) {
        std::cout << "Error closing shader error message output file." << std::endl;
        return;
    }

    // Notify the user to check the text file for compile errors.
    std::cout << "Error compiling shader.  Check shader-error.txt for error message.  "
                 "Shader filename: "
              << shaderFilename << std::endl;

    return;
}
void OutputLinkerErrorMessage(OpenGL *openGL, unsigned int programId) {
    long count;
    FILE *filePtr;
    int logSize, error;
    char *infoLog;

    // Get the size of the string containing the information log for the failed
    // shader compilation message.
    openGL->glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);

    // Increment the size by one to handle also the null terminator.
    logSize++;

    // Create a char buffer to hold the info log.
    infoLog = new char[logSize];

    // Now retrieve the info log.
    openGL->glGetProgramInfoLog(programId, logSize, NULL, infoLog);

    // Open a file to write the error message to.
    filePtr = fopen("linker-error.txt", "w");
    if (filePtr == NULL) {
        std::cout << "Error opening linker error message output file." << std::endl;
        return;
    }

    // Write out the error message.
    count = fwrite(infoLog, sizeof(char), logSize, filePtr);
    if (count != logSize) {
        std::cout << "Error writing linker error message output file." << std::endl;
        return;
    }

    // Close the file.
    error = fclose(filePtr);
    if (error != 0) {
        std::cout << "Error closing linker error message output file." << std::endl;
        return;
    }

    // Pop a message up on the screen to notify the user to check the text file
    // for linker errors.
    std::cout << "Error linking shader program.  Check linker-error.txt for message." << std::endl;

    return;
}
bool SetShaderParameters(TextureShader *textureShader, float *worldMatrix, float *viewMatrix, float *projectionMatrix) {

    float tpWorldMatrix[16], tpViewMatrix[16], tpProjectionMatrix[16];
    int location;

    // Transpose the matrices to prepare them for the shader.
    MatrixTranspose(tpWorldMatrix, worldMatrix);
    MatrixTranspose(tpViewMatrix, viewMatrix);
    MatrixTranspose(tpProjectionMatrix, projectionMatrix);

    // Install the shader program as part of the current rendering state.
    textureShader->openGL->glUseProgram(textureShader->shaderProgram);

    // Set the world matrix in the vertex shader.
    location = textureShader->openGL->glGetUniformLocation(textureShader->shaderProgram, "worldMatrix");
    if (location == -1) {
        return false;
    }
    textureShader->openGL->glUniformMatrix4fv(location, 1, false, tpWorldMatrix);

    // Set the view matrix in the vertex shader.
    location = textureShader->openGL->glGetUniformLocation(textureShader->shaderProgram, "viewMatrix");
    if (location == -1) {
        return false;
    }
    textureShader->openGL->glUniformMatrix4fv(location, 1, false, tpViewMatrix);

    // Set the projection matrix in the vertex shader.
    location = textureShader->openGL->glGetUniformLocation(textureShader->shaderProgram, "projectionMatrix");
    if (location == -1) {
        return false;
    }
    textureShader->openGL->glUniformMatrix4fv(location, 1, false, tpProjectionMatrix);

    location = textureShader->openGL->glGetUniformLocation(textureShader->shaderProgram, "shaderTexture");
    if (location == -1) {
        return false;
    }

    textureShader->openGL->glUniform1i(location, 0);

    return true;
}
bool InitializeShader(TextureShader *textureShader, char *vsFilename, char *fsFilename) {

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
    textureShader->vertexShader = textureShader->openGL->glCreateShader(GL_VERTEX_SHADER);
    textureShader->fragmentShader = textureShader->openGL->glCreateShader(GL_FRAGMENT_SHADER);

    // Copy the shader source code strings into the vertex and fragment shader
    // objects.
    textureShader->openGL->glShaderSource(textureShader->vertexShader, 1, &vertexShaderBuffer, NULL);
    textureShader->openGL->glShaderSource(textureShader->fragmentShader, 1, &fragmentShaderBuffer, NULL);

    // Release the vertex and fragment shader buffers.
    delete[] vertexShaderBuffer;
    vertexShaderBuffer = 0;

    delete[] fragmentShaderBuffer;
    fragmentShaderBuffer = 0;

    // Compile the shaders.
    textureShader->openGL->glCompileShader(textureShader->vertexShader);
    textureShader->openGL->glCompileShader(textureShader->fragmentShader);

    // Check to see if the vertex shader compiled successfully.
    textureShader->openGL->glGetShaderiv(textureShader->vertexShader, GL_COMPILE_STATUS, &status);
    if (status != 1) {
        // If it did not compile then write the syntax error message out to a text
        // file for review.
        OutputShaderErrorMessage(textureShader->openGL, textureShader->vertexShader, vsFilename);
        return false;
    }

    // Check to see if the fragment shader compiled successfully.
    textureShader->openGL->glGetShaderiv(textureShader->fragmentShader, GL_COMPILE_STATUS, &status);
    if (status != 1) {
        // If it did not compile then write the syntax error message out to a text
        // file for review.
        OutputShaderErrorMessage(textureShader->openGL, textureShader->fragmentShader, fsFilename);
        return false;
    }

    // Create a shader program object.
    textureShader->shaderProgram = textureShader->openGL->glCreateProgram();

    // Attach the vertex and fragment shader to the program object.
    textureShader->openGL->glAttachShader(textureShader->shaderProgram, textureShader->vertexShader);
    textureShader->openGL->glAttachShader(textureShader->shaderProgram, textureShader->fragmentShader);

    textureShader->openGL->glBindAttribLocation(textureShader->shaderProgram, 0, "inputPosition");
    textureShader->openGL->glBindAttribLocation(textureShader->shaderProgram, 1, "inputTexCoord");

    textureShader->openGL->glLinkProgram(textureShader->shaderProgram);

    textureShader->openGL->glGetProgramiv(textureShader->shaderProgram, GL_LINK_STATUS, &status);

    if (status != 1) {
        OutputLinkerErrorMessage(textureShader->openGL, textureShader->shaderProgram);
        return false;
    }

    return true;
}
void ShutdownShader(TextureShader *textureShader) {
    // Detach the vertex and fragment shaders from the program.
    textureShader->openGL->glDetachShader(textureShader->shaderProgram, textureShader->vertexShader);
    textureShader->openGL->glDetachShader(textureShader->shaderProgram, textureShader->fragmentShader);

    // Delete the vertex and fragment shaders.
    textureShader->openGL->glDeleteShader(textureShader->vertexShader);
    textureShader->openGL->glDeleteShader(textureShader->fragmentShader);

    // Delete the shader program.
    textureShader->openGL->glDeleteProgram(textureShader->shaderProgram);
}
void Shutdown(TextureShader *textureShader) {
    ShutdownShader(textureShader);
    textureShader->openGL = 0;
}

bool InitializeTextureShader(TextureShader *textureShader, OpenGL *openGL) {
    char vsFilename[128];
    char psFilename[128];

    bool result;

    textureShader->openGL = openGL;

    strcpy(vsFilename, "./shaders/texture.vs");
    strcpy(psFilename, "./shaders/texture.ps");

    result = InitializeShader(textureShader, vsFilename, psFilename);
    if (!result) {
        return false;
    }

    return true;
}
