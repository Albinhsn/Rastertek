#ifndef UTILS_H
#define UTILS_H

#define PI 3.14159265358979323846f

#include "math.h"

// Read targa 32 bit file
struct TargaHeader {
        unsigned char data1[12];
        unsigned short width;
        unsigned short height;
        unsigned char bpp;
        unsigned char data2;
};

unsigned char *load_targa_file(char *filename);

// read file?
char *read_file(char *filename);

#endif
