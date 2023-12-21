#include "applicationclass.h"
#include "textureshaderclass.h"

ApplicationClass::ApplicationClass() {
  m_OpenGL = 0;
  m_TextureShader = 0;
  m_Bitmap = 0;
  m_Sprite = 0;
  m_Timer = 0;
  m_FontShader = 0;
  m_Font = 0;
  m_TextString1 = 0;
  m_TextString2 = 0;
  m_Fps = 0;
  m_FpsString = 0;
}

ApplicationClass::ApplicationClass(const ApplicationClass &other) {}

ApplicationClass::~ApplicationClass() {}

bool ApplicationClass::Initialize(Display *display, Window win, int screenWidth,
                                  int screenHeight) {
  char fpsString[32];
  bool result;

  m_OpenGL = new OpenGLClass;

  result = m_OpenGL->Initialize(display, win, screenWidth, screenHeight,
                                SCREEN_NEAR, SCREEN_DEPTH, VSYNC_ENABLED);
  if (!result) {
    printf("ERROR: Failed to initialize openGL\n");
    return false;
  }

  m_Camera = new CameraClass;
  m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
  m_Camera->Render();

  m_FontShader = new FontShaderClass;
  result = m_FontShader->Initialize(m_OpenGL);
  if (!result) {
    printf("ERROR: failed to initialize font shader\n");
    return false;
  }

  m_Font = new FontClass;
  result = m_Font->Initialize(m_OpenGL, 0);
  if (!result) {
    printf("ERROR: failed to initialize fontclass\n");
    return false;
  }

  m_Fps = new FpsClass();
  m_Fps->Initialize();

  m_previousFps = -1;
  strcpy(fpsString, "Fps: 0");

  m_FpsString = new TextClass;

  result = m_FpsString->Initialize(m_OpenGL, screenWidth, screenHeight, 16,
                                   m_Font, fpsString, 10, 50, 0.0f, 1.0f, 0.0f);
  if (!result) {
    return false;
  }

  return true;
}

void ApplicationClass::Shutdown() {
  if (m_FpsString) {
    m_FpsString->Shutdown();
    delete m_FpsString;
    m_FpsString = 0;
  }
  if (m_Fps) {
    delete m_Fps;
    m_Fps = 0;
  }
  if (m_TextString2) {
    m_TextString2->Shutdown();
    delete m_TextString2;
    m_TextString2 = 0;
  }
  if (m_TextString1) {
    m_TextString1->Shutdown();
    delete m_TextString1;
    m_TextString1 = 0;
  }
  if (m_Font) {
    m_Font->Shutdown();
    delete m_Font;
    m_Font = 0;
  }
  if (m_FontShader) {
    m_FontShader->Shutdown();
    delete m_FontShader;
    m_FontShader = 0;
  }
  if (m_Timer) {
    delete m_Timer;
    m_Timer = 0;
  }
  if (m_Sprite) {
    m_Sprite->Shutdown();
    delete m_Sprite;
    m_Sprite = 0;
  }
  if (m_Bitmap) {
    m_Bitmap->Shutdown();
    delete m_Bitmap;
    m_Bitmap = 0;
  }
  // Release the color shader object.
  if (m_TextureShader) {
    m_TextureShader->Shutdown();
    delete m_TextureShader;
    m_TextureShader = 0;
  }

  // Release the model object.
  if (m_Model) {
    m_Model->Shutdown();
    delete m_Model;
    m_Model = 0;
  }

  // Release the camera object.
  if (m_Camera) {
    delete m_Camera;
    m_Camera = 0;
  }

  if (m_OpenGL) {
    m_OpenGL->Shutdown();
    delete m_OpenGL;
    m_OpenGL = 0;
  }

  return;
}

bool ApplicationClass::Frame(InputClass *Input) {
  int frameTime;
  bool result;
  if (Input->IsEscapePressed() == true) {
    return false;
  }

  result = UpdateFps();
  if (!result) {
    return false;
  }

  result = Render();
  if (!result) {
    return false;
  }

  return true;
}

bool ApplicationClass::Render() {
  float worldMatrix[16], viewMatrix[16], orthoMatrix[16];
  float pixelColor[4];
  bool result;

  m_OpenGL->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

  m_OpenGL->GetWorldMatrix(worldMatrix);
  m_Camera->GetViewMatrix(viewMatrix);
  m_OpenGL->GetOrthoMatrix(orthoMatrix);

  m_OpenGL->TurnZBufferOff();
  m_OpenGL->EnableAlphaBlending();

  m_FpsString->GetPixelColor(pixelColor);

  result = m_FontShader->SetShaderParameters(worldMatrix, viewMatrix,
                                             orthoMatrix, pixelColor);
  if (!result) {
    return false;
  }

  m_Font->SetTexture();

  m_FpsString->Render();

  m_OpenGL->TurnZBufferOn();
  m_OpenGL->DisableAlphaBlending();
  m_OpenGL->EndScene();

  return true;
}
bool ApplicationClass::UpdateFps() {
  int fps;
  char tempString[16], finalString[16];
  float red, green, blue;
  bool result;

  m_Fps->Frame();

  fps = m_Fps->GetFps();

  if (m_previousFps == fps) {
    return true;
  }

  m_previousFps = fps;

  if (fps > 99999) {
    fps = 99999;
  }

  sprintf(tempString, "%d", fps);

  strcpy(finalString, "Fps: ");
  strcat(finalString, tempString);

  if (fps >= 60) {
    red = 0.0f;
    green = 1.0f;
    blue = 0.0f;
  }

  if (fps < 60) {
    red = 1.0f;
    green = 1.0f;
    blue = 0.0f;
  }
  if (fps < 30) {
    red = 1.0f;
    green = 0.0f;
    blue = 0.0f;
  }

  result =
      m_FpsString->UpdateText(m_Font, finalString, 10, 10, red, green, blue);
  if (!result) {
    return false;
  }

  return true;
}
