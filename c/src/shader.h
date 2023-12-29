#include "utils.h"
#include "vector.h"

struct Shader {
    uint vertexShader;
    uint fragmentShader;
    uint shaderProgram;
};

bool InitializeShader(Shader &shader, const char *vsFilename, const char *fsFilename, const char **variables,
                      int variableLength);
void ShutdownShader(uint shaderProgram, uint *shaders, int length);
bool SetShaderParameters(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                         float *lightDirection, float * diffuseLightColor);
bool SetShaderParameters5(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix);
bool SetShaderParameters6(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                         float *lightDirection, float *diffuseLightColor);
