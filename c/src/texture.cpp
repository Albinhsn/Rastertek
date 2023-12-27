#include "texture.h"
#include "opengl.h"
#include "utils.h"
#include <stdio.h>

bool LoadTarga32Bit(Texture *texture, char *filename, bool wrap) {

    TargaHeader targaFileHeader;
    FILE *filePtr;
    int bpp, error, index, i, j;
    unsigned long count, imageSize;
    unsigned char *targaData;
    unsigned char *targaImage;

    // Open the targa file for reading in binary.
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        printf("ERROR: file doesn't exist %s\n", filename);
        return false;
    }

    // Read in the file header.
    count = fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);
    if (count != 1) {
        printf("ERROR: Failed to read into header\n");
        return false;
    }

    // Get the important information from the header.
    texture->width = (int)targaFileHeader.width;
    texture->height = (int)targaFileHeader.height;
    bpp = (int)targaFileHeader.bpp;

    // Check that it is 32 bit and not 24 bit.
    if (bpp != 32) {
        printf("ERROR: bpp isn't 32 but %d\n", bpp);
        return false;
    }

    // Calculate the size of the 32 bit image data.
    imageSize = texture->width * texture->height * 4;

    // Allocate memory for the targa image data.
    targaImage = new unsigned char[imageSize];

    // Read in the targa image data.
    count = fread(targaImage, 1, imageSize, filePtr);
    if (count != imageSize) {
        printf("ERROR: count read doesn't equal imageSize\n");
        return false;
    }

    error = fclose(filePtr);
    if (error != 0) {
        return false;
    }

    targaData = new unsigned char[imageSize];
    index = 0;
    for (j = 0; j < texture->height; j++) {
        for (i = 0; i < texture->width; i++) {
            targaData[index] = targaImage[index + 2];     // Red
            targaData[index + 1] = targaImage[index + 1]; // Green
            targaData[index + 2] = targaImage[index];     // Blue
            targaData[index + 3] = targaImage[index + 3]; // Blue

            index += 4;
        }
    }

    delete[] targaImage;
    targaImage = 0;

    glActiveTexture(GL_TEXTURE + texture->textureUnit);

    glGenTextures(1, &texture->textureId);
    glBindTexture(GL_TEXTURE_2D, texture->textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, targaData);

    if (wrap) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    delete[] targaData;
    targaData = 0;

    return true;
}

bool InitializeTexture(Texture *texture, char *filename, unsigned int textureUnit, bool wrap) {
    texture->textureUnit = textureUnit;
    bool result = LoadTarga32Bit(texture, filename, wrap);
    if (!result) {
        printf("ERROR: failed to load targa32bit\n");
        return false;
    }
    texture->loaded = true;
    return true;
}

void ShutdownTexture(Texture *texture) {
    if (texture->loaded) {
        glDeleteTextures(1, &texture->textureId);
        texture->loaded = false;
    }
}

void SetTexture(Texture *texture) {
    if (texture->loaded) {
        glActiveTexture(GL_TEXTURE0 + texture->textureUnit);

        glBindTexture(GL_TEXTURE_2D, texture->textureId);
    }
}
