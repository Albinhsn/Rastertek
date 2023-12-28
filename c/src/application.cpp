
#include "application.h"
#include "model.h"
#include "opengl.h"
#include <cstdio>
#include <string.h>

bool RenderApplication(Application *application) {
    bool result;

    BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

    result = SetShaderParameters(*application->shader, application->openGL->worldMatrix,
                                 application->camera->viewMatrix, application->openGL->projectionMatrix);
    if (!result) {
        return false;
    }

    RenderModel(application->model);

    EndScene(application->openGL->display, application->openGL->hwnd);

    return true;
}

bool InitializeApplication(Application *application, Display *display, Window window, int screenWidth,
                           int screenHeight) {
    application->openGL = (OpenGL *)malloc(sizeof(OpenGL));
    application->shader = 0;
    application->model = 0;
    application->camera = 0;

    char textureFilename[128];
    bool result;

    InitializeOpenGL(application->openGL, display, window, screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH,
                     VSYNC_ENABLED);

    application->camera = (Camera *)malloc(sizeof(Camera));
    SetPosition(application->camera, 0.0f, 0.0f, -5.0f);

    Render(application->camera);

    strcpy(textureFilename, "./data/blizzard01.tga");

    application->model = (Model *)malloc(sizeof(Model));

    result = InitializeModel(application->model, textureFilename, false);
    if (!result) {
        printf("ERROR: Failed to initialize model\n");
        return false;
    }

    application->shader = (Shader *)malloc(sizeof(Shader));
    const char *variables[2] = {"inputPosition", "inputTexCoord"};
    result = InitializeShader(*application->shader, "./shaders/texture.vs", "./shaders/texture.ps", variables, 2);
    if (!result) {
        printf("ERROR: Failed to initialize texture shader\n");
        return false;
    }

    return true;
}
void ShutdownApplication(Application *application) {

    // Release the color shader object.
    auto texture = application->shader;
    if (texture) {
        free(texture);
        texture = 0;
    }

    // Release the model object.
    if (application->model) {
        ShutdownModel(application->model);
        free(application->model);
    }

    // Release the camera object.
    if (application->camera) {
        free(application->camera);
    }

    if (application->openGL) {
        free(application->openGL);
    }
}
bool Frame(Application *application, Input *input) {
    bool result;

    if (IsEscapePressed(input) == true) {
        return false;
    }

    result = RenderApplication(application);
    if (!result) {
        return false;
    }

    return true;
}
