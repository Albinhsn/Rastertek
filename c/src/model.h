#ifndef MODEL_H
#define MODEL_H

#include "opengl.h"
#include "texture.h"
struct VertexType {
    float x, y, z;
    float tu, tv;
};
struct VertexTypeNTB{
    float x, y, z;
    float tu, tv;
    float nx, ny, nz;
    float tx, ty, tz;
    float bx, by, bz;

};

struct Model {
    int attribLen;
    int vertexCount, indexCount;
    unsigned int vertexArrayId, vertexBufferId, indexBufferId;
    Texture *texture;
    int textureLen;
    VertexTypeNTB *model;
};

bool InitializeModel(Model &model, const char *modelStr, const char **textures, int textureLen, bool wrap,
                     void (*enableAttribPtr)(void), int attribLen);
void ShutdownModel(Model &model);
void RenderModel(Model &model);

bool InitializeBuffers(Model &model, void (*enableAttribPtr)(void));
void ShutdownBuffers();
void RenderBuffers();

bool LoadTextures(Model &model, const char *textureFilenames, int textureLen, bool wrap);

void CalculateModelVectors(Model & model);

#endif
