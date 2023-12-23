#ifndef RENDERTEXTURECLASS_H
#define RENDERTEXTURECLASS_H

#include "openglclass.h"

class RenderTextureClass {

public:
  RenderTextureClass();
  RenderTextureClass(const RenderTextureClass &);
  ~RenderTextureClass();

  bool Initialize(OpenGLClass *, int, int, float, float, int, unsigned int);
  void Shutdown();

  void SetRenderTarget();
  void ClearRenderTarget(float, float, float, float);
  void SetTexture();


  int GetTextureWidth();
  int GetTextureHeight();

  void GetProjectionMatrix(float *);
  void GetOrthoMatrix(float*);

private:
  OpenGLClass * m_OpenGLPtr;
  int m_textureWidth, m_textureHeight;
  unsigned int m_textureUnit, m_frameBufferId, m_textureID, m_depthBufferId;
  float m_projectionMatrix[16], m_orthoMatrix[16];
};

#endif
