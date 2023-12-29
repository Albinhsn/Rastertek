#include "model.h"
#include "opengl.h"
#include "texture.h"

#include <cstdlib>
#include <fstream>
#include <stdio.h>
using namespace std;

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
// ToDo Should take pointer to bindAttribFunc?
bool InitializeBuffers(Model *model) {
    VertexType *vertices;
    unsigned int *indices;

    vertices = new VertexType[model->vertexCount];
    indices = new unsigned int[model->indexCount];

    // Load the vertex array with data.

    for (int i = 0; i < model->vertexCount; i++) {
        vertices[i].x = model->model[i].x;
        vertices[i].y = model->model[i].y;
        vertices[i].z = model->model[i].z;
        vertices[i].tu = model->model[i].tu;
        vertices[i].tv = model->model[i].tv;
        vertices[i].nx = model->model[i].nx;
        vertices[i].ny = model->model[i].ny;
        vertices[i].nz = model->model[i].nz;

        indices[i] = i;
    }

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
bool LoadModel(Model &model, char *filename) {
    ifstream fin;
    char input;
    int i;

    // Open the model file.
    fin.open(filename);

    // If it could not open the file then exit.
    if (fin.fail()) {
        return false;
    }

    // Read up to the value of vertex count.
    fin.get(input);
    while (input != ':') {
        fin.get(input);
    }

    // Read in the vertex count.
    fin >> model.vertexCount;

    // Set the number of indices to be the same as the vertex count.
    model.indexCount = model.vertexCount;

    // Create the model using the vertex count that was read in.
    model.model = new VertexType[model.vertexCount];

    // Read up to the beginning of the data.
    fin.get(input);
    while (input != ':') {
        fin.get(input);
    }
    fin.get(input);
    fin.get(input);

    // Read in the vertex data.
    for (i = 0; i < model.vertexCount; i++) {
        fin >> model.model[i].x >> model.model[i].y >> model.model[i].z;
        fin >> model.model[i].tu >> model.model[i].tv;
        fin >> model.model[i].nx >> model.model[i].ny >> model.model[i].nz;

        // Invert the V coordinate to match the OpenGL texture coordinate system.
        model.model[i].tv = 1.0f - model.model[i].tv;
    }

    // Close the model file.
    fin.close();

    return true;
}
bool InitializeModel(Model *model, char *modelFilename, char *textureFilename, bool wrap) {
    bool result;

    result = LoadModel(*model, modelFilename);
    if (!result) {
        return false;
    }

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
