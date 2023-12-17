#ifndef APPLICATION_H
#define APPLICATION_H

#include "camera.h"
#include "opengl.h"
#include "texture.h"
#include "model.h"
#include "input.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_NEAR = 0.3f;
const float SCREEN_DEPTH = 1000.0f;

bool RenderApplication();

struct Application {
        OpenGL *openGL;
        Camera *camera;
        Texture *texture;
        Model *model;
};

#endif
