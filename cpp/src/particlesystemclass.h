#ifndef PARTICLESYSTEMCLASS_H
#define PARTICLESYSTEMCLASS_H

#include "textureclass.h"

class ParticleSystemClass {
private:
  struct VertexType {
    float x, y, z;
    float tu, tv;
    float red, green, blue, alpha;
  };

  struct ParticleType {
    float positionX, positionY, positionZ;
    float red, green, blue;
    float velocity;
    bool active;
  };

public:
  ParticleSystemClass();
  ParticleSystemClass(const ParticleSystemClass&);
  ~ParticleSystemClass();

  bool Initialize(OpenGLClass *, char*);
  void Shutdown();
  void Frame(int);
  void Render();

private:
  bool LoadTexture(char *, bool);
  void ReleaseTexture();
  void InitializeParticleSystem();
  void ShutdownParticleSystem();

  void InitializeBuffers();
  void ShutdownBuffers();
  void RenderBuffers();

  void EmitParticles(int);
  void UpdateParticles(int);
  void KillParticles();

  void UpdateBuffers();

private:
  OpenGLClass * m_OpenGLPtr;
  TextureClass * m_Texture;

  ParticleType * m_particleList;
  VertexType * m_vertices;

  float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
  float m_particleVelocity, m_particleVelocityVariation;
  float m_particleSize;
  int m_particlesPerSecond, m_maxParticles;
  int m_currentParticleCount;
  int m_accumulatedTime;

  int m_vertexCount, m_indexCount;
  unsigned int m_vertexArrayId, m_vertexBufferId, m_indexBufferId;
};

#endif
