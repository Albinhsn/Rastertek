#ifndef APPLICATION_H
#define APPLICATION_H

#include "bitmap.h"
#include "camera.h"
#include "font.h"
#include "fps.h"
#include "frustum.h"
#include "input.h"
#include "model.h"
#include "opengl.h"
#include "position.h"
#include "shader.h"
#include "sprite.h"
#include "text.h"
#include "timer.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
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
struct TutorialShader {
    const char *vertexShaderName;
    const char *fragmentShaderName;
    const char **variables;
    int variablesLen;
};

struct TutorialEntity {
    TutorialShader *shader;
    bool randomPos;
    const char *model;
    const char **textures;
    int textureLen;
    bool wrap;
    void (*enableAttribPtr)();
    bool (*renderEntityPtr)(Application *application, float rotation);
};

struct TutorialData {
    TutorialText *textStrings;
    int textLen;
    TutorialEnum tutorial;

    TutorialEntity *entities;
    int entityLen;

    int cameraX, cameraY, cameraZ;
    bool (*renderApplicationPtr)(Application *application, float rotation);
    float rotationSpeed;

    // Bitmap
    const char *bitmapFilename;
    // Sprite
    const char *spriteFilename;
    // Mouse
    bool mouse;
    TutorialShader *textShader;
    TutorialShader *bitmapShader;
};

struct Entity {
    Shader *shader;
    Model model;
};

struct Application {
    OpenGL *openGL;
    Camera *camera;
    float baseViewMatrix[16];

    // Models
    Entity *entities;
    int entityLen;

    // Sprite and Bitmap
    Bitmap *bitmap;
    Sprite *sprite;
    Shader *bitmapShader;

    // Text
    Shader *textShader;
    m_Font *font;
    int textLen;
    Text *text;
    // FPS
    Shader *fontShader;
    Text *fpsText;
    FPS *fps;
    int previousFPS;
    // Mouse text
    bool mouse;
    // Frustum
    Frustum *frustum;
    Position *position;
    Timer *timer;
    Text *entityText;
    uint renderCount;
};
bool InitializeApplication(Application *application, Display *display, Window window, int screenWidth, int screenHeight,
                           TutorialData *tutorial);
void ShutdownApplication(Application *application);
bool Frame(Application *application, Input *input,
           bool (*renderApplicationPtr)(Application *application, float rotation), float rotationSpeed);

bool RenderFpsString(Application *application);
#endif
