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
bool SetShaderParameters(Shader shader, float *, float *, float *);
