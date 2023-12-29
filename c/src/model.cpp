#include "model.h"
#include "opengl.h"
#include "texture.h"

#include <cstdlib>
#include <stdio.h>

void ReleaseTexture(Model *model) {
    if (model->texture) {
        ShutdownTexture(model->texture);
        free(model->texture);
        model->texture = 0;
    }
}
void ShutdownBuffers(Model *model) {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &model->vertexBufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &model->indexBufferId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &model->vertexArrayId);

    return;
}

void ShutdownModel(Model *model) {
    ReleaseTexture(model);
    ShutdownBuffers(model);
}
bool InitializeBuffers(Model *model) {
    VertexType *vertices;
    unsigned int *indices;

    model->vertexCount = 6;
    model->indexCount = 6;

    vertices = new VertexType[model->vertexCount];
    indices = new unsigned int[model->indexCount];

    // Load the vertex array with data.

    // Bottom left.
    vertices[0].x = -1.0f; // Position.
    vertices[0].y = -1.0f;
    vertices[0].z = 0.0f;
    vertices[0].tu = 0.0f; // Texture
    vertices[0].tv = 0.0f;
    vertices[0].nx = 0.0f; // Normal.
    vertices[0].ny = 0.0f;
    vertices[0].nz = -1.0f;

    // Top middle.
    vertices[1].x = 0.0f; // Position.
    vertices[1].y = 1.0f;
    vertices[1].z = 0.0f;
    vertices[1].tu = 0.5f; // Texture
    vertices[1].tv = 1.0f;
    vertices[1].nx = 0.0f; // Normal.
    vertices[1].ny = 0.0f;
    vertices[1].nz = -1.0f;

    // Bottom right.
    vertices[2].x = 1.0f; // Position.
    vertices[2].y = -1.0f;
    vertices[2].z = 0.0f;
    vertices[2].tu = 1.0f; // Texture
    vertices[2].tv = 0.0f;
    vertices[2].nx = 0.0f; // Normal.
    vertices[2].ny = 0.0f;
    vertices[2].nz = -1.0f;

    // Load the index array with data.
    indices[0] = 0; // Bottom left.
    indices[1] = 1; // Top middle.
    indices[2] = 2; // Bottom right.
    indices[3] = 3; // Bottom left.
    indices[4] = 4; // Bottom left.
    indices[5] = 5; // Bottom left.

    glGenVertexArrays(1, &model->vertexArrayId);
    glBindVertexArray(model->vertexArrayId);

    glGenBuffers(1, &model->vertexBufferId);

    glBindBuffer(GL_ARRAY_BUFFER, model->vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, model->vertexCount * sizeof(VertexType), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexType), (unsigned char *)NULL + (5 * sizeof(float)));

    glGenBuffers(1, &model->indexBufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    delete[] vertices;
    vertices = 0;

    delete[] indices;
    indices = 0;

    return true;
}
void RenderBuffers(Model *model) {
    glBindVertexArray(model->vertexArrayId);
    glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);
}

void RenderModel(Model *model) {
    SetTexture(model->texture);
    RenderBuffers(model);
}

bool LoadTexture(Model *model, char *textureFilename, bool wrap) {
    bool result;

    model->texture = (Texture *)malloc(sizeof(Texture));

    result = InitializeTexture(model->texture, textureFilename, 0, wrap);
    if (!result) {
        printf("ERROR: Failed to initialize texture\n");
        return false;
    }

    return true;
}
bool InitializeModel(Model *model, char *textureFilename, bool wrap) {
    bool result;

    result = InitializeBuffers(model);

    if (!result) {
        printf("ERROR: Failed to initialize buffers\n");
        return false;
    }

    result = LoadTexture(model, textureFilename, wrap);

    if (!result) {
        printf("ERROR: Failed to load texture\n");
        return false;
    }

    return true;
}
