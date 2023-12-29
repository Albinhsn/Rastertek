#ifndef SYSTEM
#define SYSTEM

#include "application.h"
#include "input.h"

struct System {
    Application *application;
    Input *input;
    Display *videoDisplay;
    Window hwnd;
    GLXContext renderingContext;
};

bool InitializeSystem(System *system, int app);
void ShutdownSystem(System *system);
void Frame(System *system);
bool InitializeWindow(System *system, int & screenWidth, int & screenHeight);
void ShutdownWindow();
void ReadInput(System *system);

#endif
