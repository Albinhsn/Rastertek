#include "model.h"
#include "math.h"
#include "opengl.h"
#include "texture.h"
#include "vector.h"

#include <cstdlib>
#include <fstream>
#include <stdio.h>
using namespace std;

void ReleaseTexture(Model &model) {
    printf("Releasing texture\n");
    ShutdownTexture(model.texture);
    free(model.texture);
    printf("Released texture\n");
}
void ShutdownBuffers(Model &model) {
    for (int i = 0; i < model.attribLen; i++) {
        glDisableVertexAttribArray(i);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &model.vertexBufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &model.indexBufferId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &model.vertexArrayId);

    return;
}

void ShutdownModel(Model &model) {
    ReleaseTexture(model);
    ShutdownBuffers(model);
}

bool InitializeBuffers(Model &model, void (*enableAttribPtr)(void)) {
    VertexTypeNTB *vertices;
    unsigned int *indices;

    vertices = new VertexTypeNTB[model.vertexCount];
    indices = new unsigned int[model.indexCount];

    for (int i = 0; i < model.vertexCount; i++) {
        vertices[i].x = model.model[i].x;
        vertices[i].y = model.model[i].y;
        vertices[i].z = model.model[i].z;
        vertices[i].tu = model.model[i].tu;
        vertices[i].tv = model.model[i].tv;
        vertices[i].nx = model.model[i].nx;
        vertices[i].ny = model.model[i].ny;
        vertices[i].nz = model.model[i].nz;
        vertices[i].tx = model.model[i].tx;
        vertices[i].ty = model.model[i].ty;
        vertices[i].tz = model.model[i].tz;
        vertices[i].bx = model.model[i].bx;
        vertices[i].by = model.model[i].by;
        vertices[i].bz = model.model[i].bz;

        indices[i] = i;
    }

    glGenVertexArrays(1, &model.vertexArrayId);
    glBindVertexArray(model.vertexArrayId);

    glGenBuffers(1, &model.vertexBufferId);

    glBindBuffer(GL_ARRAY_BUFFER, model.vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, model.vertexCount * sizeof(VertexTypeNTB), vertices, GL_STATIC_DRAW);

    enableAttribPtr();

    glGenBuffers(1, &model.indexBufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    delete[] vertices;
    vertices = 0;

    delete[] indices;
    indices = 0;

    return true;
}
void RenderBuffers(Model &model) {
    glBindVertexArray(model.vertexArrayId);
    glDrawElements(GL_TRIANGLES, model.indexCount, GL_UNSIGNED_INT, 0);
}

void RenderModel(Model &model) {
    for (int i = 0; i < model.textureLen; i++) {
        SetTexture(model.texture[i]);
    }
    RenderBuffers(model);
}

bool LoadModel(Model &model, const char *filename) {
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
    model.model = new VertexTypeNTB[model.vertexCount];

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
void CalculateTangentBinormal(VertexType vertex1, VertexType vertex2, VertexType vertex3, Vector3 &tangent,
                              Vector3 &binormal) {
    float vector1[3], vector2[3];
    float tuVector[2], tvVector[2];
    float den;
    float length;

    // Calculate the two vectors for this face.
    vector1[0] = vertex2.x - vertex1.x;
    vector1[1] = vertex2.y - vertex1.y;
    vector1[2] = vertex2.z - vertex1.z;

    vector2[0] = vertex3.x - vertex1.x;
    vector2[1] = vertex3.y - vertex1.y;
    vector2[2] = vertex3.z - vertex1.z;

    // Calculate the tu and tv texture space vectors.
    tuVector[0] = vertex2.tu - vertex1.tu;
    tvVector[0] = vertex2.tv - vertex1.tv;

    tuVector[1] = vertex3.tu - vertex1.tu;
    tvVector[1] = vertex3.tv - vertex1.tv;

    // Calculate the denominator of the tangent/binormal equation.
    den = 1.0f / (tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0]);

    // Calculate the cross products and multiply by the coefficient to get the tangent and binormal.
    tangent.x = (tvVector[1] * vector1[0] - tvVector[0] * vector2[0]) * den;
    tangent.y = (tvVector[1] * vector1[1] - tvVector[0] * vector2[1]) * den;
    tangent.z = (tvVector[1] * vector1[2] - tvVector[0] * vector2[2]) * den;

    binormal.x = (tuVector[0] * vector2[0] - tuVector[1] * vector1[0]) * den;
    binormal.y = (tuVector[0] * vector2[1] - tuVector[1] * vector1[1]) * den;
    binormal.z = (tuVector[0] * vector2[2] - tuVector[1] * vector1[2]) * den;

    // Calculate the length of this normal.
    length = sqrt((tangent.x * tangent.x) + (tangent.y * tangent.y) + (tangent.z * tangent.z));

    // Normalize the normal and then store it
    tangent.x = tangent.x / length;
    tangent.y = tangent.y / length;
    tangent.z = tangent.z / length;

    // Calculate the length of this normal.
    length = sqrt((binormal.x * binormal.x) + (binormal.y * binormal.y) + (binormal.z * binormal.z));

    // Normalize the normal and then store it
    binormal.x = binormal.x / length;
    binormal.y = binormal.y / length;
    binormal.z = binormal.z / length;
}

void CalculateModelVectors(Model &model) {
    int faceCount, i, index;
    VertexType vertex1, vertex2, vertex3;
    Vector3 tangent, binormal;

    // Calculate the number of faces in the model.
    faceCount = model.vertexCount / 3;

    // Initialize the index to the model data.
    index = 0;

    // Go through all the faces and calculate the the tangent and binormal vectors.
    for (i = 0; i < faceCount; i++) {
        // Get the three vertices for this face from the model.
        vertex1.x = model.model[index].x;
        vertex1.y = model.model[index].y;
        vertex1.z = model.model[index].z;
        vertex1.tu = model.model[index].tu;
        vertex1.tv = model.model[index].tv;
        index++;

        vertex2.x = model.model[index].x;
        vertex2.y = model.model[index].y;
        vertex2.z = model.model[index].z;
        vertex2.tu = model.model[index].tu;
        vertex2.tv = model.model[index].tv;
        index++;

        vertex3.x = model.model[index].x;
        vertex3.y = model.model[index].y;
        vertex3.z = model.model[index].z;
        vertex3.tu = model.model[index].tu;
        vertex3.tv = model.model[index].tv;
        index++;

        // Calculate the tangent and binormal of that face.
        CalculateTangentBinormal(vertex1, vertex2, vertex3, tangent, binormal);

        // Store the tangent and binormal for this face back in the model structure.
        model.model[index - 1].tx = tangent.x;
        model.model[index - 1].ty = tangent.y;
        model.model[index - 1].tz = tangent.z;
        model.model[index - 1].bx = binormal.x;
        model.model[index - 1].by = binormal.y;
        model.model[index - 1].bz = binormal.z;

        model.model[index - 2].tx = tangent.x;
        model.model[index - 2].ty = tangent.y;
        model.model[index - 2].tz = tangent.z;
        model.model[index - 2].bx = binormal.x;
        model.model[index - 2].by = binormal.y;
        model.model[index - 2].bz = binormal.z;

        model.model[index - 3].tx = tangent.x;
        model.model[index - 3].ty = tangent.y;
        model.model[index - 3].tz = tangent.z;
        model.model[index - 3].bx = binormal.x;
        model.model[index - 3].by = binormal.y;
        model.model[index - 3].bz = binormal.z;
    }
}

bool InitializeModel(Model &model, const char *modelStr, const char **textures, int textureLen, bool wrap,
                     void (*enableAttribPtr)(void), int attribLen) {
    bool result;
    model.attribLen = attribLen;
    result = LoadModel(model, modelStr);
    if (!result) {
        printf("ERROR: Failed to load model '%s'\n", modelStr);
        return false;
    }
    CalculateModelVectors(model);

    result = InitializeBuffers(model, enableAttribPtr);

    if (!result) {
        printf("ERROR: Failed to initialize buffers\n");
        return false;
    }

    model.texture = (Texture *)malloc(sizeof(Texture) * textureLen);
    model.textureLen = textureLen;

    for (int i = 0; i < textureLen; i++) {
        result = InitializeTexture(model.texture[i], textures[i], i, wrap);
        if (!result) {
            printf("ERROR: Failed to initialize texture\n");
            return false;
        }
    }

    return true;
}
