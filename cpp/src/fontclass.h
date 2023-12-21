#ifndef FONTCLASS_H
#define FONTCLASS_H

#include <fstream>

using namespace std;

#include "textureclass.h"

class FontClass {
private:
  struct FontType {
    float left, right;
    int size;
  };
  struct VertexType {
    float x, y, z;
    float tu, tv;
  };

public:
  FontClass();
  FontClass(const FontClass &);
  ~FontClass();

  bool Initialize(OpenGLClass *, int);;
  void Shutdown();

  void BuildVertexArray(void *, char *, float, float);

  int GetSentencePixelLength(char*);
  int GetFontHeight();

  void SetTexture();

private:
  bool LoadFontData(char*);
  void ReleaseFontData();
  bool LoadTexture(char*);
  void ReleaseTexture();

private:
  OpenGLClass * m_OpenGLPtr;
  FontType * m_Font;
  TextureClass * m_Texture;

  float m_fontHeight;
  int m_spaceSize;
};

#endif
