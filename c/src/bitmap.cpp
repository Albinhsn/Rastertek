#include "bitmap.h"
#include "model.h"
#include "opengl.h"
#include "texture.h"
#include <cstdlib>
#include <string.h>

void resizeBitmap(Bitmap &bitmap, int height, int width) {
    bitmap.bitmapHeight = height;
    bitmap.bitmapWidth = width;
}

void UpdateBitmapBuffer(Bitmap &bitmap) {
    resizeBitmap(bitmap, 150, 150);
    if (bitmap.prevPosX == bitmap.renderX && bitmap.prevPosY == bitmap.renderY) {
        return;
    }
    bitmap.prevPosX = bitmap.renderX;
    bitmap.prevPosY = bitmap.renderY;

    VertexType *vertices = new VertexType[bitmap.vertexCount];

    float left = (float)((bitmap.screenWidth / 2) * -1) + (float)bitmap.renderX;
    float right = left + (float)bitmap.bitmapWidth;
    float top = (float)(bitmap.screenHeight / 2) - (float)bitmap.renderY;
    float bottom = top - (float)bitmap.bitmapHeight;

    // First triangle.
    vertices[0].x = left; // Top left.
    vertices[0].y = top;
    vertices[0].z = 0.0f;
    vertices[0].tu = 0.0f;
    vertices[0].tv = 1.0f;

    vertices[1].x = right; // Bottom right.
    vertices[1].y = bottom;
    vertices[1].z = 0.0f;
    vertices[1].tu = 1.0f;
    vertices[1].tv = 0.0f;

    vertices[2].x = left; // Bottom left.
    vertices[2].y = bottom;
    vertices[2].z = 0.0f;
    vertices[2].tu = 0.0f;
    vertices[2].tv = 0.0f;

    // Second triangle.
    vertices[3].x = left; // Top left.
    vertices[3].y = top;
    vertices[3].z = 0.0f;
    vertices[3].tu = 0.0f;
    vertices[3].tv = 1.0f;

    vertices[4].x = right; // Top right.
    vertices[4].y = top;
    vertices[4].z = 0.0f;
    vertices[4].tu = 1.0f;
    vertices[4].tv = 1.0f;

    vertices[5].x = right; // Bottom right.
    vertices[5].y = bottom;
    vertices[5].z = 0.0f;
    vertices[5].tu = 1.0f;
    vertices[5].tv = 0.0f;

    glBindBuffer(GL_ARRAY_BUFFER, bitmap.vertexBufferId);

    void *dataPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(dataPtr, vertices, bitmap.vertexCount * sizeof(VertexType));
    glUnmapBuffer(GL_ARRAY_BUFFER);

    delete[] vertices;
    vertices = 0;
}

bool InitializeBitmapBuffers(Bitmap &bitmap) {
    VertexType *vertices;
    unsigned int *indices;
    int i;

    bitmap.prevPosX = -1;
    bitmap.prevPosY = -1;
    bitmap.vertexCount = 6;
    bitmap.indexCount = 6;

    vertices = new VertexType[bitmap.vertexCount];
    indices = new unsigned int[bitmap.vertexCount];
    memset(vertices, 0, (sizeof(VertexType) * bitmap.vertexCount));

    // Load the index array with data.
    for (i = 0; i < bitmap.vertexCount; i++) {
        indices[i] = i;
    }

    // Allocate an OpenGL vertex array object.
    glGenVertexArrays(1, &bitmap.vertexArrayId);

    // Bind the vertex array object to store all the buffers and vertex attributes we create here.
    glBindVertexArray(bitmap.vertexArrayId);

    // Generate an ID for the vertex buffer.
    glGenBuffers(1, &bitmap.vertexBufferId);

    // Bind the vertex buffer and load the vertex data into the vertex buffer.  Set gpu hint to dynamic since it
    // will change once in a while.
    glBindBuffer(GL_ARRAY_BUFFER, bitmap.vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, bitmap.vertexCount * sizeof(VertexType), vertices, GL_DYNAMIC_DRAW);

    // Enable the two vertex array attributes.
    glEnableVertexAttribArray(0); // Vertex position.
    glEnableVertexAttribArray(1); // Texture coordinates.

    // Specify the location and format of the position portion of the vertex buffer.
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);

    // Specify the location and format of the texture coordinate portion of the vertex buffer.
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType), (unsigned char *)NULL + (3 * sizeof(float)));

    // Generate an ID for the index buffer.
    glGenBuffers(1, &bitmap.indexBufferId);

    // Bind the index buffer and load the index data into it.  Leave it static since the indices won't change, only the
    // vertices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bitmap.indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bitmap.indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // Now that the buffers have been loaded we can release the array data.
    delete[] vertices;
    vertices = 0;

    delete[] indices;
    indices = 0;

    return true;
}
bool LoadBitmapTexture(Bitmap &bitmap, const char *textureFilename) {
    bitmap.texture = (Texture *)malloc(sizeof(Texture));
    bool result = InitializeTexture(bitmap.texture, textureFilename, 0, false);
    if (!result) {
        return false;
    }
    bitmap.bitmapWidth = bitmap.texture->width;
    bitmap.bitmapHeight = bitmap.texture->height;

    return true;
}
bool InitializeBitmap(Bitmap &bitmap, int screenWidth, int screenHeight, const char *textureFilename, int renderX,
                      int renderY) {
    bitmap.screenWidth = screenWidth;
    bitmap.screenHeight = screenHeight;
    bitmap.renderX = renderX;
    bitmap.renderY = renderY;

    if (!InitializeBitmapBuffers(bitmap)) {
        printf("ERROR: failed to initialize bitmap buffers\n");
    }
    if (!LoadBitmapTexture(bitmap, textureFilename)) {
        printf("ERROR: failed to initialize bitmap buffers\n");
    }

    return true;
}
void RenderBitmapBuffers(Bitmap bitmap) {
    glBindVertexArray(bitmap.vertexArrayId);
    glDrawElements(GL_TRIANGLES, bitmap.indexCount, GL_UNSIGNED_INT, 0);
}

void RenderBitmap(Bitmap &bitmap) {
    UpdateBitmapBuffer(bitmap);

    SetTexture(bitmap.texture);

    RenderBitmapBuffers(bitmap);
}

void ShutdownBitmapBuffers(Bitmap bitmap) {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &bitmap.vertexBufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &bitmap.indexBufferId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &bitmap.vertexArrayId);
}
void ShutdownBitmap(Bitmap *bitmap) {
    ShutdownTexture(bitmap->texture);
    free(bitmap->texture);
}
