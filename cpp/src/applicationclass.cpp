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
  m_MouseStrings = 0;
  m_MultiTextureShader = 0;
  m_Model = 0;
  m_LightMapShader = 0;
}

ApplicationClass::ApplicationClass(const ApplicationClass &other) {}

ApplicationClass::~ApplicationClass() {}

bool ApplicationClass::Initialize(Display *display, Window win, int screenWidth,
                                  int screenHeight) {
  char modelFilename[128], textureFilename1[128], textureFilename2[128];
  bool result;

  m_OpenGL = new OpenGLClass;

  result = m_OpenGL->Initialize(display, win, screenWidth, screenHeight,
                                SCREEN_NEAR, SCREEN_DEPTH, VSYNC_ENABLED);
  if (!result) {
    printf("ERROR: Failed to initialize openGL\n");
    return false;
  }

  m_Camera = new CameraClass;
  m_Camera->SetPosition(0.0f, 0.0f, -5.0f);
  m_Camera->Render();

  m_LightMapShader = new LightMapShaderClass;

  result = m_LightMapShader->Initialize(m_OpenGL);
  if (!result) {
    printf("Failed to initialize light map shader\n");
    return false;
  }
  strcpy(modelFilename, "./data/square.txt");

  strcpy(textureFilename1, "./data/stone01.tga");
  strcpy(textureFilename2, "./data/light01.tga");

  m_Model = new ModelClass;

  result = m_Model->Initialize(m_OpenGL, modelFilename, textureFilename1,
                               textureFilename2, true);
  if (!result) {
    printf("Failed to initialize model\n");
    return false;
  }

  return true;
}

void ApplicationClass::Shutdown() {
  if (m_MultiTextureShader) {
    m_MultiTextureShader->Shutdown();
    delete m_MultiTextureShader;
    m_MultiTextureShader = 0;
  }
  if(m_LightMapShader){
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


 	// Clear the buffers to begin the scene.
    m_OpenGL->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

    // Get the world, view, and projection matrices from the opengl and camera objects.
    m_OpenGL->GetWorldMatrix(worldMatrix);
    m_Camera->GetViewMatrix(viewMatrix);
    m_OpenGL->GetProjectionMatrix(projectionMatrix);

    // Set the multitexture shader as active and set its parameters.
    result = m_LightMapShader->SetShaderParameters(worldMatrix, viewMatrix, projectionMatrix);
    if(!result)
    {
          return false;
    }

    // Render the model using the multitexture shader.
    m_Model->Render();

    // Present the rendered scene to the screen.
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
