#ifndef CAMERACLASS_H
#define CAMERACLASS_H

#include <math.h>

class CameraClass {
private:
  struct VectorType {
    float x, y, z;
  };

public:
  CameraClass();
  CameraClass(const CameraClass&);
  ~CameraClass();

  void SetPosition(float, float, float);
  void SetRotation(float, float, float);

  void GetPosition(float*);
  void GetRotation(float*);

  void Render();
  void GetViewMatrix(float*);

  void RenderReflection(float);
  void GetReflectionViewMatrix(float*);

private:
  void MatrixRotationYawPitchRoll(float *, float, float, float);
  void TransformCoord(VectorType&, float*);
  void BuildViewMatrix(VectorType, VectorType, VectorType);
  void BuildReflectionViewMatrix(VectorType, VectorType, VectorType);

private:
  float m_positionX, m_positionY, m_positionZ;
  float m_rotationX, m_rotationY, m_rotationZ;
  float m_viewMatrix[16];
  float m_reflectionViewMatrix[16];
};

#endif
