#include "text.h"
#include "model.h"
#include <string.h>

bool UpdateText(m_Font &font, Text text, const char *text_seq, int positionX, int positionY, float red, float green,
                float blue) {
    int numLetters;
    VertexType *vertices;
    float drawX, drawY;
    void *dataPtr;

    // Store the color of the sentence.
    text.pixelColor[0] = red;
    text.pixelColor[1] = green;
    text.pixelColor[2] = blue;
    text.pixelColor[3] = 1.0f;

    // Get the number of letters in the sentence.
    numLetters = (int)strlen(text_seq);

    // Check for possible buffer overflow.
    if (numLetters > text.maxLength) {
        return false;
    }

    // Create the vertex array.
    vertices = new VertexType[text.vertexCount];

    // Initialize vertex array to zeros at first.
    memset(vertices, 0, (sizeof(VertexType) * text.vertexCount));

    // Calculate the X and Y pixel position on the screen to start drawing to.
    drawX = (float)(((text.screenWidth / 2) * -1) + positionX);
    drawY = (float)((text.screenHeight / 2) - positionY);

    // Use the font class to build the vertex array from the sentence text and sentence draw location.
    BuildVertexArray(font, (void *)vertices, text_seq, drawX, drawY);

    // Bind the vertex buffer.
    glBindBuffer(GL_ARRAY_BUFFER, text.vertexBufferId);

    // Get a pointer to the buffer's actual location in memory.
    dataPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    // Copy the vertex data into memory.
    memcpy(dataPtr, vertices, text.vertexCount * sizeof(VertexType));

    // Unlock the vertex buffer.
    glUnmapBuffer(GL_ARRAY_BUFFER);

    // Release the vertex array as it is no longer needed.
    delete[] vertices;
    vertices = 0;

    return true;
}

bool InitializeTextBuffers(Text &text, const char *text_seq, m_Font *font, int positionX, int positionY, float red,
                           float green, float blue) {
    VertexType *vertices;
    unsigned int *indices;
    int i;
    bool result;

    // Set the vertex and index count.
    text.vertexCount = 6 * text.maxLength;
    text.indexCount = text.vertexCount;

    // Create the vertex array.
    vertices = new VertexType[text.vertexCount];

    // Create the index array.
    indices = new unsigned int[text.indexCount];

    // Initialize vertex array to zeros at first.
    memset(vertices, 0, (sizeof(VertexType) * text.vertexCount));

    // Initialize the index array.
    for (i = 0; i < text.indexCount; i++) {
        indices[i] = i;
    }

    // Allocate an OpenGL vertex array object.
    glGenVertexArrays(1, &text.vertexArrayId);

    // Bind the vertex array object to store all the buffers and vertex attributes we create here.
    glBindVertexArray(text.vertexArrayId);

    // Generate an ID for the vertex buffer.
    glGenBuffers(1, &text.vertexBufferId);

    // Bind the vertex buffer and load the vertex data into the vertex buffer.  Set gpu hint to dynamic since it will
    // change once in a while.
    glBindBuffer(GL_ARRAY_BUFFER, text.vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, text.vertexCount * sizeof(VertexType), vertices, GL_DYNAMIC_DRAW);

    // Enable the two vertex array attributes.
    glEnableVertexAttribArray(0); // Vertex position.
    glEnableVertexAttribArray(1); // Texture coordinates.

    // Specify the location and format of the position portion of the vertex buffer.
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);

    // Specify the location and format of the texture coordinate portion of the vertex buffer.
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType), (unsigned char *)NULL + (3 * sizeof(float)));

    // Generate an ID for the index buffer.
    glGenBuffers(1, &text.indexBufferId);

    // Bind the index buffer and load the index data into it.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, text.indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, text.indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // Release the vertex and index arrays as they are no longer needed.
    delete[] vertices;
    vertices = 0;

    delete[] indices;
    indices = 0;

    // Now add the text data to the sentence buffers.
    result = UpdateText(*font, text, text_seq, positionX, positionY, red, green, blue);
    if (!result) {
        return false;
    }

    return true;
}
bool InitializeText(Text &text, int screenWidth, int screenHeight, int maxLength, m_Font *font, const char *text_seq,
                    int positionX, int positionY, float red, float green, float blue) {

    text.screenWidth = screenWidth;
    text.screenHeight = screenHeight;

    text.maxLength = maxLength;
    text.pixelColor[0] = red;
    text.pixelColor[1] = green;
    text.pixelColor[2] = blue;
    text.pixelColor[3] = 1.0f;

    bool result = InitializeTextBuffers(text, text_seq, font, positionX, positionY, red, green, blue);
    if (!result) {
        return false;
    }
    return true;
}

void ShutdownTextBuffers(Text &text) {
    // Disable the two vertex array attributes.
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Release the vertex buffer.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &text.vertexBufferId);

    // Release the index buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &text.indexBufferId);

    // Release the vertex array object.
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &text.vertexArrayId);
}

void RenderTextBuffers(Text text) {
    // Bind the vertex array object that stored all the information about the vertex and index buffers.
    glBindVertexArray(text.vertexArrayId);

    // Render the vertex buffer using the index buffer.
    glDrawElements(GL_TRIANGLES, text.indexCount, GL_UNSIGNED_INT, 0);
}
void RenderText(Text text) { RenderTextBuffers(text); }

void ShutdownText(Text &text) { ShutdownTextBuffers(text); }
