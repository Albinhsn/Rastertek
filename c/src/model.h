#ifndef MODEL_H
#define MODEL_H

#include "opengl.h"
#include "texture.h"
struct VertexType {
    float x, y, z;
    float tu, tv;
};
struct VertexTypeN {
    float x, y, z;
    float tu, tv;
    float nx, ny, nz;
};

struct Model {
    int attribLen;
    int vertexCount, indexCount;
    unsigned int vertexArrayId, vertexBufferId, indexBufferId;
    Texture *texture;
    VertexTypeN *model;
};

bool InitializeModel(Model *model, const char **models, int modelLen, const char **textures, int textureLen, bool wrap,
                     void (*enableAttribPtr)(void), int attribLen);
void ShutdownModel(Model *model);
void RenderModel(Model *model);

bool InitializeBuffers(Model *model, void (*enableAttribPtr)(void));
void ShutdownBuffers();
void RenderBuffers();

bool LoadTexture(Model *model, const char *textureFilename, bool wrap);
void ReleaseTexture();

#endif
