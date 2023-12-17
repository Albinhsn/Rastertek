#ifndef MODELCLASS_H
#define MODELCLASS_H

#include <fstream>

using namespace std;

#include "textureclass.h"

class ModelClass {
private:
  struct VertexType {
    float x, y, z;
    float tu, tv;
  };

public:
  ModelClass();
  ModelClass(const ModelClass &);
  ~ModelClass();

  bool Initialize(OpenGLClass *, char *, bool);
  void Shutdown();
  void Render();

private:
  bool InitializeBuffers();
  void ShutdownBuffers();
  void RenderBuffers();

  bool LoadTexture(char *, bool);
  void ReleaseTexture();

private:
  OpenGLClass *m_OpenGLPtr;
  int m_vertexCount, m_indexCount;
  unsigned int m_vertexArrayId, m_vertexBufferId, m_indexBufferId;

  TextureClass *m_Texture;
};

#endif
