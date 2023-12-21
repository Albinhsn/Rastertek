#ifndef TEXTCLASS_H
#define TEXTCLASS_H

#include "fontclass.h"

class TextClass {

private:
  struct VertexType {
    float x, y, z;
    float tu, tv;
  };

public:
  TextClass();
  ~TextClass();
  TextClass(const TextClass &);

  bool Initialize(OpenGLClass *, int, int, int, FontClass *, char *, int, int,
                  float, float, float);
  void Shutdown();
  void Render();

  bool UpdateText(FontClass *, char *, int, int, float, float, float);
  void GetPixelColor(float *);

private:
  bool InitializeBuffers(FontClass *, char *, int, int, float, float, float);
  void ShutdownBuffers();
  void RenderBuffers();
private:
  OpenGLClass * m_OpenGLPtr;
  int m_screenWidth, m_screenHeight, m_maxLength, m_vertexCount, m_indexCount;
  unsigned int m_vertexArrayId, m_vertexBufferId, m_indexBufferId;

  float m_pixelColor[4];
};

#endif
