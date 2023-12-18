#include "model.h"
#include "texture.h"

#include <stdio.h>

void ReleaseTexture(Model *model) {
    if (model->texture) {
        ShutdownTexture(model->texture);
        free(model->texture);
        model->texture = 0;
    }
}
void ShutdownBuffers(Model *model) {
    model->openGL->glDisableVertexAttribArray(0);
    model->openGL->glDisableVertexAttribArray(1);

    model->openGL->glBindBuffer(GL_ARRAY_BUFFER, 0);
    model->openGL->glDeleteBuffers(1, &model->vertexBufferId);

    model->openGL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    model->openGL->glDeleteBuffers(1, &model->indexBufferId);

    model->openGL->glBindVertexArray(0);
    model->openGL->glDeleteVertexArrays(1, &model->vertexArrayId);

    return;
}

void ShutdownModel(Model *model) {
    ReleaseTexture(model);
    ShutdownBuffers(model);
    model->openGL = 0;
}
bool InitializeBuffers(Model *model) {
    VertexType *vertices;
    unsigned int *indices;

    model->vertexCount = 3;
    model->indexCount = 3;
    model->vertexBufferId = 0;
    model->vertexArrayId = 0;
    model->indexBufferId = 0;

    vertices = new VertexType[model->vertexCount];
    indices = new unsigned int[model->indexCount];

    // Load the vertex array with data.

    // Bottom left.
    vertices[0].x = -1.0f; // Position.
    vertices[0].y = -1.0f;
    vertices[0].z = 0.0f;
    vertices[0].tu = 0.0f; // Texture
    vertices[0].tv = 0.0f;

    // Top middle.
    vertices[1].x = 0.0f; // Position.
    vertices[1].y = 1.0f;
    vertices[1].z = 0.0f;
    vertices[1].tu = 0.5f; // Texture
    vertices[1].tv = 1.0f;

    // Bottom right.
    vertices[2].x = 1.0f; // Position.
    vertices[2].y = -1.0f;
    vertices[2].z = 0.0f;
    vertices[2].tu = 1.0f; // Texture
    vertices[2].tv = 0.0f;

    // Load the index array with data.
    indices[0] = 0; // Bottom left.
    indices[1] = 1; // Top middle.
    indices[2] = 2; // Bottom right.

    model->openGL->glGenVertexArrays(1, &model->vertexArrayId);
    model->openGL->glBindVertexArray(model->vertexArrayId);

    model->openGL->glGenBuffers(1, &model->vertexBufferId);

    model->openGL->glBindBuffer(GL_ARRAY_BUFFER, model->vertexBufferId);
    model->openGL->glBufferData(GL_ARRAY_BUFFER, model->vertexCount * sizeof(VertexType), vertices, GL_STATIC_DRAW);

    model->openGL->glEnableVertexAttribArray(0);
    model->openGL->glEnableVertexAttribArray(1);

    model->openGL->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);

    model->openGL->glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType),
                                         (unsigned char *)NULL + (3 * sizeof(float)));

    model->openGL->glGenBuffers(1, &model->indexBufferId);

    model->openGL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indexBufferId);
    model->openGL->glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indexCount * sizeof(unsigned int), indices,
                                GL_STATIC_DRAW);

    delete[] vertices;
    vertices = 0;

    delete[] indices;
    indices = 0;

    return true;
}
void RenderBuffers(Model *model) {
    model->openGL->glBindVertexArray(model->vertexArrayId);

    glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);

    return;
}

void RenderModel(Model *model) {
    SetTexture(model->texture, model->openGL);
    RenderBuffers(model);
}

bool LoadTexture(Model *model, char *textureFilename, bool wrap) {
    bool result;

    model->texture = (Texture *)malloc(sizeof(Texture));

    result = InitializeTexture(model->texture, model->openGL, textureFilename, 0, wrap);
    if (!result) {
        printf("ERROR: Failed to initialize texture\n");
        return false;
    }

    return true;
}
bool InitializeModel(Model* model, OpenGL *openGL, char *textureFilename, bool wrap) {
    bool result;

    model->openGL = openGL;
    model->texture = 0;

    result = InitializeBuffers(model);

    if (!result) {
        return false;
    }

    result = LoadTexture(model, textureFilename, wrap);

    if (!result) {
        printf("ERROR: Failed to load texture\n");
        return false;
    }

    return true;
}
