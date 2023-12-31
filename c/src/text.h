#ifndef TEXT_H
#define TEXT_H

#include "font.h"
#include <sys/types.h>
struct Text {
    int screenWidth, screenHeight, maxLength, vertexCount, indexCount;
    uint vertexArrayId, vertexBufferId, indexBufferId;
    float pixelColor[4];
};
bool UpdateText(m_Font &font, Text text, const char *text_seq, int positionX, int positionY, float red, float green,
                float blue);

    bool InitializeTextBuffers(Text & text, char *text_seq, m_Font *font, int positionX, int positionY, float red,
                               float green, float blue);
    bool InitializeText(Text & text, int screenWidth, int screenHeight, int maxLength, m_Font *font,
                        const char *text_seq, int positionX, int positionY, float red, float green, float blue);

    void ShutdownTextBuffers(Text & text);

    void RenderTextBuffers(Text text);
    void RenderText(Text text);

    void ShutdownText(Text & text);

#endif
