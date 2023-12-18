#ifndef TEXTURESHADER_H
#define TEXTURESHADER_H
#include "opengl.h"

struct TextureShader {
    OpenGL *openGL;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
};

bool InitializeTextureShader(TextureShader*, OpenGL*);
void Shutdown(TextureShader*);
bool SetShaderParameters(TextureShader *textureShader, float*, float*, float*);
bool InitializeShader(TextureShader *textureShader, char*, char*);
void ShutdownShader();
void OutputShaderErrorMessage(OpenGL *openGL, unsigned int shaderId, char *shaderFilename);
void OutputLinkerErrorMessage(OpenGL *openGL, unsigned int programId);

#endif
