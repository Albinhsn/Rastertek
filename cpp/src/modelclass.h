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
    float nx, ny, nz;
    float tx, ty, tz;
    float bx, by, bz;
  };
  struct ModelType {
    float x, y, z;
    float tu, tv;
    float nx, ny, nz;
    float tx, ty, tz;
    float bx, by, bz;
  };

  struct TempVertexType {
    float x, y, z;
    float tu, tv;
  };

  struct VectorType {
    float x, y, z;
  };

public:
  ModelClass();
  ModelClass(const ModelClass &);
  ~ModelClass();

  bool Initialize(OpenGLClass *, char *, char *, char *, bool);
  void Shutdown();
  void Render(int);

private:
  bool InitializeBuffers();
  void ShutdownBuffers();
  void RenderBuffers();

  bool LoadTextures(char *, char *, bool);
  void ReleaseTextures();

  bool LoadModel(char *);
  void ReleaseModel();

  void CalculateModelVectors();
  void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType,
                                VectorType &, VectorType &);

private:
  OpenGLClass *m_OpenGLPtr;
  int m_vertexCount, m_indexCount;
  unsigned int m_vertexArrayId, m_vertexBufferId, m_indexBufferId;

  TextureClass *m_Textures;

  ModelType *m_model;
};

#endif
