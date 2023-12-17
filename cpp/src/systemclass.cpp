#include "systemclass.h"
#include <cstddef>
#include <cstdio>

SystemClass::SystemClass() {
  m_Input = 0;
  m_Application = 0;
}

SystemClass::SystemClass(const SystemClass &other) {}

SystemClass::~SystemClass() {}

bool SystemClass::Initialize() {
  int screenWidth, screenHeight;
  bool result;

  m_Input = new InputClass;
  m_Input->Initialize();

  screenWidth = 0;
  screenHeight = 0;

  result = InitializeWindow(screenWidth, screenHeight);
  if (!result) {
    printf("ERROR: Failed to initialize window\n");
    return false;
  }

  m_Application = new ApplicationClass;

  result = m_Application->Initialize(m_videoDisplay, m_hwnd, screenWidth,
                                     screenHeight);

  if (!result) {
    printf("ERROR: Failed to initialize application\n");
    return false;
  }
  return true;
}

void SystemClass::Shutdown() {
  if (m_Application) {
    m_Application->Shutdown();
    delete m_Application;
    m_Application = 0;
  }

  ShutdownWindow();

  if (m_Input) {
    delete m_Input;
    m_Input = 0;
  }
  return;
}

void SystemClass::Frame() {
  bool done, result;

  done = false;
  while (!done) {
    ReadInput();

    result = m_Application->Frame(m_Input);
    if (!result) {
      done = true;
    }
  }
  return;
}

bool SystemClass::InitializeWindow(int &screenWidth, int &screenHeight) {
  Window rootWindow;
  XVisualInfo *visualInfo;
  GLint attributeList[15];
  Colormap colorMap;
  XSetWindowAttributes setWindowAttributes;
  XWindowAttributes windowAttributes;
  Screen *defaultScreen;
  bool result, windowSet;
  int majorVersion;
  Atom wmState, fullScreenState, motifHints;
  XEvent fullScreenEvent;
  long motifHintList[5];

  m_videoDisplay = XOpenDisplay(NULL);
  if (m_videoDisplay == NULL) {
    printf("ERROR: Failed to open display\n");
    return false;
  }

  rootWindow = DefaultRootWindow(m_videoDisplay);

  attributeList[0] = GLX_RGBA; // Support for 24 bit color and an alpha channel.
  attributeList[1] = GLX_DEPTH_SIZE; // Support for 24 bit depth buffer.
  attributeList[2] = 24;
  attributeList[3] = GLX_STENCIL_SIZE; // Support for 8 bit stencil buffer.
  attributeList[4] = 8;
  attributeList[5] = GLX_DOUBLEBUFFER; // Support for double buffering.
  attributeList[6] = GLX_RED_SIZE;     // 8 bits for each channel.
  attributeList[7] = 8;
  attributeList[8] = GLX_GREEN_SIZE;
  attributeList[9] = 8;
  attributeList[10] = GLX_BLUE_SIZE;
  attributeList[11] = 8;
  attributeList[12] = GLX_ALPHA_SIZE;
  attributeList[13] = 8;
  attributeList[14] = None; // Null terminate the attribute list.

  visualInfo = glXChooseVisual(m_videoDisplay, 0, attributeList);
  if (visualInfo == NULL) {
    printf("ERROR: Failed to choose visuals\n");
    return false;
  }

  colorMap = XCreateColormap(m_videoDisplay, rootWindow, visualInfo->visual,
                             AllocNone);

  setWindowAttributes.colormap = colorMap;
  setWindowAttributes.event_mask = KeyPressMask | KeyReleaseMask;

  if (FULL_SCREEN) {
    defaultScreen = XDefaultScreenOfDisplay(m_videoDisplay);
    screenWidth = XWidthOfScreen(defaultScreen);
    screenHeight = XHeightOfScreen(defaultScreen);

  } else {

    screenWidth = 1024;
    screenHeight = 768;
  }

  m_hwnd =
      XCreateWindow(m_videoDisplay, rootWindow, 0, 0, screenWidth, screenHeight,
                    0, visualInfo->depth, InputOutput, visualInfo->visual,
                    CWColormap | CWEventMask, &setWindowAttributes);
  XMapWindow(m_videoDisplay, m_hwnd);

  XStoreName(m_videoDisplay, m_hwnd, "Window");

  if (FULL_SCREEN) {
    wmState = XInternAtom(m_videoDisplay, "_NET_WM_STATE", False);
    fullScreenState =
        XInternAtom(m_videoDisplay, "_NET_WM_STATE_FULLSCREEN", False);

    memset(&fullScreenEvent, 0, sizeof(fullScreenEvent));

    fullScreenEvent.type = ClientMessage;
    fullScreenEvent.xclient.window = m_hwnd;
    fullScreenEvent.xclient.message_type = wmState;
    fullScreenEvent.xclient.format = 32;
    fullScreenEvent.xclient.data.l[0] = 1;
    fullScreenEvent.xclient.data.l[1] = fullScreenState;
    fullScreenEvent.xclient.data.l[2] = 0;

    XSendEvent(m_videoDisplay, DefaultRootWindow(m_videoDisplay), False,
               SubstructureRedirectMask | SubstructureNotifyMask,
               &fullScreenEvent);

    motifHints = XInternAtom(m_videoDisplay, "_MOTIF_WM_HINTS", False);

    motifHintList[0] = 2;
    motifHintList[1] = 0;
    motifHintList[2] = 0;
    motifHintList[3] = 0;
    motifHintList[4] = 0;

    XChangeProperty(m_videoDisplay, m_hwnd, motifHints, motifHints, 32,
                    PropModeReplace, (unsigned char *)&motifHintList, 5);

    XFlush(m_videoDisplay);
  }
  m_renderingContext =
      glXCreateContext(m_videoDisplay, visualInfo, NULL, GL_TRUE);
  if (m_renderingContext == NULL) {
    return false;
  }

  result = glXMakeCurrent(m_videoDisplay, m_hwnd, m_renderingContext);
  if (!result) {
    return false;
  }

  glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
  if (majorVersion < 4) {
    return false;
  }

  result = glXIsDirect(m_videoDisplay, m_renderingContext);
  if (!result) {
    return true;
    return false;
  }
  return true;
}

void SystemClass::ShutdownWindow() {
  glXMakeCurrent(m_videoDisplay, None, NULL);
  glXDestroyContext(m_videoDisplay, m_renderingContext);
  XUnmapWindow(m_videoDisplay, m_hwnd);
  XDestroyWindow(m_videoDisplay, m_hwnd);
  XCloseDisplay(m_videoDisplay);

  return;
}

void SystemClass::ReadInput() {
  XEvent event;
  long eventMask;
  bool foundEvent;
  char keyBuffer[32];
  KeySym keySymbol;

  eventMask = KeyPressMask | KeyReleaseMask;

  foundEvent = XCheckWindowEvent(m_videoDisplay, m_hwnd, eventMask, &event);
  if (foundEvent) {
    if (event.type == KeyPress) {
      XLookupString(&event.xkey, keyBuffer, sizeof(keyBuffer), &keySymbol,
                    NULL);
      m_Input->KeyDown((int)keySymbol);
    }

    if (event.type == KeyRelease) {
      XLookupString(&event.xkey, keyBuffer, sizeof(keyBuffer), &keySymbol,
                    NULL);
      m_Input->KeyUp((int)keySymbol);
    }
  }

  return;
}
