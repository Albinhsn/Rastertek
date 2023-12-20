#include "applicationclass.h"

ApplicationClass::ApplicationClass() {
  m_OpenGL = 0;
  m_TextureShader = 0;
  m_Model = 0;
  m_LightShader = 0;
  m_Light = 0;
}

ApplicationClass::ApplicationClass(const ApplicationClass &other) {}

ApplicationClass::~ApplicationClass() {}

bool ApplicationClass::Initialize(Display *display, Window win, int screenWidth,
                                  int screenHeight) {
  char modelFilename[128];
  char textureFilename[128];
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

  strcpy(modelFilename, "./data/cube.txt");

  strcpy(textureFilename, "./data/stone01.tga");

  m_Model = new ModelClass;

  result = m_Model->Initialize(m_OpenGL, modelFilename, textureFilename, false);
  if (!result) {
    printf("ERROR: Failed to initialize model\n");
    return false;
  }

  m_LightShader = new LightShaderClass;
  result = m_LightShader->Initialize(m_OpenGL);
  if (!result) {
    printf("ERROR: failed to initialize light shader\n");
    return false;
  }

  m_Light = new LightClass;
  m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
  m_Light->SetDirection(0.0f, 0.0f, 1.0f);

  m_TextureShader = new TextureShaderClass;

  result = m_TextureShader->Initialize(m_OpenGL);
  if (!result) {
    printf("ERROR: Failed to initialize texture shader\n");
    return false;
  }

  return true;
}

void ApplicationClass::Shutdown() {
  if (m_Light) {
    delete m_Light;
    m_Light = 0;
  }

  if (m_LightShader) {
    m_LightShader->Shutdown();
    delete m_LightShader;
    m_LightShader = 0;
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
  float worldMatrix[16], viewMatrix[16], projectionMatrix[16], rotateMatrix[16],
      translateMatrix[16], scaleMatrix[16], srMatrix[16];
  float diffuseLightColor[4], lightDirection[3];
  bool result;

  m_OpenGL->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

  // Get the world, view, and projection matrices from the opengl and camera
  // objects.
  m_OpenGL->GetWorldMatrix(worldMatrix);
  m_Camera->GetViewMatrix(viewMatrix);
  m_OpenGL->GetProjectionMatrix(projectionMatrix);

  m_OpenGL->MatrixRotationY(worldMatrix, rotation);
  m_Light->GetDirection(lightDirection);
  m_Light->GetDiffuseColor(diffuseLightColor);

  m_OpenGL->MatrixRotationY(rotateMatrix, rotation);
  m_OpenGL->MatrixTranslation(translateMatrix, -2.0f, 0.0f, 0.0f);

  m_OpenGL->MatrixMultiply(worldMatrix, rotateMatrix, translateMatrix);

  // Set the color shader as the current shader program and set the matrices
  // that it will use for rendering.
  result = m_LightShader->SetShaderParameters(worldMatrix, viewMatrix,
                                              projectionMatrix, lightDirection,
                                              diffuseLightColor);
  if (!result) {
    return false;
  }
  // Render the model.
  m_Model->Render();

  m_OpenGL->MatrixScale(scaleMatrix, 0.5f, 0.5f, 0.5f);
  m_OpenGL->MatrixRotationY(rotateMatrix, rotation);
  m_OpenGL->MatrixTranslation(translateMatrix, 2.0f, 0.0f, 0.0f);

  m_OpenGL->MatrixMultiply(srMatrix, scaleMatrix, rotateMatrix);
  m_OpenGL->MatrixMultiply(worldMatrix, srMatrix, translateMatrix);

  result = m_LightShader->SetShaderParameters(worldMatrix, viewMatrix,
                                              projectionMatrix, lightDirection,
                                              diffuseLightColor);
  if (!result) {
    return false;
  }

  // Render the model.
  m_Model->Render();

  m_OpenGL->EndScene();

  return true;
}
