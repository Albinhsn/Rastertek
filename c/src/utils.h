#ifndef UTILS_H
#define UTILS_H

#define PI 3.14159265358979323846f

#include "math.h"
#include "opengl.h"

struct TargaHeader {
    unsigned char data1[12];
    unsigned short width;
    unsigned short height;
    unsigned char bpp;
    unsigned char data2;
};

char *ReadFile(const char *filename);
void OutputShaderErrorMessage(unsigned int shaderId, const char *shaderFilename);
void OutputLinkerErrorMessage(unsigned int programId);

#endif
