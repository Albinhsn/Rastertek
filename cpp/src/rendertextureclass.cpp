#include "rendertextureclass.h"

RenderTextureClass::RenderTextureClass() { m_OpenGLPtr = 0; }
RenderTextureClass::RenderTextureClass(const RenderTextureClass &other) {}
RenderTextureClass::~RenderTextureClass() {}

bool RenderTextureClass::Initialize(OpenGLClass *OpenGL, int textureWidth,
                                    int textureHeight, float screenNear,
                                    float screenDepth, int format,
                                    unsigned int textureUnit) {
  int textureFormat;
  unsigned int drawBuffersArray[1];
  float fieldOfView, screenAspect;

  m_OpenGLPtr = OpenGL;

  m_textureWidth = textureWidth;
  m_textureHeight = textureHeight;

  m_textureUnit = textureUnit;
  switch (format) {
  case 0: {
    textureFormat = GL_RGBA;
    break;
  }
  default: {
    textureFormat = GL_RGBA;
    break;
  }
  }

  m_OpenGLPtr->glGenFramebuffers(1, &m_frameBufferId);
  m_OpenGLPtr->glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);

  m_OpenGLPtr->glActiveTexture(GL_TEXTURE0 + m_textureUnit);

  glGenTextures(1, &m_textureID);
  glBindTexture(GL_TEXTURE_2D, m_textureID);

  glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, m_textureWidth, m_textureHeight,
               0, textureFormat, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  m_OpenGLPtr->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                      GL_TEXTURE_2D, m_textureID, 0);

  m_OpenGLPtr->glGenRenderbuffers(1, &m_depthBufferId);
  m_OpenGLPtr->glBindRenderbuffer(GL_RENDERBUFFER, m_depthBufferId);

  m_OpenGLPtr->glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
                                     m_textureWidth, m_textureHeight);

  m_OpenGLPtr->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                         GL_RENDERBUFFER, m_depthBufferId);

  drawBuffersArray[0] = GL_COLOR_ATTACHMENT0;
  m_OpenGLPtr->glDrawBuffers(1, drawBuffersArray);

  m_OpenGLPtr->glBindFramebuffer(GL_FRAMEBUFFER, 0);

  fieldOfView = 3.14159265358979323846f / 4.0f;
  screenAspect = (float)m_textureWidth / (float)m_textureHeight;
  m_OpenGLPtr->BuildPerspectiveFovMatrix(m_projectionMatrix, fieldOfView,
                                         screenAspect, screenNear, screenDepth);

  m_OpenGLPtr->BuildOrthoMatrix(m_orthoMatrix, (float)m_textureWidth,
                                (float)m_textureHeight, screenNear,
                                screenDepth);

  return true;
}
void RenderTextureClass::Shutdown() {
  // Release the depth buffer.
  m_OpenGLPtr->glDeleteRenderbuffers(1, &m_depthBufferId);

  // Release the texture.
  glDeleteTextures(1, &m_textureID);

  // Release the frame buffer.
  m_OpenGLPtr->glDeleteFramebuffers(1, &m_frameBufferId);

  // Release the pointer to the OpenGL object.
  m_OpenGLPtr = 0;

  return;
}
void RenderTextureClass::SetRenderTarget() {
  // Set the frame buffer (and its attached texture and depth buffer) as the
  // render target.
  m_OpenGLPtr->glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);

  // Set the viewport to be the correct dimensions for the texture dimensions
  // used.
  glViewport(0, 0, m_textureWidth, m_textureHeight);

  return;
}
void RenderTextureClass::ClearRenderTarget(float red, float green, float blue,
                                           float alpha) {
  // Clear the back buffer.
  glClearColor(red, green, blue, alpha);

  // Clear the depth buffer.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  return;
}

void RenderTextureClass::SetTexture() {
  m_OpenGLPtr->glActiveTexture(GL_TEXTURE0 + m_textureUnit);

  glBindTexture(GL_TEXTURE_2D, m_textureID);
}
int RenderTextureClass::GetTextureWidth() { return m_textureWidth; }

int RenderTextureClass::GetTextureHeight() { return m_textureHeight; }

void RenderTextureClass::GetProjectionMatrix(float *matrix) {
  matrix[0] = m_projectionMatrix[0];
  matrix[1] = m_projectionMatrix[1];
  matrix[2] = m_projectionMatrix[2];
  matrix[3] = m_projectionMatrix[3];

  matrix[4] = m_projectionMatrix[4];
  matrix[5] = m_projectionMatrix[5];
  matrix[6] = m_projectionMatrix[6];
  matrix[7] = m_projectionMatrix[7];

  matrix[8] = m_projectionMatrix[8];
  matrix[9] = m_projectionMatrix[9];
  matrix[10] = m_projectionMatrix[10];
  matrix[11] = m_projectionMatrix[11];

  matrix[12] = m_projectionMatrix[12];
  matrix[13] = m_projectionMatrix[13];
  matrix[14] = m_projectionMatrix[14];
  matrix[15] = m_projectionMatrix[15];

  return;
}

void RenderTextureClass::GetOrthoMatrix(float *matrix) {
  matrix[0] = m_orthoMatrix[0];
  matrix[1] = m_orthoMatrix[1];
  matrix[2] = m_orthoMatrix[2];
  matrix[3] = m_orthoMatrix[3];

  matrix[4] = m_orthoMatrix[4];
  matrix[5] = m_orthoMatrix[5];
  matrix[6] = m_orthoMatrix[6];
  matrix[7] = m_orthoMatrix[7];

  matrix[8] = m_orthoMatrix[8];
  matrix[9] = m_orthoMatrix[9];
  matrix[10] = m_orthoMatrix[10];
  matrix[11] = m_orthoMatrix[11];

  matrix[12] = m_orthoMatrix[12];
  matrix[13] = m_orthoMatrix[13];
  matrix[14] = m_orthoMatrix[14];
  matrix[15] = m_orthoMatrix[15];

  return;
}
