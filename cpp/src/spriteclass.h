#ifndef SPRITECLASS_H
#define SPRITECLASS_H


#include <fstream>
#include "textureclass.h"

using namespace std;

class SpriteClass{
private:
  struct VertexType{
    float x, y, z;
    float tu, tv;

};

public:
  SpriteClass();
  SpriteClass(const SpriteClass &);
  ~SpriteClass();

  bool Initialize(OpenGLClass *, int, int, int, int, char *);
  void Shutdown();
  void Render();
  void Update(int);
  void SetRenderLocation(int, int);
  bool InitializeBuffers();
  void ShutdownBuffers();
  bool UpdateBuffers();
  void RenderBuffers();

  bool LoadTextures(char*);
  void ReleaseTextures();
  void SetTexture();
private:
  OpenGLClass * m_OpenGLPtr;
  int m_vertexCount, m_indexCount, m_screenWidth, m_screenHeight, m_bitmapWidth, m_bitmapHeight, m_renderX, m_renderY, m_prevPosX, m_prevPosY;
  unsigned int m_vertexArrayId, m_vertexBufferId, m_indexBufferId;

  TextureClass * m_Textures;
  int m_textureCount, m_currentTexture, m_cycleTime, m_frameTime;
  
};

#endif
