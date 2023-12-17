#ifndef TEXTURECLASS_H
#define TEXTURECLASS_H

#include <stdio.h>

#include "openglclass.h"

class TextureClass {
private:
  struct TargaHeader {
    unsigned char data1[12];
    unsigned short width;
    unsigned short height;
    unsigned char bpp;
    unsigned char data2;
  };

public:
  TextureClass();
  TextureClass(const TextureClass&);
  ~TextureClass();

  bool Initialize(OpenGLClass*, char*, unsigned int, bool);
  void Shutdown();
  void SetTexture(OpenGLClass*);

  int GetWidth();
  int GetHeight();

private:
  bool LoadTarga32Bit(OpenGLClass*, char*, bool);
private:
  unsigned int m_textureUnit, m_textureId;
  int m_width, m_height;
  bool m_loaded;
};

#endif
