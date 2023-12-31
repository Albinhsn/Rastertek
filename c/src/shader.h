#include "utils.h"
#include "vector.h"

struct Shader {
    uint vertexShader;
    uint fragmentShader;
    uint program;
};

bool InitializeShader(Shader &shader, const char *vsFilename, const char *fsFilename, const char **variables,
                      int variableLength);
void ShutdownShader(uint shaderProgram, uint *shaders, int length);
bool SetShaderParameters(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                         float *lightDirection, float *diffuseLightColor);
bool SetShaderParameters9(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                          float *lightDirection, float *diffuseLightColor, float *ambientLight);
bool SetShaderParameters5(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix);
bool SetShaderParameters6(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                          float *lightDirection, float *diffuseLightColor);
bool SetShaderParameters10(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                           float *lightDirection, float *diffuseLightColor, float *ambientLight, float *cameraPosition,
                           float *specularColor, float specularPower);
bool SetShaderParameters11(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                           float *diffuseColorArray, float *lightPositionArray, int numLights);
bool SetShaderParameters12(Shader shader, float *worldMatrix, float *viewMatrix, float *orthoMatrix);
bool SetShaderParameters14(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                           float *pixelColor);
bool SetTextShaderParameters(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix,
                             float *pixelColor);
bool SetShaderParameters17(Shader shader, float *worldMatrix, float *viewMatrix, float *projectionMatrix);
