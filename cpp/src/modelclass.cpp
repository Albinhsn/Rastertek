#include "modelclass.h"
#include <GL/glext.h>

ModelClass::ModelClass() {
  m_OpenGLPtr = 0; 
  m_Texture = 0;
}

ModelClass::ModelClass(const ModelClass &other) {}

ModelClass::~ModelClass() {}

bool ModelClass::Initialize(OpenGLClass *OpenGL, char * textureFilename, bool wrap) {
  bool result;

  m_OpenGLPtr = OpenGL;

  result = InitializeBuffers();

  if (!result) {
    return false;
  }

  result = LoadTexture(textureFilename, wrap);
  if(!result){
    printf("ERROR: Failed to load texture\n");
    return false;
  }

  return true;
}

void ModelClass::Shutdown() {
  ReleaseTexture();
  ShutdownBuffers();

  m_OpenGLPtr = 0;

  return;
}

void ModelClass::Render() {

  m_Texture->SetTexture(m_OpenGLPtr);
  RenderBuffers();

  return;
}

bool ModelClass::InitializeBuffers() {
  VertexType *vertices;
  unsigned int *indices;

  m_vertexCount = 3;
  m_indexCount = 3;

  vertices = new VertexType[m_vertexCount];
  indices = new unsigned int[m_indexCount];

  // Load the vertex array with data.

  // Bottom left.
  vertices[0].x = -1.0f; // Position.
  vertices[0].y = -1.0f;
  vertices[0].z = 0.0f;
  vertices[0].tu = 0.0f; // Texture
  vertices[0].tv = 0.0f; 

  // Top middle.
  vertices[1].x = 0.0f; // Position.
  vertices[1].y = 1.0f;
  vertices[1].z = 0.0f;
  vertices[1].tu = 0.5f; // Texture
  vertices[1].tv = 1.0f; 


  // Bottom right.
  vertices[2].x = 1.0f; // Position.
  vertices[2].y = -1.0f;
  vertices[2].z = 0.0f;
  vertices[2].tu = 1.0f; // Texture
  vertices[2].tv = 0.0f; 


  // Load the index array with data.
  indices[0] = 0; // Bottom left.
  indices[1] = 1; // Top middle.
  indices[2] = 2; // Bottom right.

  m_OpenGLPtr->glGenVertexArrays(1, &m_vertexArrayId);
  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  m_OpenGLPtr->glGenBuffers(1, &m_vertexBufferId);

  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
  m_OpenGLPtr->glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(VertexType),
                            vertices, GL_STATIC_DRAW);

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

void ModelClass::ShutdownBuffers() {
  m_OpenGLPtr->glDisableVertexAttribArray(0);
  m_OpenGLPtr->glDisableVertexAttribArray(1);

  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_OpenGLPtr->glDeleteBuffers(1, &m_vertexBufferId);

  m_OpenGLPtr->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_OpenGLPtr->glDeleteBuffers(1, &m_indexBufferId);

  m_OpenGLPtr->glBindVertexArray(0);
  m_OpenGLPtr->glDeleteVertexArrays(1, &m_vertexArrayId);

  return;
}

void ModelClass::RenderBuffers(){
  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

  return;
}

bool ModelClass::LoadTexture(char * textureFilename, bool wrap){
  bool result;

  m_Texture = new TextureClass;

  result = m_Texture->Initialize(m_OpenGLPtr, textureFilename, 0, wrap);
  if(!result){
    printf("ERROR: Failed to initialize texture\n");
    return false;
  }

  return true;
}

void ModelClass::ReleaseTexture(){
  if(m_Texture){
    m_Texture->Shutdown();
    delete m_Texture;
    m_Texture = 0;
  }

  return;
}
