#ifndef UTILS_H
#define UTILS_H

#define PI 3.14159265358979323846f

#include "opengl.h"
#include "math.h"

// Read targa 32 bit file
struct TargaHeader {
    unsigned char data1[12];
    unsigned short width;
    unsigned short height;
    unsigned char bpp;
    unsigned char data2;
};

// read file?
char *ReadFile(char *filename);
void OutputShaderErrorMessage(unsigned int shaderId, char * shaderFilename);
void OutputLinkerErrorMessage(unsigned int programId);

#endif
