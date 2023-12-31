#ifndef APPLICATION_H
#define APPLICATION_H

#include "bitmap.h"
#include "camera.h"
#include "font.h"
#include "input.h"
#include "model.h"
#include "opengl.h"
#include "shader.h"
#include "sprite.h"
#include "text.h"
#include "timer.h"
#include "fps.h"

const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = false;
const float SCREEN_NEAR = 0.3f;
const float SCREEN_DEPTH = 1000.0f;

struct Application;

enum TutorialEnum { MODEL, SPRITE, BITMAP, FONT };
struct TutorialText {
    const char *text;
    float color[4];
    int fontSize;
    int posX, posY;
};

struct TutorialData {
    TutorialText *textStrings;
    int textLen;
    TutorialEnum tutorial;
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
    const char *bitmapFilename;

    // Sprite
    const char *spriteFilename;

    // Mouse
    bool mouse;
};

struct Application {
    Shader * fpsShader;
    OpenGL *openGL;
    Camera *camera;
    Shader *shader;
    Model *model;
    Bitmap *bitmap;
    Sprite *sprite;
    Timer *timer;
    m_Font *font;
    int textLen;
    Text *text;
    Text * fpsText;
    FPS * fps;
    int previousFPS;
    bool mouse;
};
bool InitializeApplication(Application *application, Display *display, Window window, int screenWidth, int screenHeight,
                           TutorialData *tutorial);
void ShutdownApplication(Application *application);
bool Frame(Application *application, Input *input,
           bool (*renderApplicationPtr)(Application *application, float rotation), float rotationSpeed);

bool RenderFpsString(Application *application);
#endif
