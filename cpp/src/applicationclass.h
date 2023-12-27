#ifndef APPLICATIONCLASS_H
#define APPLICATIONCLASS_H

#include "alphamapshaderclass.h"
#include "bitmapclass.h"
#include "cameraclass.h"
#include "clipplaneshaderclass.h"
#include "displayplaneclass.h"
#include "fogshaderclass.h"
#include "fontclass.h"
#include "fontshaderclass.h"
#include "fpsclass.h"
#include "frustumclass.h"
#include "glassshaderclass.h"
#include "inputclass.h"
#include "lightclass.h"
#include "lightmapshaderclass.h"
#include "lightshaderclass.h"
#include "modelclass.h"
#include "modellistclass.h"
#include "multitextureshaderclass.h"
#include "normalmapshaderclass.h"
#include "openglclass.h"
#include "positionclass.h"
#include "reflectionshaderclass.h"
#include "refractionshaderclass.h"
#include "rendertextureclass.h"
#include "shadermanagerclass.h"
#include "specmapshaderclass.h"
#include "spriteclass.h"
#include "textclass.h"
#include "textureshaderclass.h"
#include "timerclass.h"
#include "translateshaderclass.h"
#include "transparentshaderclass.h"
#include "watershaderclass.h"
#include "fireshaderclass.h"

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
  bool RenderReflectionToTexture();
  bool RenderRefractionToTexture();
  bool RenderSceneToTexture(float);
  bool Render();
  bool UpdateFps();
  bool UpdateRenderCountString(int renderCount);
  bool UpdateMouseStrings(int, int, bool);

  OpenGLClass *m_OpenGL;
  MultiTextureShaderClass *m_MultiTextureShader;
  TextureShaderClass *m_TextureShader;
  ModelClass *m_Model;
  ModelClass *m_WindowModel;
  ModelClass *m_Model1;
  ModelClass *m_Model2;
  ModelClass *m_CubeModel, *m_FloorModel;
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
  LightMapShaderClass *m_LightMapShader;
  AlphaMapShaderClass *m_AlphaMapShader;
  NormalMapShaderClass *m_NormalMapShader;
  SpecMapShaderClass *m_SpecMapShader;
  int m_previousFps;
  ShaderManagerClass *m_ShaderManager;
  FrustumClass *m_Frustum;
  PositionClass *m_Position;
  ModelListClass *m_ModelList;
  float m_baseViewMatrix[16];
  TextClass *m_RenderCountString;
  RenderTextureClass *m_RenderTexture;
  DisplayPlaneClass *m_DisplayPlane;
  FogShaderClass *m_FogShader;
  ClipPlaneShaderClass *m_ClipPlaneShader;
  TranslateShaderClass *m_TranslateShader;
  TransparentShaderClass *m_TransparentShader;
  ReflectionShaderClass *m_ReflectionShader;

  // Water
  ModelClass *m_GroundModel, *m_WallModel, *m_BathModel, *m_WaterModel;
  RenderTextureClass *m_RefractionTexture, *m_ReflectionTexture;
  RefractionShaderClass *m_RefractionShader;
  WaterShaderClass *m_WaterShader;

  // Glass and Ice
  GlassShaderClass *m_GlassShader;

  // Fire
  FireShaderClass * m_FireShader;

  float m_waterHeight, m_waterTranslation;
};

#endif
