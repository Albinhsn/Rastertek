#ifndef TEXTURESHADER_H
#define TEXTURESHADER_H
#include "opengl.h"
#include "utils.h"

struct TextureShader {
    uint vertexShader;
    uint fragmentShader;
    uint shaderProgram;
};

bool InitializeTextureShader(TextureShader *);
void Shutdown(TextureShader *);
bool SetShaderParameters(TextureShader *textureShader, float *, float *, float *);
bool InitializeShader(TextureShader *textureShader, char *, char *);
void ShutdownShader();

#endif
