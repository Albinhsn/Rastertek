#ifndef TEXTURE_H
#define TEXTURE_H

struct Texture {
        unsigned int textureUnit, textureId;
        int width, height;
        bool loaded;
};

#endif
