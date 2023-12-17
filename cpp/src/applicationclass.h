#ifndef APPLICATIONCLASS_H
#define APPLICATIONCLASS_H

#include "cameraclass.h"
#include "inputclass.h"
#include "modelclass.h"
#include "openglclass.h"
#include "textureshaderclass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_NEAR = 0.3f;
const float SCREEN_DEPTH = 1000.0f;

class ApplicationClass {
public:
  ApplicationClass();
  ApplicationClass(const ApplicationClass &);
  ~ApplicationClass();

  bool Initialize(Display *, Window, int, int);
  void Shutdown();
  bool Frame(InputClass *);

private:
  bool Render();

  OpenGLClass *m_OpenGL;

  TextureShaderClass *m_TextureShader;
  ModelClass *m_Model;
  CameraClass *m_Camera;
};

#endif
