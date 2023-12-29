#ifndef APPLICATION_H
#define APPLICATION_H

#include "bitmap.h"
#include "camera.h"
#include "input.h"
#include "model.h"
#include "opengl.h"
#include "shader.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_NEAR = 0.3f;
const float SCREEN_DEPTH = 1000.0f;

struct Application;

struct TutorialData {
    // Model 
    const char **models;
    int modelLen;
    const char **textures;
    int textureLen;
    const char *vertexShaderName;
    const char *fragmentShaderName;
    const char **variables;
    int variablesLen;
    int cameraX, cameraY, cameraZ;
    void (*enableAttribPtr)();
    bool (*renderApplicationPtr)(Application *application, float rotation);
    float rotationSpeed;
    bool wrap;

    // Bitmap
    Bitmap * bitmap;
    const char * bitmapFilename;
};

struct Application {
    OpenGL *openGL;
    Camera *camera;
    Shader *shader;
    Model *model;
    Bitmap *bitmap;
};
bool InitializeApplication(Application *application, Display *display, Window window, int screenWidth, int screenHeight,
                           TutorialData *tutorial);
void ShutdownApplication(Application *application);
bool Frame(Application *application, Input *input,
           bool (*renderApplicationPtr)(Application *application, float rotation), float rotationSpeed);

#endif
