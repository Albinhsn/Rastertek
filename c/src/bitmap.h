#ifndef BITMAP_H
#define BITMAP_H

#include "texture.h"
#include <stdio.h>

struct Bitmap {
    Texture *texture;
    int vertexCount, indexCount, screenWidth, screenHeight, bitmapWidth, bitmapHeight, renderX, renderY, prevPosX,
        prevPosY;
    uint vertexArrayId, vertexBufferId, indexBufferId;
};
void UpdateBitmapBuffer(Bitmap &bitmap);

bool InitializeBitmapBuffers(Bitmap &bitmap);
bool LoadBitmapTexture(Bitmap &bitmap, const char *textureFilename);
bool InitializeBitmap(Bitmap &bitmap, int screenWidth, int screenHeight, const char *textureFilename, int renderX,
                      int renderY);
void RenderBitmapBuffers(Bitmap bitmap);
void RenderBitmap(Bitmap &bitmap);
void ShutdownBitmapBuffers(Bitmap bitmap);
void ShutdownBitmap(Bitmap *bitmap);

#endif
