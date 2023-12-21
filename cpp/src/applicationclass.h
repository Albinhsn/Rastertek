#ifndef APPLICATIONCLASS_H
#define APPLICATIONCLASS_H

#include "bitmapclass.h"
#include "cameraclass.h"
#include "fontclass.h"
#include "fontshaderclass.h"
#include "fpsclass.h"
#include "inputclass.h"
#include "lightclass.h"
#include "lightshaderclass.h"
#include "modelclass.h"
#include "openglclass.h"
#include "spriteclass.h"
#include "textclass.h"
#include "textureshaderclass.h"
#include "multitextureshaderclass.h"
#include "timerclass.h"

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
  bool UpdateFps();
  bool UpdateMouseStrings(int, int, bool);

  OpenGLClass *m_OpenGL;
  MultiTextureShaderClass * m_MultiTextureShader;
  TextureShaderClass *m_TextureShader;
  ModelClass *m_Model;
  CameraClass *m_Camera;
  LightShaderClass *m_LightShader;
  LightClass *m_Light;
  BitmapClass *m_Bitmap;
  SpriteClass *m_Sprite;
  TimerClass *m_Timer;
  FontShaderClass *m_FontShader;
  FontClass *m_Font;
  TextClass *m_TextString1, *m_TextString2;
  FpsClass *m_Fps;
  TextClass *m_FpsString;
  TextClass *m_MouseStrings;
  int m_previousFps;
};

#endif
