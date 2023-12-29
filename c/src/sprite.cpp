#include "sprite.h"
#include "model.h"
#include "string.h"
#include "texture.h"

bool InitializeSpriteBuffers(Sprite &sprite) {
    VertexType *vertices;
    uint *indices;
    sprite.prevPosX = -1;
    sprite.prevPosY = -1;

    sprite.vertexCount = 6;
    sprite.indexCount = 6;

    vertices = new VertexType[6];
    indices = new uint[6];

    memset(vertices, 0, sizeof(VertexType) * sprite.vertexCount);

    for (int i = 0; i < 6; i++) {
        indices[i] = i;
    }
    // Allocate an OpenGL vertex array object.
    glGenVertexArrays(1, &sprite.vertexArrayId);

    // Bind the vertex array object to store all the buffers and vertex attributes we create here.
    glBindVertexArray(sprite.vertexArrayId);

    // Generate an ID for the vertex buffer.
    glGenBuffers(1, &sprite.vertexBufferId);

    // Bind the vertex buffer and load the vertex data into the vertex buffer.  Set gpu hint to dynamic since it will
    // change once in a while.
    glBindBuffer(GL_ARRAY_BUFFER, sprite.vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sprite.vertexCount * sizeof(VertexType), vertices, GL_DYNAMIC_DRAW);

    // Enable the two vertex array attributes.
    glEnableVertexAttribArray(0); // Vertex position.
    glEnableVertexAttribArray(1); // Texture coordinates.

    // Specify the location and format of the position portion of the vertex buffer.
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);

    // Specify the location and format of the texture coordinate portion of the vertex buffer.
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType), (unsigned char *)NULL + (3 * sizeof(float)));

    // Generate an ID for the index buffer.
    glGenBuffers(1, &sprite.indexBufferId);

    // Bind the index buffer and load the index data into it.  Leave it static since the indices won't change, only the
    // vertices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite.indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sprite.indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // Now that the buffers have been loaded we can release the array data.
    delete[] vertices;
    vertices = 0;

    delete[] indices;
    indices = 0;

    return true;
}
void ShutdownSpriteBuffers(Sprite &sprite) {
    // Disable the two vertex array attributes.
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Release the vertex buffer.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &sprite.vertexBufferId);

    // Release the index buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &sprite.indexBufferId);

    // Release the vertex array object.
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &sprite.vertexArrayId);
}

bool LoadSpriteTexture(Sprite &sprite, const char *filename) {
    char textureFilename[128];
    ifstream fin;
    int i, j;
    char input;
    bool result;

    // Open the sprite info data file.
    fin.open(filename);
    if (fin.fail()) {
        printf("Failed to open file '%s'\n", filename);
        return false;
    }

    // Read in the number of textures.
    fin >> sprite.textureCount;

    // Create and initialize the texture array with the texture count from the file.
    sprite.textures = new Texture[sprite.textureCount];

    // Read to start of next line.
    fin.get(input);

    // Read in each texture file name.
    for (i = 0; i < sprite.textureCount; i++) {
        j = 0;
        fin.get(input);
        while (input != '\n') {
            textureFilename[j] = input;
            j++;
            fin.get(input);
        }
        textureFilename[j] = '\0';

        // Once you have the filename then load the texture in the texture array.
        result = InitializeTexture(&sprite.textures[i], textureFilename, 0, false);
        if (!result) {
            printf("Failed to initialize texture '%s'\n", textureFilename);
            return false;
        }
    }

    // Read in the cycle time.
    fin >> sprite.cycleTime;

    // Close the file.
    fin.close();

    // Get the dimensions of the first texture and use that as the dimensions of the 2D sprite images.
    sprite.bitmapWidth = sprite.textures[0].width;
    sprite.bitmapHeight = sprite.textures[0].height;

    // Set the starting texture in the cycle to be the first one in the list.
    sprite.currentTexture = 0;

    return true;
}

bool InitializeSprite(Sprite &sprite, int screenWidth, int screenHeight, int renderX, int renderY,
                      const char *spriteFilename) {

    bool result;

    sprite.screenWidth = screenWidth;
    sprite.screenHeight = screenHeight;
    sprite.renderX = renderX;
    sprite.renderY = renderY;
    sprite.frameTime = 0;

    result = InitializeSpriteBuffers(sprite);
    if (!result) {
        printf("ERROR: failed to InitializeSpriteBuffers\n");
        return false;
    }

    result = LoadSpriteTexture(sprite, spriteFilename);
    if (!result) {
        printf("ERROR: failed to LoadSpriteTexture\n");
        return false;
    }

    return true;
}

void ShutdownSprite(Sprite &sprite) {

    for (int i = 0; i < sprite.textureCount; i++) {
        ShutdownTexture(&sprite.textures[i]);
    }
    free(sprite.textures);
    ShutdownSpriteBuffers(sprite);
}

void UpdateSprite(Sprite &sprite, int frameTime) {
    sprite.frameTime += frameTime;
    if (sprite.frameTime > sprite.cycleTime) {
        sprite.frameTime -= sprite.cycleTime;

        sprite.currentTexture++;

        if (sprite.currentTexture == sprite.textureCount) {
            sprite.currentTexture = 0;
        }
    }
}
void UpdateSpriteBuffers(Sprite &sprite) {
    VertexType *vertices;
    void *dataPtr;
    float left, right, top, bottom;

    // If the position we are rendering this sprite to hasn't changed then don't update the vertex buffer.
    if ((sprite.prevPosX == sprite.renderX) && (sprite.prevPosY == sprite.renderY)) {
        return;
    }

    // If the rendering location has changed then store the new position and update the vertex buffer.
    sprite.prevPosX = sprite.renderX;
    sprite.prevPosY = sprite.renderY;

    // Create the vertex array.
    vertices = new VertexType[sprite.vertexCount];

    // Calculate the screen coordinates of the left side of the sprite.
    left = (float)((sprite.screenWidth / 2) * -1) + (float)sprite.renderX;

    // Calculate the screen coordinates of the right side of the sprite.
    right = left + (float)sprite.bitmapWidth;

    // Calculate the screen coordinates of the top of the sprite.
    top = (float)(sprite.screenHeight / 2) - (float)sprite.renderY;

    // Calculate the screen coordinates of the bottom of the sprite.
    bottom = top - (float)sprite.bitmapHeight;

    // Load the vertex array with data.

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

    // Bind the vertex buffer.
    glBindBuffer(GL_ARRAY_BUFFER, sprite.vertexBufferId);

    // Get a pointer to the buffer's actual location in memory.
    dataPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    // Copy the vertex data into memory.
    memcpy(dataPtr, vertices, sprite.vertexCount * sizeof(VertexType));

    // Unlock the vertex buffer.
    glUnmapBuffer(GL_ARRAY_BUFFER);

    // Now that the vertex buffer has been loaded we can release the array data.
    delete[] vertices;
    vertices = 0;
}
void RenderSpriteBuffers(Sprite &sprite) {
    // Bind the vertex array object that stored all the information about the vertex and index buffers.
    glBindVertexArray(sprite.vertexArrayId);

    // Render the vertex buffer using the index buffer.
    glDrawElements(GL_TRIANGLES, sprite.indexCount, GL_UNSIGNED_INT, 0);
}

void RenderSprite(Sprite &sprite) {
    UpdateSpriteBuffers(sprite);
    SetTexture(&sprite.textures[sprite.currentTexture]);
    RenderSpriteBuffers(sprite);
}
