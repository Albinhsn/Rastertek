#ifndef LIGHTSHADERCLASS_H
#define LIGHTSHADERCLASS_H


#include <iostream>
using namespace std;

#include "openglclass.h"


class LightShaderClass{
public:
  LightShaderClass();
  LightShaderClass(const LightShaderClass&);
  ~LightShaderClass();

  bool Initialize(OpenGLClass*);
  void Shutdown();

  bool SetShaderParameters(float *, float *, float *, float *, float*, float*);

private:
  bool InitializeShader(char*, char*);
  void ShutdownShader();
  char * LoadShaderSourceFile(char*);
  void OutputShaderErrorMessage(unsigned int, char*);
  void OutputLinkerErrorMessage(unsigned int);
private:
  OpenGLClass * m_OpenGLPtr;
  unsigned int m_vertexShader;
  unsigned int m_fragmentShader;
  unsigned int m_shaderProgram;
};


#endif
