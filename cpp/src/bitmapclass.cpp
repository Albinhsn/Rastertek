#include "bitmapclass.h"

BitmapClass::BitmapClass() {
  m_OpenGLPtr = 0;
  m_Texture = 0;
}

BitmapClass::BitmapClass(const BitmapClass &other) {}

BitmapClass::~BitmapClass() {}

bool BitmapClass::Initialize(OpenGLClass *OpenGL, int screenWidth,
                             int screenHeight, char *textureFilename,
                             int renderX, int renderY) {
  bool result;

  m_OpenGLPtr = OpenGL;

  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;

  m_renderX = renderX;
  m_renderY = renderY;

  result = InitializeBuffers();
  if (!result) {
    return false;
  }

  result = LoadTexture(textureFilename);
  if (!result) {
    return false;
  }

  return true;
}

void BitmapClass::Shutdown() {
  ReleaseTexture();
  ShutdownBuffers();

  m_OpenGLPtr = 0;
}

void BitmapClass::Render() {
  UpdateBuffers();
  m_Texture->SetTexture(m_OpenGLPtr);

  RenderBuffers();
}

bool BitmapClass::InitializeBuffers() {
  VertexType *vertices;
  unsigned int *indices;

  int i;

  m_prevPosX = -1;
  m_prevPosY = -1;

  m_vertexCount = 6;
  m_indexCount = m_vertexCount;

  vertices = new VertexType[m_vertexCount];
  indices = new unsigned int[m_indexCount];

  memset(vertices, 0, sizeof(VertexType) * m_vertexCount);

  for (i = 0; i < m_indexCount; ++i) {
    indices[i] = i;
  }
  m_OpenGLPtr->glGenVertexArrays(1, &m_vertexArrayId);
  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  m_OpenGLPtr->glGenBuffers(1, &m_vertexBufferId);

  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
  m_OpenGLPtr->glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(VertexType),
                            vertices, GL_DYNAMIC_DRAW);

  m_OpenGLPtr->glEnableVertexAttribArray(0);
  m_OpenGLPtr->glEnableVertexAttribArray(1);

  m_OpenGLPtr->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType),
                                     0);
  m_OpenGLPtr->glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType),
                                     (unsigned char *)NULL +
                                         (3 * sizeof(float)));

  m_OpenGLPtr->glGenBuffers(1, &m_indexBufferId);

  m_OpenGLPtr->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
  m_OpenGLPtr->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                            m_indexCount * sizeof(unsigned int), indices,
                            GL_STATIC_DRAW);

  delete[] vertices;
  vertices = 0;

  delete[] indices;
  indices = 0;

  return true;
}

void BitmapClass::ShutdownBuffers() {
  m_OpenGLPtr->glDisableVertexAttribArray(0);
  m_OpenGLPtr->glDisableVertexAttribArray(1);

  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_OpenGLPtr->glDeleteBuffers(1, &m_indexBufferId);

  m_OpenGLPtr->glBindVertexArray(0);
  m_OpenGLPtr->glDeleteVertexArrays(1, &m_vertexArrayId);
}

bool BitmapClass::UpdateBuffers() {
  VertexType *vertices;
  void *dataPtr;
  float left, right, top, bottom;

  if (m_prevPosX == m_renderX && m_prevPosY == m_renderY) {
    return true;
  }

  m_prevPosX = m_renderX;
  m_prevPosY = m_renderY;

  vertices = new VertexType[m_vertexCount];

  // Calculate the screen coordinates of the left side of the bitmap.
  left = (float)((m_screenWidth / 2) * -1) + (float)m_renderX;

  // Calculate the screen coordinates of the right side of the bitmap.
  right = left + (float)m_bitmapWidth;

  // Calculate the screen coordinates of the top of the bitmap.
  top = (float)(m_screenHeight / 2) - (float)m_renderY;

  // Calculate the screen coordinates of the bottom of the bitmap.
  bottom = top - (float)m_bitmapHeight;

  // First triangle.
  vertices[0].x = left; // Top left.
  vertices[0].y = top;
  vertices[0].z = 0.0f;
  vertices[0].tu = 0.0f;
  vertices[0].tv = 1.0f;

  vertices[1].x = right; // Bottom right.
  vertices[1].y = bottom;
  vertices[1].z = 0.0f;
  vertices[1].tu = 1.0f;
  vertices[1].tv = 0.0f;

  vertices[2].x = left; // Bottom left.
  vertices[2].y = bottom;
  vertices[2].z = 0.0f;
  vertices[2].tu = 0.0f;
  vertices[2].tv = 0.0f;

  // Second triangle.
  vertices[3].x = left; // Top left.
  vertices[3].y = top;
  vertices[3].z = 0.0f;
  vertices[3].tu = 0.0f;
  vertices[3].tv = 1.0f;

  vertices[4].x = right; // Top right.
  vertices[4].y = top;
  vertices[4].z = 0.0f;
  vertices[4].tu = 1.0f;
  vertices[4].tv = 1.0f;

  vertices[5].x = right; // Bottom right.
  vertices[5].y = bottom;
  vertices[5].z = 0.0f;
  vertices[5].tu = 1.0f;
  vertices[5].tv = 0.0f;

  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);

  dataPtr = m_OpenGLPtr->glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

  memcpy(dataPtr, vertices, m_vertexCount * sizeof(VertexType));

  m_OpenGLPtr->glUnmapBuffer(GL_ARRAY_BUFFER);

  delete[] vertices;
  vertices = 0;

  return true;
}

void BitmapClass::RenderBuffers() {
  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
}

bool BitmapClass::LoadTexture(char *textureFilename) {
  bool result;

  m_Texture = new TextureClass;

  result = m_Texture->Initialize(m_OpenGLPtr, textureFilename, 0, false);
  if (!result) {
    return false;
  }

  m_bitmapWidth = m_Texture->GetWidth();
  m_bitmapHeight = m_Texture->GetHeight();

  return true;
}

void BitmapClass::ReleaseTexture() {
  if (m_Texture) {
    m_Texture->Shutdown();
    delete m_Texture;
    m_Texture = 0;
  }
}

void BitmapClass::SetRenderLocation(int x, int y) {
  m_renderX = x;
  m_renderY = y;
}
