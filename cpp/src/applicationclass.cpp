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
  m_ClipPlaneShader = 0;
  m_TranslateShader = 0;
  m_TransparentShader = 0;
  m_ReflectionShader = 0;
  m_GroundModel = 0;
  m_WallModel = 0;
  m_BathModel = 0;
  m_WaterModel = 0;
  m_RefractionTexture = 0;
  m_ReflectionTexture = 0;
  m_RefractionShader = 0;
  m_WaterShader = 0;
  m_GlassShader = 0;
  m_FireShader = 0;
}

ApplicationClass::ApplicationClass(const ApplicationClass &other) {}

ApplicationClass::~ApplicationClass() {}

bool ApplicationClass::Initialize(Display *display, Window win, int screenWidth,
                                  int screenHeight) {
  char modelFilename[128];
  char textureFilename1[128], textureFilename2[128], textureFilename3[128];
  bool result;

  // Create and initialize the OpenGL object.
  m_OpenGL = new OpenGLClass;

  result = m_OpenGL->Initialize(display, win, screenWidth, screenHeight,
                                SCREEN_NEAR, SCREEN_DEPTH, VSYNC_ENABLED);
  if (!result) {
    return false;
  }

  // Create and initialize the camera object.
  m_Camera = new CameraClass;
  m_Camera->SetPosition(0.0f, 0.0f, -5.0f);
  m_Camera->Render();

  strcpy(modelFilename, "./data/square.txt");

  strcpy(textureFilename1, "./data/fire01.tga");
  strcpy(textureFilename2, "./data/noise01.tga");
  strcpy(textureFilename3, "./data/alpha01.tga");

  m_Model = new ModelClass;
  result = m_Model->Initialize(m_OpenGL, modelFilename, textureFilename1, false,
                               textureFilename2, true, textureFilename3, false);
  if (!result) {
    printf("Failed to initialize model\n");
    return false;
  }

  m_FireShader = new FireShaderClass;
  result = m_FireShader->Initialize(m_OpenGL);
  if (!result) {
    return false;
  }

  return true;
}
void ApplicationClass::Shutdown() {
  if (m_FireShader) {
    m_FireShader->Shutdown();
    delete m_FireShader;
    m_FireShader = 0;
  }
  if (m_GlassShader) {
    m_GlassShader->Shutdown();
    delete m_GlassShader;
    m_GlassShader = 0;
  }
  if (m_WaterShader) {
    m_WaterShader->Shutdown();
    delete m_WaterShader;
    m_WaterShader = 0;
  }
  if (m_RefractionShader) {
    m_RefractionShader->Shutdown();
    delete m_RefractionShader;
    m_RefractionShader = 0;
  }
  if (m_LightShader) {
    m_LightShader->Shutdown();
    delete m_LightShader;
    m_LightShader = 0;
  }
  if (m_ReflectionTexture) {
    m_ReflectionTexture->Shutdown();
    delete m_ReflectionTexture;
    m_ReflectionTexture = 0;
  }
  if (m_RefractionTexture) {
    m_RefractionTexture->Shutdown();
    delete m_RefractionTexture;
    m_RefractionTexture = 0;
  }
  if (m_WaterModel) {
    m_WaterModel->Shutdown();
    delete m_WaterModel;
    m_WaterModel = 0;
  }
  if (m_BathModel) {
    m_BathModel->Shutdown();
    delete m_BathModel;
    m_BathModel = 0;
  }
  if (m_WallModel) {
    m_WallModel->Shutdown();
    delete m_WallModel;
    m_WallModel = 0;
  }
  if (m_GroundModel) {
    m_GroundModel->Shutdown();
    delete m_GroundModel;
    m_GroundModel = 0;
  }
  if (m_ReflectionShader) {
    m_ReflectionShader->Shutdown();
    delete m_ReflectionShader;
    m_ReflectionShader = 0;
  }
  if (m_CubeModel) {
    m_CubeModel->Shutdown();
    delete m_CubeModel;
    m_CubeModel = 0;
  }
  if (m_FloorModel) {
    m_FloorModel->Shutdown();
    delete m_FloorModel;
    m_FloorModel = 0;
  }
  if (m_TransparentShader) {
    m_TransparentShader->Shutdown();
    delete m_TransparentShader;
    m_TransparentShader = 0;
  }
  if (m_Model1) {
    m_Model1->Shutdown();
    delete m_Model1;
    m_Model1 = 0;
  }
  if (m_Model2) {
    m_Model2->Shutdown();
    delete m_Model2;
    m_Model2 = 0;
  }
  if (m_TranslateShader) {
    m_TranslateShader->Shutdown();
    delete m_TranslateShader;
    m_TranslateShader = 0;
  }
  if (m_ClipPlaneShader) {
    m_ClipPlaneShader->Shutdown();
    delete m_ClipPlaneShader;
    m_ClipPlaneShader = 0;
  }
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
  bool result;

  // Check if the escape key has been pressed, if so quit.
  if (Input->IsEscapePressed() == true) {
    return false;
  }

  result = Render();
  if (!result) {
    return false;
  }
  return true;
}
bool ApplicationClass::RenderRefractionToTexture() {
  float worldMatrix[16], viewMatrix[16], projectionMatrix[16];
  float clipPlane[4];
  float diffuseLightColor[4], lightDirection[3], ambientLight[4];
  bool result;

  clipPlane[0] = 0.0f;
  clipPlane[0] = -1.0f;
  clipPlane[2] = 0.0f;
  clipPlane[3] = m_waterHeight + 0.1f;

  m_RefractionTexture->SetRenderTarget();
  m_RefractionTexture->ClearRenderTarget(0.0f, 0.0f, 0.0f, 1.0f);

  m_OpenGL->GetWorldMatrix(worldMatrix);
  m_Camera->GetViewMatrix(viewMatrix);
  m_RefractionTexture->GetProjectionMatrix(projectionMatrix);

  m_Light->GetDirection(lightDirection);
  m_Light->GetDiffuseColor(diffuseLightColor);
  m_Light->GetAmbientLight(ambientLight);

  m_OpenGL->EnableClipping();

  m_OpenGL->MatrixTranslation(worldMatrix, 0.0f, 2.0f, 0.0f);

  result = m_RefractionShader->SetShaderParameters(
      worldMatrix, viewMatrix, projectionMatrix, lightDirection,
      diffuseLightColor, ambientLight, clipPlane);
  if (!result) {
    return false;
  }

  m_BathModel->Render();

  m_OpenGL->DisableClipping();
  m_OpenGL->SetBackBufferRenderTarget();
  m_OpenGL->ResetViewport();

  return true;
}

bool ApplicationClass::RenderReflectionToTexture() {
  float worldMatrix[16], reflectionViewMatrix[16], projectionMatrix[16];
  float diffuseLightColor[4], lightDirection[3], ambientLight[4];
  bool result;

  // Set the render target to be the render texture and clear it.
  m_ReflectionTexture->SetRenderTarget();
  m_ReflectionTexture->ClearRenderTarget(0.0f, 0.0f, 0.0f, 1.0f);

  m_Camera->RenderReflection(m_waterHeight);
  m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

  m_OpenGL->GetWorldMatrix(worldMatrix);
  m_ReflectionTexture->GetProjectionMatrix(projectionMatrix);

  m_Light->GetDirection(lightDirection);
  m_Light->GetDiffuseColor(diffuseLightColor);
  m_Light->GetAmbientLight(ambientLight);

  m_OpenGL->MatrixTranslation(worldMatrix, 0.0f, 6.0f, 8.0f);

  result = m_LightShader->SetShaderParameters(worldMatrix, reflectionViewMatrix,
                                              projectionMatrix, lightDirection,
                                              diffuseLightColor, ambientLight);
  if (!result) {
    return false;
  }

  m_WallModel->Render();

  m_OpenGL->SetBackBufferRenderTarget();
  m_OpenGL->ResetViewport();

  return true;
}

bool ApplicationClass::RenderSceneToTexture(float rotation) {
  float worldMatrix[16], viewMatrix[16], projectionMatrix[16];
  bool result;

  // Set the render target to be the render texture and clear it.
  m_RenderTexture->SetRenderTarget();
  m_RenderTexture->ClearRenderTarget(0.0f, 0.0f, 0.0f, 1.0f);

  m_OpenGL->GetWorldMatrix(worldMatrix);
  m_Camera->GetViewMatrix(viewMatrix);
  m_RenderTexture->GetProjectionMatrix(projectionMatrix);

  m_OpenGL->MatrixRotationY(worldMatrix, rotation);

  result = m_TextureShader->SetShaderParameters(worldMatrix, viewMatrix,
                                                projectionMatrix);
  if (!result) {
    return false;
  }

  m_Model->Render();

  m_OpenGL->SetBackBufferRenderTarget();
  m_OpenGL->ResetViewport();

  return true;
}

bool ApplicationClass::Render() {
  float worldMatrix[16], viewMatrix[16], projectionMatrix[16];
  float scrollSpeeds[3], scales[3], distortion1[2], distortion2[2],
      distortion3[2];
  float distortionScale, distortionBias;
  bool result;

  static float frameTime = 0.0f;

  frameTime += 0.01f;
  if (frameTime > 1000.0f) {
    frameTime = 0.0f;
  }

  scrollSpeeds[0] = 1.3f;
  scrollSpeeds[1] = 2.1f;
  scrollSpeeds[2] = 2.3f;

  scales[0] = 1.0f;
  scales[1] = 2.0f;
  scales[2] = 3.0f;

  distortion1[0] = 0.1f;
  distortion1[1] = 0.2f;

  distortion2[0] = 0.1f;
  distortion2[1] = 0.3f;

  distortion3[0] = 0.1f;
  distortion3[1] = 0.1f;

  distortionScale = 0.8f;
  distortionBias = 0.5f;

  m_OpenGL->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

  m_OpenGL->GetWorldMatrix(worldMatrix);
  m_Camera->GetViewMatrix(viewMatrix);
  m_OpenGL->GetProjectionMatrix(projectionMatrix);

  m_OpenGL->EnableAlphaBlending();
  result = m_FireShader->SetShaderParameters(
      worldMatrix, viewMatrix, projectionMatrix, frameTime, scrollSpeeds,
      scales, distortion1, distortion2, distortion3, distortionScale,
      distortionBias);
  if (!result) {
    return false;
  }

  m_Model->Render();

  m_OpenGL->DisableAlphaBlending();

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
