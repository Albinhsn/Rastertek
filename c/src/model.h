#ifndef MODEL_H
#define MODEL_H

#include "opengl.h"
#include "texture.h"
struct VertexType {
    float x, y, z;
    float tu, tv;
    float nx, ny, nz;
};

struct Model {
    int vertexCount, indexCount;
    unsigned int vertexArrayId, vertexBufferId, indexBufferId;
    Texture *texture;
    VertexType *model;
};

bool InitializeModel(Model *model, char *, char *, bool);
void ShutdownModel(Model *model);
void RenderModel(Model *model);

bool InitializeBuffers(Model *model);
void ShutdownBuffers();
void RenderBuffers();

bool LoadTexture(char *, bool);
void ReleaseTexture();

#endif
