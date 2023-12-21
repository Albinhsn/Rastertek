#ifndef FONTSHADERCLASS_H
#define FONTSHADERCLASS_H

#include "openglclass.h"
#include <fstream>
using namespace std;


class FontShaderClass{
public:
  FontShaderClass();
  FontShaderClass(const FontShaderClass & );
  ~FontShaderClass();

  bool Initialize(OpenGLClass*);
  void Shutdown();

  bool SetShaderParameters(float *, float*, float*, float*);

private:
  bool InitializeShader(char*,char *);
  void ShutdownShader();
  char * LoadShaderSourceFile(char *);
  void OutputShaderErrorMessage(unsigned int, char *);
  void OutputLinkerErrorMessage(unsigned int);

private:
  OpenGLClass * m_OpenGLPtr;
  unsigned int m_vertexShader;
  unsigned int m_fragmentShader;
  unsigned int m_shaderProgram;
};

#endif
