#ifndef TEXTURE_H
#define TEXTURE_H

#include "opengl.h"

struct Texture {
        unsigned int textureUnit, textureId;
        int width, height;
        bool loaded;
};

bool LoadTarga(Texture *texture, char *filename, bool wrap);
bool InitializeTexture(Texture *texture, char *filename, unsigned int textureUnit, bool wrap);
void ShutdownTexture(Texture *texture);
void SetTexture(Texture *texture);

#endif
