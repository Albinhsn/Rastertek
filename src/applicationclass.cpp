#include "applicationclass.h"

ApplicationClass::ApplicationClass() {
  m_OpenGL = 0;
  m_ColorShader = 0;
  m_Model = 0;
  m_Camera = 0;
}

ApplicationClass::ApplicationClass(const ApplicationClass &other) {}

ApplicationClass::~ApplicationClass() {}

bool ApplicationClass::Initialize(Display *display, Window win, int screenWidth,
                                  int screenHeight) {
  bool result;

  m_OpenGL = new OpenGLClass;

  result = m_OpenGL->Initialize(display, win, screenWidth, screenHeight,
                                SCREEN_NEAR, SCREEN_DEPTH, VSYNC_ENABLED);
  if (!result) {
    return false;
  }

  m_ColorShader = new ColorShaderClass;

  result = m_ColorShader->Initialize(m_OpenGL);
  if (!result) {
    return false;
  }

  m_Camera = new CameraClass;

  m_Camera->SetPosition(0.0f, 0.0f, -5.0f);
  m_Camera->Render();

  m_Model = new ModelClass;

  result = m_Model->Initialize(m_OpenGL);
  if (!result) {
    return false;
  }

  return true;
}

void ApplicationClass::Shutdown() {

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

  // Release the color shader object.
  if (m_ColorShader) {
    m_ColorShader->Shutdown();
    delete m_ColorShader;
    m_ColorShader = 0;
  }

  if (m_OpenGL) {
    m_OpenGL->Shutdown();
    delete m_OpenGL;
    m_OpenGL = 0;
  }

  return;
}

bool ApplicationClass::Frame(InputClass *Input) {
  bool result;

  if (Input->IsEscapePressed() == true) {
    return false;
  }

  result = Render();
  if (!result) {
    return false;
  }

  return true;
}

bool ApplicationClass::Render() {
  float worldMatrix[16], viewMatrix[16], projectionMatrix[16];
  bool result;

  m_OpenGL->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

  // Get the world, view, and projection matrices from the opengl and camera
  // objects.
  m_OpenGL->GetWorldMatrix(worldMatrix);
  m_Camera->GetViewMatrix(viewMatrix);
  m_OpenGL->GetProjectionMatrix(projectionMatrix);

  // Set the color shader as the current shader program and set the matrices
  // that it will use for rendering.
  result = m_ColorShader->SetShaderParameters(worldMatrix, viewMatrix,
                                              projectionMatrix);
  if (!result) {
    return false;
  }

  // Render the model.
  m_Model->Render();

  m_OpenGL->EndScene();

  return true;
}
