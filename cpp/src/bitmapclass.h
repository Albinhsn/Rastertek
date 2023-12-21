#ifndef BITMAPCLASS_H
#define BITMAPCLASS_H

#include <fstream>

using namespace std;

#include "textureclass.h"

class BitmapClass {
private:
  struct VertexType {
    float x, y, z;
    float tu, tv;
  };

public:
  BitmapClass();
  BitmapClass(const BitmapClass &);
  ~BitmapClass();

  bool Initialize(OpenGLClass *, int, int, char *, int, int);
  void Shutdown();
  void Render();

  void SetRenderLocation(int, int);

private:
  bool InitializeBuffers();
  void ShutdownBuffers();
  void RenderBuffers();
  bool UpdateBuffers();

  bool LoadTexture(char *);
  void ReleaseTexture();

  bool LoadModel(char *);
  void ReleaseModel();

private:
  OpenGLClass *m_OpenGLPtr;
  int m_vertexCount, m_indexCount, m_screenWidth, m_screenHeight, m_bitmapWidth,
      m_bitmapHeight, m_renderX, m_renderY, m_prevPosX, m_prevPosY;
  unsigned int m_vertexArrayId, m_vertexBufferId, m_indexBufferId;

  TextureClass *m_Texture;
};

#endif
