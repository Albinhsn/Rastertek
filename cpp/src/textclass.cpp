#include "textclass.h"

TextClass::TextClass() {}
TextClass::~TextClass() {}
TextClass::TextClass(const TextClass &) {}

bool TextClass::Initialize(OpenGLClass *OpenGL, int screenWidth,
                           int screenHeight, int maxLength, FontClass *Font,
                           char *text, int positionX, int positionY, float red,
                           float green, float blue) {
  bool result;
  m_OpenGLPtr = OpenGL;

  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;

  m_maxLength = maxLength;

  result =
      InitializeBuffers(Font, text, positionX, positionY, red, green, blue);
  if (!result) {
    return false;
  }

  return true;
}

void TextClass::Shutdown() {
  ShutdownBuffers();

  m_OpenGLPtr = 0;
}

void TextClass::Render() { RenderBuffers(); }

bool TextClass::InitializeBuffers(FontClass *Font, char *text, int positionX,
                                  int positionY, float red, float green,
                                  float blue) {
  VertexType *vertices;
  unsigned int *indices;
  int i;
  bool result;

  m_vertexCount = 6 * m_maxLength;
  m_indexCount = m_vertexCount;

  vertices = new VertexType[m_vertexCount];

  indices = new unsigned int[m_indexCount];

  memset(vertices, 0, sizeof(VertexType) * m_vertexCount);
  for (i = 0; i < m_indexCount; i++) {
    indices[i] = i;
  }

  m_OpenGLPtr->glGenVertexArrays(1, &m_vertexArrayId);

  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  m_OpenGLPtr->glGenBuffers(1, &m_vertexBufferId);

  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
  m_OpenGLPtr->glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(VertexType),
                            vertices, GL_DYNAMIC_DRAW);

  m_OpenGLPtr->glEnableVertexAttribArray(0);
  m_OpenGLPtr->glEnableVertexAttribArray(1);

  m_OpenGLPtr->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType),
                                     0);
  m_OpenGLPtr->glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType),
                                     (unsigned char *)NULL +
                                         (3 * sizeof(float)));

  m_OpenGLPtr->glGenBuffers(1, &m_indexBufferId);

  m_OpenGLPtr->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
  m_OpenGLPtr->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                            m_indexCount * sizeof(unsigned int), indices,
                            GL_STATIC_DRAW);

  delete[] vertices;
  vertices = 0;

  delete[] indices;
  indices = 0;

  result = UpdateText(Font, text, positionX, positionY, red, green, blue);
  if (!result) {
    return false;
  }

  return true;
}

void TextClass::ShutdownBuffers() {
  m_OpenGLPtr->glDisableVertexAttribArray(0);
  m_OpenGLPtr->glDisableVertexAttribArray(1);

  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_OpenGLPtr->glDeleteBuffers(1, &m_vertexBufferId);

  m_OpenGLPtr->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_OpenGLPtr->glDeleteBuffers(1, &m_indexBufferId);

  m_OpenGLPtr->glBindVertexArray(0);
  m_OpenGLPtr->glDeleteVertexArrays(1, &m_vertexArrayId);
}

bool TextClass::UpdateText(FontClass *Font, char *text, int positionX,
                           int positionY, float red, float green, float blue) {
  int numLetters;
  VertexType *vertices;
  float drawX, drawY;
  void *dataPtr;

  m_pixelColor[0] = red;
  m_pixelColor[1] = green;
  m_pixelColor[2] = blue;
  m_pixelColor[3] = 1.0f;

  numLetters = (int)strlen(text);
  if (numLetters > m_maxLength) {
    return false;
  }

  vertices = new VertexType[m_vertexCount];

  memset(vertices, 0, sizeof(VertexType) * m_vertexCount);

  drawX = (float)(((m_screenWidth / 2) * -1) + positionX);
  drawY = (float)((m_screenHeight / 2) - positionY);

  Font->BuildVertexArray((void *)vertices, text, drawX, drawY);

  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);

  dataPtr = m_OpenGLPtr->glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

  memcpy(dataPtr, vertices, m_vertexCount * sizeof(VertexType));

  m_OpenGLPtr->glUnmapBuffer(GL_ARRAY_BUFFER);

  delete[] vertices;
  vertices = 0;
  return true;
}

void TextClass::RenderBuffers() {
  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
}

void TextClass::GetPixelColor(float *color) {
  color[0] = m_pixelColor[0];
  color[1] = m_pixelColor[1];
  color[2] = m_pixelColor[2];
  color[3] = m_pixelColor[3];
}
