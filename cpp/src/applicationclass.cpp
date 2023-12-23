#include "applicationclass.h"
#include "normalmapshaderclass.h"
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
  m_MouseStrings = 0;
  m_MultiTextureShader = 0;
  m_Model = 0;
  m_LightMapShader = 0;
  m_AlphaMapShader = 0;
  m_NormalMapShader = 0;
  m_SpecMapShader = 0;
  m_Frustum = 0;
  m_ModelList = 0;
  m_Position = 0;
  m_RenderCountString = 0;
  m_RenderTexture = 0;
  m_DisplayPlane = 0;
  m_FogShader = 0;
}

ApplicationClass::ApplicationClass(const ApplicationClass &other) {}

ApplicationClass::~ApplicationClass() {}

bool ApplicationClass::Initialize(Display *display, Window win, int screenWidth,
                                  int screenHeight) {
  char modelFilename[128], textureFilename[128];
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
    return false;
  }

  m_FogShader = new FogShaderClass;
  result = m_FogShader->Initialize(m_OpenGL);
  if (!result) {
    return false;
  }
  printf("INFO: Initialized system\n");

  return true;
}

void ApplicationClass::Shutdown() {
  if (m_FogShader) {
    m_FogShader->Shutdown();
    delete m_FogShader;
    m_FogShader = 0;
  }
  if (m_DisplayPlane) {
    m_DisplayPlane->Shutdown();
    delete m_DisplayPlane;
    m_DisplayPlane = 0;
  }
  if (m_RenderTexture) {
    m_RenderTexture->Shutdown();
    delete m_RenderTexture;
    m_RenderTexture = 0;
  }
  if (m_Frustum) {
    delete m_Frustum;
    m_Frustum = 0;
  }
  if (m_ModelList) {
    m_ModelList->Shutdown();
    delete m_ModelList;
    m_ModelList = 0;
  }
  if (m_Position) {
    delete m_Position;
    m_Position = 0;
  }
  if (m_RenderCountString) {
    m_RenderCountString->Shutdown();
    delete m_RenderCountString;
    m_Position = 0;
  }
  if (m_ShaderManager) {
    m_ShaderManager->Shutdown();
    delete m_ShaderManager;
    m_ShaderManager = 0;
  }
  if (m_Light) {
    delete m_Light;
    m_Light = 0;
  }
  if (m_NormalMapShader) {
    m_NormalMapShader->Shutdown();
    delete m_NormalMapShader;
    m_NormalMapShader = 0;
  }
  if (m_AlphaMapShader) {
    m_AlphaMapShader->Shutdown();
    delete m_AlphaMapShader;
    m_AlphaMapShader = 0;
  }
  if (m_MultiTextureShader) {
    m_MultiTextureShader->Shutdown();
    delete m_MultiTextureShader;
    m_MultiTextureShader = 0;
  }
  if (m_LightMapShader) {
    m_LightMapShader->Shutdown();
    delete m_LightMapShader;
    m_LightMapShader = 0;
  }
  if (m_MouseStrings) {
    m_MouseStrings[0].Shutdown();
    m_MouseStrings[1].Shutdown();
    m_MouseStrings[2].Shutdown();
    delete[] m_MouseStrings;
    m_MouseStrings = 0;
  }
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
  if (m_SpecMapShader) {
    m_SpecMapShader->Shutdown();
    delete m_SpecMapShader;
    m_SpecMapShader = 0;
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

  unsigned int error = glGetError();
  if (error != GL_NO_ERROR) {
    cout << "GL Error: " << error << endl;
  }

  return;
}

bool ApplicationClass::Frame(InputClass *Input) {
  static float rotation = 360.0f;
  bool result;

  // Check if the escape key has been pressed, if so quit.
  if (Input->IsEscapePressed() == true) {
    return false;
  }

  rotation -= 0.0174532925f * 1.0f;
  if (rotation <= 0.0f) {
    rotation += 360.0f;
  }

  // Render the final graphics scene.
  result = Render(rotation);
  if (!result) {
    return false;
  }
  return true;
}

bool ApplicationClass::RenderSceneToTexture(float rotation) {
  float worldMatrix[16], viewMatrix[16], projectionMatrix[16];
  bool result;

  // Set the render target to be the render texture and clear it.
  m_RenderTexture->SetRenderTarget();
  m_RenderTexture->ClearRenderTarget(1.0f, 0.5f, 0.0f, 1.0f);

  // Set the position of the camera for viewing the cube.
  m_Camera->SetPosition(0.0f, 0.0f, -5.0f);
  m_Camera->Render();

  // Get the matrices.
  m_OpenGL->GetWorldMatrix(worldMatrix);
  m_Camera->GetViewMatrix(viewMatrix);
  m_RenderTexture->GetProjectionMatrix(projectionMatrix);

  // Rotate the world matrix by the rotation value so that the triangle will
  // spin.
  m_OpenGL->MatrixRotationY(worldMatrix, rotation);

  // Set the texture shader as the current shader program and set the matrices
  // that it will use for rendering.
  result = m_TextureShader->SetShaderParameters(worldMatrix, viewMatrix,
                                                projectionMatrix);
  if (!result) {
    return false;
  }

  // Render the model.
  m_Model->Render();

  // Reset the render target back to the original back buffer and not the
  // render to texture anymore.  And reset the viewport back to the
  // original.
  m_OpenGL->SetBackBufferRenderTarget();
  m_OpenGL->ResetViewport();

  return true;
}

bool ApplicationClass::Render(float rotation) {
  float worldMatrix[16], viewMatrix[16], projectionMatrix[16], fogPosition[2];
  float fogColor, fogStart, fogEnd;
  bool result;

  fogColor = 0.5f;
  fogStart = 0.0f;
  fogEnd = 10.0f;

  fogPosition[0] = fogStart;
  fogPosition[1] = fogEnd;

  m_OpenGL->BeginScene(fogColor, fogColor, fogColor, 1.0f);

  m_OpenGL->GetWorldMatrix(worldMatrix);
  m_Camera->GetViewMatrix(viewMatrix);
  m_OpenGL->GetProjectionMatrix(projectionMatrix);

  m_OpenGL->MatrixRotationY(worldMatrix, rotation);

  result = m_FogShader->SetShaderParameters(worldMatrix, viewMatrix,
                                            projectionMatrix, fogPosition);
  if (!result) {
    return false;
  }

  m_Model->Render();

  m_OpenGL->EndScene();

  return true;
}

bool ApplicationClass::UpdateRenderCountString(int renderCount) {
  char tempString[16], finalString[32];
  bool result;

  sprintf(tempString, "%d", renderCount);
  strcpy(finalString, "Render Count: ");
  strcat(finalString, tempString);
  result = m_RenderCountString->UpdateText(m_Font, finalString, 10, 10, 1.0f,
                                           1.0f, 1.0f);
  if (!result) {
    return false;
  }
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
bool ApplicationClass::UpdateMouseStrings(int mouseX, int mouseY,
                                          bool mouseDown) {
  char tempString[16], finalString[32];
  bool result;

  // Convert the mouse X integer to string format.
  sprintf(tempString, "%d", mouseX);

  // Setup the mouse X string.
  strcpy(finalString, "Mouse X: ");
  strcat(finalString, tempString);

  // Update the sentence vertex buffer with the new string information.
  result = m_MouseStrings[0].UpdateText(m_Font, finalString, 10, 10, 1.0f, 1.0f,
                                        1.0f);
  if (!result) {
    return false;
  }

  // Convert the mouse Y integer to string format.
  sprintf(tempString, "%d", mouseY);

  // Setup the mouse Y string.
  strcpy(finalString, "Mouse Y: ");
  strcat(finalString, tempString);

  // Update the sentence vertex buffer with the new string information.
  result = m_MouseStrings[1].UpdateText(m_Font, finalString, 10, 35, 1.0f, 1.0f,
                                        1.0f);
  if (!result) {
    return false;
  }

  // Setup the mouse button string.
  if (mouseDown) {
    strcpy(finalString, "Mouse Button: Yes");
  } else {
    strcpy(finalString, "Mouse Button: No");
  }

  // Update the sentence vertex buffer with the new string information.
  result = m_MouseStrings[2].UpdateText(m_Font, finalString, 10, 60, 1.0f, 1.0f,
                                        1.0f);
  if (!result) {
    return false;
  }

  return true;
}
