#include "orthowindowclass.h"

OrthoWindowClass::OrthoWindowClass() { m_OpenGLPtr = 0; }

OrthoWindowClass::OrthoWindowClass(const OrthoWindowClass &other) {}

OrthoWindowClass::~OrthoWindowClass() {}

bool OrthoWindowClass::Initialize(OpenGLClass *OpenGL, int windowWidth,
                                  int windowHeight) {
  bool result;

  m_OpenGLPtr = OpenGL;

  result = InitializeBuffers(windowWidth, windowHeight);
  if (!result) {
    return false;
  }

  return true;
}

void OrthoWindowClass::Shutdown() {
  ShutdownBuffers();

  m_OpenGLPtr = 0;
}

void OrthoWindowClass::Render() { RenderBuffers(); }

bool OrthoWindowClass::InitializeBuffers(int windowWidth, int windowHeight) {
  VertexType *vertices;
  unsigned int *indices;
  float left, right, top, bottom;
  int i;

  left = (float)((windowWidth / 2) * -1);

  right = left + (float)windowWidth;

  top = (float)(windowHeight / 2);

  bottom = top - (float)windowHeight;

  m_vertexCount = 6;
  m_indexCount = m_vertexCount;

  vertices = new VertexType[m_vertexCount];

  indices = new unsigned int[m_indexCount];

  vertices[0].x = left;
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

  // Load the index array with data.
  for (i = 0; i < m_indexCount; i++) {
    indices[i] = i;
  }

  // Allocate an OpenGL vertex array object.
  m_OpenGLPtr->glGenVertexArrays(1, &m_vertexArrayId);

  // Bind the vertex array object to store all the buffers and vertex attributes
  // we create here.
  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  // Generate an ID for the vertex buffer.
  m_OpenGLPtr->glGenBuffers(1, &m_vertexBufferId);

  // Bind the vertex buffer and load the vertex data into the vertex buffer. Set
  // gpu hint to static since it will never change.
  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
  m_OpenGLPtr->glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(VertexType),
                            vertices, GL_STATIC_DRAW);

  // Enable the two vertex array attributes.
  m_OpenGLPtr->glEnableVertexAttribArray(0); // Vertex position.
  m_OpenGLPtr->glEnableVertexAttribArray(1); // Texture coordinates.

  // Specify the location and format of the position portion of the vertex
  // buffer.
  m_OpenGLPtr->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType),
                                     0);

  // Specify the location and format of the texture coordinate portion of the
  // vertex buffer.
  m_OpenGLPtr->glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType),
                                     (unsigned char *)NULL +
                                         (3 * sizeof(float)));

  // Generate an ID for the index buffer.
  m_OpenGLPtr->glGenBuffers(1, &m_indexBufferId);

  // Bind the index buffer and load the index data into it.  Leave it static
  // since the indices won't change.
  m_OpenGLPtr->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
  m_OpenGLPtr->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                            m_indexCount * sizeof(unsigned int), indices,
                            GL_STATIC_DRAW);

  // Now that the buffers have been loaded we can release the array data.
  delete[] vertices;
  vertices = 0;

  delete[] indices;
  indices = 0;

  return true;
}

void OrthoWindowClass::ShutdownBuffers() {
  // Disable the two vertex array attributes.
  m_OpenGLPtr->glDisableVertexAttribArray(0);
  m_OpenGLPtr->glDisableVertexAttribArray(1);

  // Release the vertex buffer.
  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_OpenGLPtr->glDeleteBuffers(1, &m_vertexBufferId);

  // Release the index buffer.
  m_OpenGLPtr->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_OpenGLPtr->glDeleteBuffers(1, &m_indexBufferId);

  // Release the vertex array object.
  m_OpenGLPtr->glBindVertexArray(0);
  m_OpenGLPtr->glDeleteVertexArrays(1, &m_vertexArrayId);

  return;
}

void OrthoWindowClass::RenderBuffers() {
  // Bind the vertex array object that stored all the information about the
  // vertex and index buffers.
  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  // Render the vertex buffer using the index buffer.
  glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

  return;
}
