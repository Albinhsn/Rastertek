#ifndef APPLICATION_H
#define APPLICATION_H

#include "camera.h"
#include "input.h"
#include "model.h"
#include "opengl.h"
#include "shader.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_NEAR = 0.3f;
const float SCREEN_DEPTH = 1000.0f;

struct Application {
    OpenGL *openGL;
    Camera *camera;
    Shader *shader;
    Model *model;
};
bool RenderApplication(Application *application);
bool InitializeApplication(Application *application, Display *display, Window window, int screenWidth,
                           int screenHeight);
void ShutdownApplication(Application *application);
bool Frame(Application *application, Input *);

#endif
