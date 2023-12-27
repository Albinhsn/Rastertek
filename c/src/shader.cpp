#include "shader.h"

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
    textureShader->vertexShader = CreateShader(GL_VERTEX_SHADER);
    textureShader->fragmentShader = CreateShader(GL_FRAGMENT_SHADER);

    // Copy the shader source code strings into the vertex and fragment shader
    // objects.
    glShaderSource(textureShader->vertexShader, vertexShaderBuffer);
    glShaderSource(textureShader->fragmentShader, fragmentShaderBuffer);

    // Release the vertex and fragment shader buffers.
    delete[] vertexShaderBuffer;
    vertexShaderBuffer = 0;

    delete[] fragmentShaderBuffer;
    fragmentShaderBuffer = 0;

    // Compile the shaders.
    glCompileShader(textureShader->vertexShader);
    glCompileShader(textureShader->fragmentShader);

    // Check to see if the vertex shader compiled successfully.
    glGetShaderiv(textureShader->vertexShader, GL_COMPILE_STATUS, &status);
    if (status != 1) {
        // If it did not compile then write the syntax error message out to a text
        // file for review.
        OutputShaderErrorMessage(textureShader->vertexShader, vsFilename);
        return false;
    }

    // Check to see if the fragment shader compiled successfully.
    glGetShaderiv(textureShader->fragmentShader, GL_COMPILE_STATUS, &status);
    if (status != 1) {
        // If it did not compile then write the syntax error message out to a text
        // file for review.
        OutputShaderErrorMessage(textureShader->fragmentShader, fsFilename);
        return false;
    }

    // Create a shader program object.
    textureShader->shaderProgram = CreateProgram();

    // Attach the vertex and fragment shader to the program object.
    AttachShaders(textureShader->shaderProgram, textureShader->vertexShader, textureShader->fragmentShader);

    // ToDo, this should be a function ptr or smth we send to this
    const char *inputPositionStr = "inputPosition";
    const char *inputTexCoordStr = "inputTexCoord";

    BindAttribLocation(textureShader->shaderProgram, 0, inputPositionStr);
    BindAttribLocation(textureShader->shaderProgram, 1, inputTexCoordStr);

    LinkProgram(textureShader->shaderProgram);

    GetProgramiv(textureShader->shaderProgram, GL_LINK_STATUS, &status);

    if (status != 1) {
        OutputLinkerErrorMessage(textureShader->shaderProgram);
        return false;
    }

    return true;
}
