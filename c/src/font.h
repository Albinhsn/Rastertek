#ifndef FONT_H
#define FONT_H

#include <fstream>
using namespace std;

#include "texture.h"

struct FontType {
    float left, right;
    int size;
};
struct m_Font {
    FontType *type;
    Texture *texture;
    float height;
    int spaceSize;
};

int GetSentencePixelLength(m_Font &font, char *sentence);

void BuildVertexArray(m_Font &font, void *vertices, const char *sentence, float drawX, float drawY);
bool LoadFontData(m_Font &font, const char *filename);
bool LoadTexture(m_Font &font, const char *fileName);
bool InitializeFont(m_Font &font, int fontChoice);
void ShutdownFont(m_Font &font);

#endif
