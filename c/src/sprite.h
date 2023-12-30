#ifndef SPRITE_H
#define SPRITE_H

#include <fstream>
using namespace std;

#include "texture.h"

struct Sprite {
    int vertexCount, indexCount, screenWidth, screenHeight, bitmapWidth, bitmapHeight, renderX, renderY, prevPosX,
        prevPosY;
    uint vertexArrayId, vertexBufferId, indexBufferId;
    Texture *textures;

    int textureCount, currentTexture, cycleTime, frameTime;
};
bool InitializeSpriteBuffers(Sprite &sprite);
bool InitializeSprite(Sprite &sprite, int screenWidth, int screenHeight, int renderX, int renderY,
                      const char *spriteFilename);
bool LoadSpriteTexture(Sprite &sprite, char *filename);

void ShutdownSprite(Sprite &sprite);
void ShutdownSpriteBuffers(Sprite &sprite);

void UpdateSprite(Sprite &sprite, int frameTime);
void UpdateSpriteBuffers(Sprite &sprite);

void RenderSpriteBuffers(Sprite &sprite);
void RenderSprite(Sprite &sprite);

#endif
