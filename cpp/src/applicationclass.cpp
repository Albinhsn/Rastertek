#include "applicationclass.h"
#include "textureshaderclass.h"

ApplicationClass::ApplicationClass() {
  m_OpenGL = 0;
  m_TextureShader = 0;
  m_Bitmap = 0;
}

ApplicationClass::ApplicationClass(const ApplicationClass &other) {}

ApplicationClass::~ApplicationClass() {}

bool ApplicationClass::Initialize(Display *display, Window win, int screenWidth,
                                  int screenHeight) {
  char bitmapFilename[128];
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

  m_TextureShader = new TextureShaderClass;

  result = m_TextureShader->Initialize(m_OpenGL);
  if (!result) {
    return false;
  }

  strcpy(bitmapFilename, "./data/stone01.tga");

  m_Bitmap = new BitmapClass;

  result = m_Bitmap->Initialize(m_OpenGL, screenWidth, screenHeight,
                                bitmapFilename, 100, 100);
  if (!result) {
    printf("ERROR: Failed to initialize bitmap\n");
    return false;
  }

  return true;
}

void ApplicationClass::Shutdown() {
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
  static float rotation = 360.0f;
  bool result;

  if (Input->IsEscapePressed() == true) {
    return false;
  }

  rotation -= 0.0174532925f * 1.0f;
  if (rotation <= 0.0f) {
    rotation += 360.0f;
  }

  result = Render(rotation);
  if (!result) {
    return false;
  }

  return true;
}

bool ApplicationClass::Render(float rotation) {
  float worldMatrix[16], viewMatrix[16], orthoMatrix[16];
  bool result;

  m_OpenGL->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

  m_OpenGL->GetWorldMatrix(worldMatrix);
  m_Camera->GetViewMatrix(viewMatrix);
  m_OpenGL->GetOrthoMatrix(orthoMatrix);

  m_OpenGL->TurnZBufferOff();

  result = m_TextureShader->SetShaderParameters(worldMatrix, viewMatrix,
                                                orthoMatrix);
  if (!result) {
    return false;
  }

  m_Bitmap->Render();
  m_OpenGL->TurnZBufferOn();
  m_OpenGL->EndScene();

  return true;
}
