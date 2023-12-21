#include "modelclass.h"
#include <GL/glext.h>

ModelClass::ModelClass() {
  m_OpenGLPtr = 0;
  m_Textures = 0;
  m_model = 0;
}

ModelClass::ModelClass(const ModelClass &other) {}

ModelClass::~ModelClass() {}

bool ModelClass::Initialize(OpenGLClass *OpenGL, char *modelFilename,
                            char *textureFilename1, char *textureFilename2,
                            bool wrap) {
  bool result;

  m_OpenGLPtr = OpenGL;

  result = LoadModel(modelFilename);
  if (!result) {
    printf("Failed to load model at '%s'\n", modelFilename);
    return false;
  }

  result = InitializeBuffers();
  if (!result) {
    printf("Failed to initialize buffers\n");
    return false;
  }

  result = LoadTextures(textureFilename1, textureFilename2, wrap);
  if (!result) {
    printf("ERROR: Failed to load texture\n");
    return false;
  }

  return true;
}

void ModelClass::Shutdown() {
  ReleaseTextures();
  ShutdownBuffers();
  ReleaseModel();

  m_OpenGLPtr = 0;

  return;
}

void ModelClass::Render() {

  m_Textures[0].SetTexture(m_OpenGLPtr);
  m_Textures[1].SetTexture(m_OpenGLPtr);
  RenderBuffers();

  return;
}

bool ModelClass::InitializeBuffers() {
  VertexType *vertices;
  unsigned int *indices;
  int i;

  vertices = new VertexType[m_vertexCount];
  indices = new unsigned int[m_indexCount];

  for (i = 0; i < m_vertexCount; i++) {
    vertices[i].x = m_model[i].x;
    vertices[i].y = m_model[i].y;
    vertices[i].z = m_model[i].z;
    vertices[i].tu = m_model[i].tu;
    vertices[i].tv = m_model[i].tv;
    vertices[i].nx = m_model[i].nx;
    vertices[i].ny = m_model[i].ny;
    vertices[i].nz = m_model[i].nz;

    indices[i] = i;
  }

  m_OpenGLPtr->glGenVertexArrays(1, &m_vertexArrayId);
  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  m_OpenGLPtr->glGenBuffers(1, &m_vertexBufferId);

  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
  m_OpenGLPtr->glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(VertexType),
                            vertices, GL_STATIC_DRAW);

  m_OpenGLPtr->glEnableVertexAttribArray(0); // Vertex Position
  m_OpenGLPtr->glEnableVertexAttribArray(1); // Texture coordinates
  m_OpenGLPtr->glEnableVertexAttribArray(2); // Normals

  m_OpenGLPtr->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType),
                                     0);

  m_OpenGLPtr->glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType),
                                     (unsigned char *)NULL +
                                         (3 * sizeof(float)));

  m_OpenGLPtr->glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexType),
                                     (unsigned char *)NULL +
                                         (5 * sizeof(float)));

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
  m_OpenGLPtr->glDisableVertexAttribArray(2);

  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_OpenGLPtr->glDeleteBuffers(1, &m_vertexBufferId);

  m_OpenGLPtr->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_OpenGLPtr->glDeleteBuffers(1, &m_indexBufferId);

  m_OpenGLPtr->glBindVertexArray(0);
  m_OpenGLPtr->glDeleteVertexArrays(1, &m_vertexArrayId);

  return;
}

void ModelClass::RenderBuffers() {
  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

  return;
}

bool ModelClass::LoadModel(char *filename) {
  ifstream fin;
  char input;
  int i;

  fin.open(filename);

  if (fin.fail()) {
    return false;
  }

  fin.get(input);
  while (input != ':') {
    fin.get(input);
  }

  fin >> m_vertexCount;

  m_indexCount = m_vertexCount;
  m_model = new ModelType[m_vertexCount];

  fin.get(input);
  while (input != ':') {
    fin.get(input);
  }
  fin.get(input);
  fin.get(input);

  for (i = 0; i < m_vertexCount; i++) {
    fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
    fin >> m_model[i].tu >> m_model[i].tv;
    fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;

    m_model[i].tv = 1.0f - m_model[i].tv;
  }

  fin.close();

  return true;
}

void ModelClass::ReleaseModel() {
  if (m_model) {
    delete[] m_model;
    m_model = 0;
  }
}

bool ModelClass::LoadTextures(char *textureFilename1, char *textureFilename2,
                              bool wrap) {
  bool result;

  // Create and initialize the texture objects.
  m_Textures = new TextureClass[2];

  result = m_Textures[0].Initialize(m_OpenGLPtr, textureFilename1, 0, wrap);
  if (!result) {
    printf("Failed to initialize texture at '%s'\n", textureFilename1);
    return false;
  }

  result = m_Textures[1].Initialize(m_OpenGLPtr, textureFilename2, 1, wrap);
  if (!result) {
    printf("Failed to initialize texture at '%s'\n", textureFilename2);
    return false;
  }

  return true;
}

void ModelClass::ReleaseTextures() {
  // Release the texture objects.
  if (m_Textures) {
    m_Textures[0].Shutdown();
    m_Textures[1].Shutdown();

    delete[] m_Textures;
    m_Textures = 0;
  }

  return;
}
