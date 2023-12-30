#include "system.h"
#include "application.h"
#include <stdio.h>
#include <string.h>

bool InitializeSystem(System *system, TutorialData *tutorial) {
    int screenWidth = 0, screenHeight = 0;
    bool result;

    system->input = (Input *)malloc(sizeof(Input));
    InitializeInput(system->input);

    result = InitializeWindow(system, screenWidth, screenHeight);
    if (!result) {
        printf("ERROR: Failed to initialize window\n");
        return false;
    }
    system->application = (Application *)malloc(sizeof(Application));

    result = InitializeApplication(system->application, system->videoDisplay, system->hwnd, screenWidth, screenHeight,
                                   tutorial);
    if (!result) {
        printf("ERROR: Failed to initialize application\n");
        return false;
    }
    printf("INFO: Initialized Application\n");
    return true;
}
void ShutdownWindow(System *system) {
    glXMakeCurrent(system->videoDisplay, None, NULL);
    glXDestroyContext(system->videoDisplay, system->renderingContext);
    XUnmapWindow(system->videoDisplay, system->hwnd);
    XDestroyWindow(system->videoDisplay, system->hwnd);
    XCloseDisplay(system->videoDisplay);

    return;
}
void ShutdownSystem(System *system) {
    if (system->application) {
        ShutdownApplication(system->application);
        free(system->application);
        printf("Shutdown Application\n");
    }
    ShutdownWindow(system);
    printf("Shutdown Window\n");
}
void Frame(System *system, TutorialData *tutorial) {
    while (true) {
        ReadInput(system);

        if (!Frame(system->application, system->input, tutorial->renderApplicationPtr, tutorial->rotationSpeed)) {
            break;
        }
    }
}
bool InitializeWindow(System *system, int &screenWidth, int &screenHeight) {
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

    system->videoDisplay = XOpenDisplay(NULL);
    if (system->videoDisplay == NULL) {
        printf("ERROR: Failed to open display\n");
        return false;
    }

    rootWindow = DefaultRootWindow(system->videoDisplay);

    attributeList[0] = GLX_RGBA;       // Support for 24 bit color and an alpha channel.
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

    visualInfo = glXChooseVisual(system->videoDisplay, 0, attributeList);
    if (visualInfo == NULL) {
        printf("ERROR: Failed to choose visuals\n");
        return false;
    }

    colorMap = XCreateColormap(system->videoDisplay, rootWindow, visualInfo->visual, AllocNone);

    setWindowAttributes.colormap = colorMap;
    setWindowAttributes.event_mask = KeyPressMask | KeyReleaseMask;

    if (FULL_SCREEN) {
        defaultScreen = XDefaultScreenOfDisplay(system->videoDisplay);
        screenWidth = XWidthOfScreen(defaultScreen);
        screenHeight = XHeightOfScreen(defaultScreen);

    } else {

        screenWidth = 1024;
        screenHeight = 768;
    }

    system->hwnd =
        XCreateWindow(system->videoDisplay, rootWindow, 0, 0, screenWidth, screenHeight, 0, visualInfo->depth,
                      InputOutput, visualInfo->visual, CWColormap | CWEventMask, &setWindowAttributes);
    XMapWindow(system->videoDisplay, system->hwnd);

    XStoreName(system->videoDisplay, system->hwnd, "Window");

    if (FULL_SCREEN) {
        wmState = XInternAtom(system->videoDisplay, "_NET_WM_STATE", False);
        fullScreenState = XInternAtom(system->videoDisplay, "_NET_WM_STATE_FULLSCREEN", False);

        memset(&fullScreenEvent, 0, sizeof(fullScreenEvent));

        fullScreenEvent.type = ClientMessage;
        fullScreenEvent.xclient.window = system->hwnd;
        fullScreenEvent.xclient.message_type = wmState;
        fullScreenEvent.xclient.format = 32;
        fullScreenEvent.xclient.data.l[0] = 1;
        fullScreenEvent.xclient.data.l[1] = fullScreenState;
        fullScreenEvent.xclient.data.l[2] = 0;

        XSendEvent(system->videoDisplay, DefaultRootWindow(system->videoDisplay), False,
                   SubstructureRedirectMask | SubstructureNotifyMask, &fullScreenEvent);

        motifHints = XInternAtom(system->videoDisplay, "_MOTIF_WM_HINTS", False);

        motifHintList[0] = 2;
        motifHintList[1] = 0;
        motifHintList[2] = 0;
        motifHintList[3] = 0;
        motifHintList[4] = 0;

        XChangeProperty(system->videoDisplay, system->hwnd, motifHints, motifHints, 32, PropModeReplace,
                        (unsigned char *)&motifHintList, 5);

        XFlush(system->videoDisplay);
    }
    system->renderingContext = glXCreateContext(system->videoDisplay, visualInfo, NULL, GL_TRUE);
    if (system->renderingContext == NULL) {
        return false;
    }

    result = glXMakeCurrent(system->videoDisplay, system->hwnd, system->renderingContext);
    if (!result) {
        return false;
    }

    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    if (majorVersion < 4) {
        return false;
    }

    result = glXIsDirect(system->videoDisplay, system->renderingContext);
    if (!result) {
        return false;
    }
    return true;
}
void ReadInput(System *system) {
    XEvent event;
    long eventMask;
    bool foundEvent;
    char keyBuffer[32];
    KeySym keySymbol;

    eventMask = KeyPressMask | KeyReleaseMask;

    foundEvent = XCheckWindowEvent(system->videoDisplay, system->hwnd, eventMask, &event);
    if (foundEvent) {
        if (event.type == KeyPress) {
            XLookupString(&event.xkey, keyBuffer, sizeof(keyBuffer), &keySymbol, NULL);
            KeyDown(system->input, (int)keySymbol);
        }

        if (event.type == KeyRelease) {
            XLookupString(&event.xkey, keyBuffer, sizeof(keyBuffer), &keySymbol, NULL);
            KeyUp(system->input, (int)keySymbol);
        }
    }

    return;
}
