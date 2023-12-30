#include "font.h"
#include "model.h"
#include <string.h>
int GetSentencePixelLength(m_Font &font, char *sentence) {
    int pixelLength, numLetters, i, letter;

    pixelLength = 0;
    numLetters = (int)strlen(sentence);

    for (i = 0; i < numLetters; i++) {
        letter = ((int)sentence[i]) - 32;

        // If the letter is a space then count it as three pixels.
        if (letter == 0) {
            pixelLength += font.spaceSize;
        } else {
            pixelLength += (font.type[letter].size + 1);
        }
    }

    return pixelLength;
}

void BuildVertexArray(m_Font &font, void *vertices, const char *sentence, float drawX, float drawY) {
    VertexType *vertexPtr;
    int numLetters, index, i, letter;

    // Coerce the input vertices into a VertexType structure.
    vertexPtr = (VertexType *)vertices;

    // Get the number of letters in the sentence.
    numLetters = (int)strlen(sentence);

    // Initialize the index to the vertex array.
    index = 0;

    // Draw each letter onto a quad.
    for (i = 0; i < numLetters; i++) {
        letter = ((int)sentence[i]) - 32;

        // If the letter is a space then just move over three pixels.
        if (letter == 0) {
            drawX = drawX + (float)font.spaceSize;
        } else {
            // First triangle in quad.
            vertexPtr[index].x = drawX; // Top left.
            vertexPtr[index].y = drawY;
            vertexPtr[index].z = 0.0f;
            vertexPtr[index].tu = font.type[letter].left;
            vertexPtr[index].tv = 1.0f;
            index++;

            vertexPtr[index].x = drawX + font.type[letter].size; // Bottom right.
            vertexPtr[index].y = drawY - font.height;
            vertexPtr[index].z = 0.0f;
            vertexPtr[index].tu = font.type[letter].right;
            vertexPtr[index].tv = 0.0f;
            index++;

            vertexPtr[index].x = drawX; // Bottom left.
            vertexPtr[index].y = drawY - font.height;
            vertexPtr[index].z = 0.0f;
            vertexPtr[index].tu = font.type[letter].left;
            vertexPtr[index].tv = 0.0f;
            index++;

            // Second triangle in quad.
            vertexPtr[index].x = drawX; // Top left.
            vertexPtr[index].y = drawY;
            vertexPtr[index].z = 0.0f;
            vertexPtr[index].tu = font.type[letter].left;
            vertexPtr[index].tv = 1.0f;
            index++;

            vertexPtr[index].x = drawX + font.type[letter].size; // Top right.
            vertexPtr[index].y = drawY;
            vertexPtr[index].z = 0.0f;
            vertexPtr[index].tu = font.type[letter].right;
            vertexPtr[index].tv = 1.0f;
            index++;

            vertexPtr[index].x = drawX + font.type[letter].size; // Bottom right.
            vertexPtr[index].y = drawY - font.height;
            vertexPtr[index].z = 0.0f;
            vertexPtr[index].tu = font.type[letter].right;
            vertexPtr[index].tv = 0.0f;
            index++;

            // Update the x location for drawing by the size of the letter and one pixel.
            drawX = drawX + font.type[letter].size + 1.0f;
        }
    }
}
bool LoadFontData(m_Font &font, const char *filename) {
    ifstream fin;
    int i;
    char temp;
    // Create the font spacing buffer.
    font.type = new FontType[95];

    // Read in the font size and spacing between chars.
    fin.open(filename);
    if (fin.fail()) {
        return false;
    }

    // Read in the 95 used ascii characters for text.
    for (i = 0; i < 95; i++) {
        fin.get(temp);
        while (temp != ' ') {
            fin.get(temp);
        }
        fin.get(temp);
        while (temp != ' ') {
            fin.get(temp);
        }

        fin >> font.type[i].left;
        fin >> font.type[i].right;
        fin >> font.type[i].size;
    }

    // Close the file.
    fin.close();

    return true;
}
bool LoadTexture(m_Font &font, const char *fileName) {
    bool result;

    // Create and initialize the font texture object.
    font.texture = (Texture *)malloc(sizeof(Texture));

    result = InitializeTexture(font.texture, fileName, 0, false);
    if (!result) {
        return false;
    }

    return true;
}
bool InitializeFont(m_Font &font, int fontChoice) {
    const char *fontFilename;
    const char *fontTextureFilename;
    bool result;

    switch (fontChoice) {
    case 0: {
        fontFilename = "./data/font01.txt";
        fontTextureFilename = "./data/font01.tga";
        font.height = 32.0f;
        font.spaceSize = 3;
        break;
    }
    default: {
        fontFilename = "./data/font01.txt";
        fontTextureFilename = "./data/font01.tga";
        font.height = 32.0f;
        font.spaceSize = 3;
        break;
    }
    }
    result = LoadFontData(font, fontFilename);
    if (!result) {
        printf("Failed to load font data at '%s'\n", fontFilename);
        return false;
    }

    result = LoadTexture(font, fontTextureFilename);
    if (!result) {
        printf("Failed to load font texture at '%s'\n", fontTextureFilename);
        return false;
    }

    return true;
}
void ShutdownFont(m_Font &font) { ShutdownTexture(font.texture); }
