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
}

ApplicationClass::ApplicationClass(const ApplicationClass &other) {}

ApplicationClass::~ApplicationClass() {}

bool ApplicationClass::Initialize(Display *display, Window win, int screenWidth,
                                  int screenHeight) {
  char modelFilename1[128], modelFilename2[128], textureFilename1[128],
      textureFilename2[128];
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

  m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
  m_Camera->Render();

  // Set the file names of the models.
  strcpy(modelFilename1, "./data/cube.txt");
  strcpy(modelFilename2, "./data/floor.txt");

  // Set the file names of the textures.
  strcpy(textureFilename1, "./data/stone01.tga");
  strcpy(textureFilename2, "./data/blue01.tga");

  // Create and initialize the cube model object.
  m_CubeModel = new ModelClass;

  result =
      m_CubeModel->Initialize(m_OpenGL, modelFilename1, textureFilename1, true);
  if (!result) {
    return false;
  }

  // Create and initialize the floor model object.
  m_FloorModel = new ModelClass;

  result = m_FloorModel->Initialize(m_OpenGL, modelFilename2, textureFilename2,
                                    true);
  if (!result) {
    return false;
  }

  // Create and initialize the texture shader object.
  m_TextureShader = new TextureShaderClass;

  result = m_TextureShader->Initialize(m_OpenGL);
  if (!result) {
    return false;
  }

  // Create and initialize the reflection shader object.
  m_ReflectionShader = new ReflectionShaderClass;

  result = m_ReflectionShader->Initialize(m_OpenGL);
  if (!result) {
    return false;
  }

  // Create and initialize the render to texture object.
  m_RenderTexture = new RenderTextureClass;

  // Set the texture to use unit texture unit 1, since the floor texture will be
  // using unit 0.
  result = m_RenderTexture->Initialize(m_OpenGL, screenWidth, screenHeight,
                                       SCREEN_NEAR, SCREEN_DEPTH, 0, 1);
  if (!result) {
    return false;
  }

  return true;
}
void ApplicationClass::Shutdown() {
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
  static float rotation = 360.0f;
  bool result;

  // Check if the escape key has been pressed, if so quit.
  if (Input->IsEscapePressed() == true) {
    return false;
  }
  // Update the rotation variable each frame.
  rotation -= 0.0174532925f * 1.0f;
  if (rotation <= 0.0f) {
    rotation += 360.0f;
  }
  // Render the entire scene as a reflection to the texture first.
  result = RenderReflectionToTexture(rotation);
  if (!result) {
    return false;
  }

  // Render the final graphics scene.
  result = Render(rotation);
  if (!result) {
    return false;
  }
  return true;
}
bool ApplicationClass::RenderReflectionToTexture(float rotation) {
  float worldMatrix[16], reflectionViewMatrix[16], projectionMatrix[16];
  bool result;

  // Set the render target to be the render texture and clear it.
  m_RenderTexture->SetRenderTarget();
  m_RenderTexture->ClearRenderTarget(0.0f, 0.0f, 0.0f, 1.0f);

  // Use the camera to calculate the reflection matrix.
  m_Camera->RenderReflection(-1.5f);

  // Get the reflection view matrix.
  m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

  // Get the camera reflection view matrix instead of the regular camera view
  // matrix.  Also good practice to use the projection matrix from the render
  // texture.
  m_OpenGL->GetWorldMatrix(worldMatrix);
  m_RenderTexture->GetProjectionMatrix(projectionMatrix);

  // Rotate the world matrix by the rotation value so that the cube will spin.
  m_OpenGL->MatrixRotationY(worldMatrix, rotation);

  // Set the texture shader as the current shader program and set the matrices
  // that it will use for rendering.
  result = m_TextureShader->SetShaderParameters(
      worldMatrix, reflectionViewMatrix, projectionMatrix);
  if (!result) {
    return false;
  }

  // Render the cube model using the texture shader and the reflection view
  // matrix.
  m_CubeModel->Render();

  // Reset the render target back to the original back buffer and not the render
  // to texture anymore.  And reset the viewport back to the original.
  m_OpenGL->SetBackBufferRenderTarget();
  m_OpenGL->ResetViewport();

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
  float worldMatrix[16], viewMatrix[16], projectionMatrix[16],
      reflectionViewMatrix[16];
  bool result;

  // Clear the buffers to begin the scene.
  m_OpenGL->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

  // Get the world, view, and projection matrices from the opengl and camera
  // objects.
  m_OpenGL->GetWorldMatrix(worldMatrix);
  m_Camera->GetViewMatrix(viewMatrix);
  m_OpenGL->GetProjectionMatrix(projectionMatrix);

  // Rotate the world matrix by the rotation value so that the cube will spin.
  m_OpenGL->MatrixRotationY(worldMatrix, rotation);

  // Set the texture shader as the current shader program and set the matrices
  // that it will use for rendering.
  result = m_TextureShader->SetShaderParameters(worldMatrix, viewMatrix,
                                                projectionMatrix);
  if (!result) {
    return false;
  }

  // Render the cube model as normal with the texture shader.
  m_CubeModel->Render();

  // Now get the world matrix again and translate down for the floor model
  // to render underneath the cube.
  m_OpenGL->GetWorldMatrix(worldMatrix);
  m_OpenGL->MatrixTranslation(worldMatrix, 0.0f, -1.5f, 0.0f);

  // Get the camera reflection view matrix for the reflection shader.
  m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

  // Render the floor model using the reflection shader, reflection texture, and
  // reflection view matrix.
  result = m_ReflectionShader->SetShaderParameters(
      worldMatrix, viewMatrix, projectionMatrix, reflectionViewMatrix);
  if (!result) {
    return false;
  }

  // Set the render texture as the texture to be used in texture unit 1 for the
  // reflection shader.
  m_RenderTexture->SetTexture();

  // Render the floor model using the reflection shader and using texture unit 0
  // for the floor texture and texture unit 1 for the reflection render texture.
  m_FloorModel->Render();

  // Present the rendered scene to the screen.
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
