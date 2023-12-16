#include "applicationclass.h"

ApplicationClass::ApplicationClass() { m_OpenGL = 0; }

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

  return true;
}

void ApplicationClass::Shutdown() {
  if (m_OpenGL) {
    m_OpenGL->Shutdown();
    delete m_OpenGL;
    m_OpenGL = 0;
  }

  return;
}

bool ApplicationClass::Frame(InputClass*Input){
  bool result;

  if(Input->IsEscapePressed() ==true){
    return false;
  }

  result = Render();
  if(!result){
    return false;
  }

  return true;
}

bool ApplicationClass::Render(){
  m_OpenGL->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

  m_OpenGL->EndScene();

  return true;
}
