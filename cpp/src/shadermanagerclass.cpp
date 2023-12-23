#include "shadermanagerclass.h"

ShaderManagerClass::ShaderManagerClass() {
  m_TextureShader = 0;
  m_LightShader = 0;
  m_NormalMapShader = 0;
}

ShaderManagerClass::~ShaderManagerClass() {}
ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass &other) {}

bool ShaderManagerClass::Initialize(OpenGLClass *OpenGL) {
  bool result;

  m_TextureShader = new TextureShaderClass;

  result = m_TextureShader->Initialize(OpenGL);
  if (!result) {
    return false;
  }

  m_LightShader = new LightShaderClass;
  result = m_LightShader->Initialize(OpenGL);
  if (!result) {
    return false;
  }

  m_NormalMapShader = new NormalMapShaderClass;
  result = m_NormalMapShader->Initialize(OpenGL);
  if (!result) {
    return false;
  }

  return true;
}

void ShaderManagerClass::Shutdown() {
  if (m_NormalMapShader) {
    m_NormalMapShader->Shutdown();
    delete m_NormalMapShader;
    m_NormalMapShader = 0;
  }

  // Release the light shader object.
  if (m_LightShader) {
    m_LightShader->Shutdown();
    delete m_LightShader;
    m_LightShader = 0;
  }

  // Release the texture shader object.
  if (m_TextureShader) {
    m_TextureShader->Shutdown();
    delete m_TextureShader;
    m_TextureShader = 0;
  }
}

bool ShaderManagerClass::RenderTextureShader(float *worldMatrix,
                                             float *viewMatrix,
                                             float *projectionMatrix) {
  return m_TextureShader->SetShaderParameters(worldMatrix, viewMatrix,
                                              projectionMatrix);
}

bool ShaderManagerClass::RenderLightShader(float *worldMatrix,
                                           float *viewMatrix,
                                           float *projectionMatrix,
                                           float *lightDirection,
                                           float *diffuseLightColor) {
  return m_LightShader->SetShaderParameters(worldMatrix, viewMatrix,
                                            projectionMatrix, lightDirection,
                                            diffuseLightColor);
}

bool ShaderManagerClass::RenderNormalMapShader(float *worldMatrix,
                                               float *viewMatrix,
                                               float *projectionMatrix,
                                               float *lightDirection,
                                               float *diffuseLightColor) {
  return m_NormalMapShader->SetShaderParameters(
      worldMatrix, viewMatrix, projectionMatrix, lightDirection,
      diffuseLightColor);
}
