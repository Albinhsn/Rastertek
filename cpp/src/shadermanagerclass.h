#ifndef SHADERMANAGERCLASS_H
#define SHADERMANAGERCLASS_H

#include "lightshaderclass.h"
#include "normalmapshaderclass.h"
#include "textureshaderclass.h"

class ShaderManagerClass {
public:
  ShaderManagerClass();
  ShaderManagerClass(const ShaderManagerClass &);
  ~ShaderManagerClass();

  bool Initialize(OpenGLClass *);
  void Shutdown();

  bool RenderTextureShader(float *, float *, float *);
  bool RenderLightShader(float *, float *, float *, float *, float *);
  bool RenderNormalMapShader(float *, float *, float *, float *, float *);

private:
  TextureShaderClass *m_TextureShader;
  LightShaderClass *m_LightShader;
  NormalMapShaderClass *m_NormalMapShader;
};

#endif
