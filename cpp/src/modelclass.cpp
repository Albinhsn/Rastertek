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
                            char *textureFilename3, bool wrap) {
  bool result;

  m_OpenGLPtr = OpenGL;

  result = LoadModel(modelFilename);
  if (!result) {
    printf("Failed to load model at '%s'\n", modelFilename);
    return false;
  }

  CalculateModelVectors();

  result = InitializeBuffers();
  if (!result) {
    printf("Failed to initialize buffers\n");
    return false;
  }

  result =
      LoadTextures(textureFilename1, textureFilename2, textureFilename3, wrap);
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
  m_Textures[2].SetTexture(m_OpenGLPtr);
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
    vertices[i].tx = m_model[i].tx;
    vertices[i].ty = m_model[i].ty;
    vertices[i].tz = m_model[i].tz;
    vertices[i].bx = m_model[i].bx;
    vertices[i].by = m_model[i].by;
    vertices[i].bz = m_model[i].bz;

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
  m_OpenGLPtr->glEnableVertexAttribArray(3); // Tangent
  m_OpenGLPtr->glEnableVertexAttribArray(4); // Binormal

  m_OpenGLPtr->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType),
                                     0);

  m_OpenGLPtr->glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType),
                                     (unsigned char *)NULL +
                                         (3 * sizeof(float)));

  m_OpenGLPtr->glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexType),
                                     (unsigned char *)NULL +
                                         (5 * sizeof(float)));
  m_OpenGLPtr->glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(VertexType),
                                     (unsigned char *)NULL +
                                         (8 * sizeof(float)));
  m_OpenGLPtr->glVertexAttribPointer(4, 3, GL_FLOAT, false, sizeof(VertexType),
                                     (unsigned char *)NULL +
                                         (11 * sizeof(float)));

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
  m_OpenGLPtr->glDisableVertexAttribArray(3);
  m_OpenGLPtr->glDisableVertexAttribArray(4);

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
                              char *textureFilename3, bool wrap) {
  bool result;

  // Create and initialize the texture objects.
  m_Textures = new TextureClass[3];

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

  result = m_Textures[2].Initialize(m_OpenGLPtr, textureFilename3, 2, wrap);
  if (!result) {
    printf("Failed to initialize texture at '%s'\n", textureFilename3);
    return false;
  }

  return true;
}

void ModelClass::ReleaseTextures() {
  // Release the texture objects.
  if (m_Textures) {
    m_Textures[0].Shutdown();
    m_Textures[1].Shutdown();
    m_Textures[2].Shutdown();

    delete[] m_Textures;
    m_Textures = 0;
  }

  return;
}
void ModelClass::CalculateModelVectors() {
  int faceCount, i, index;
  TempVertexType vertex1, vertex2, vertex3;
  VectorType tangent, binormal;

  // Calculate the number of faces in the model.
  faceCount = m_vertexCount / 3;

  // Initialize the index to the model data.
  index = 0;

  // Go through all the faces and calculate the the tangent and binormal
  // vectors.
  for (i = 0; i < faceCount; i++) {
    // Get the three vertices for this face from the model.
    vertex1.x = m_model[index].x;
    vertex1.y = m_model[index].y;
    vertex1.z = m_model[index].z;
    vertex1.tu = m_model[index].tu;
    vertex1.tv = m_model[index].tv;
    index++;

    vertex2.x = m_model[index].x;
    vertex2.y = m_model[index].y;
    vertex2.z = m_model[index].z;
    vertex2.tu = m_model[index].tu;
    vertex2.tv = m_model[index].tv;
    index++;

    vertex3.x = m_model[index].x;
    vertex3.y = m_model[index].y;
    vertex3.z = m_model[index].z;
    vertex3.tu = m_model[index].tu;
    vertex3.tv = m_model[index].tv;
    index++;

    // Calculate the tangent and binormal of that face.
    CalculateTangentBinormal(vertex1, vertex2, vertex3, tangent, binormal);

    // Store the tangent and binormal for this face back in the model structure.
    m_model[index - 1].tx = tangent.x;
    m_model[index - 1].ty = tangent.y;
    m_model[index - 1].tz = tangent.z;
    m_model[index - 1].bx = binormal.x;
    m_model[index - 1].by = binormal.y;
    m_model[index - 1].bz = binormal.z;

    m_model[index - 2].tx = tangent.x;
    m_model[index - 2].ty = tangent.y;
    m_model[index - 2].tz = tangent.z;
    m_model[index - 2].bx = binormal.x;
    m_model[index - 2].by = binormal.y;
    m_model[index - 2].bz = binormal.z;

    m_model[index - 3].tx = tangent.x;
    m_model[index - 3].ty = tangent.y;
    m_model[index - 3].tz = tangent.z;
    m_model[index - 3].bx = binormal.x;
    m_model[index - 3].by = binormal.y;
    m_model[index - 3].bz = binormal.z;
  }

  return;
}

void ModelClass::CalculateTangentBinormal(TempVertexType vertex1,
                                          TempVertexType vertex2,
                                          TempVertexType vertex3,
                                          VectorType &tangent,
                                          VectorType &binormal) {
  float vector1[3], vector2[3];
  float tuVector[2], tvVector[2];
  float den;
  float length;

  // Calculate the two vectors for this face.
  vector1[0] = vertex2.x - vertex1.x;
  vector1[1] = vertex2.y - vertex1.y;
  vector1[2] = vertex2.z - vertex1.z;

  vector2[0] = vertex3.x - vertex1.x;
  vector2[1] = vertex3.y - vertex1.y;
  vector2[2] = vertex3.z - vertex1.z;

  // Calculate the tu and tv texture space vectors.
  tuVector[0] = vertex2.tu - vertex1.tu;
  tvVector[0] = vertex2.tv - vertex1.tv;

  tuVector[1] = vertex3.tu - vertex1.tu;
  tvVector[1] = vertex3.tv - vertex1.tv;

  // Calculate the denominator of the tangent/binormal equation.
  den = 1.0f / (tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0]);

  // Calculate the cross products and multiply by the coefficient to get the
  // tangent and binormal.
  tangent.x = (tvVector[1] * vector1[0] - tvVector[0] * vector2[0]) * den;
  tangent.y = (tvVector[1] * vector1[1] - tvVector[0] * vector2[1]) * den;
  tangent.z = (tvVector[1] * vector1[2] - tvVector[0] * vector2[2]) * den;

  binormal.x = (tuVector[0] * vector2[0] - tuVector[1] * vector1[0]) * den;
  binormal.y = (tuVector[0] * vector2[1] - tuVector[1] * vector1[1]) * den;
  binormal.z = (tuVector[0] * vector2[2] - tuVector[1] * vector1[2]) * den;

  // Calculate the length of this normal.
  length = sqrt((tangent.x * tangent.x) + (tangent.y * tangent.y) +
                (tangent.z * tangent.z));

  // Normalize the normal and then store it
  tangent.x = tangent.x / length;
  tangent.y = tangent.y / length;
  tangent.z = tangent.z / length;

  // Calculate the length of this normal.
  length = sqrt((binormal.x * binormal.x) + (binormal.y * binormal.y) +
                (binormal.z * binormal.z));

  // Normalize the normal and then store it
  binormal.x = binormal.x / length;
  binormal.y = binormal.y / length;
  binormal.z = binormal.z / length;

  return;
}
