
#include "application.h"
#include "model.h"
#include "opengl.h"
#include <cstdio>
#include <string.h>

bool RenderApplication(Application *application) {
    bool result;

    BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

    result = SetShaderParameters(application->textureShader, application->openGL->worldMatrix,
                                 application->camera->viewMatrix, application->openGL->projectionMatrix);
    if (!result) {
        return false;
    }

    // Render the model.
    RenderModel(application->model);

    EndScene(application->openGL->display, application->openGL->hwnd);

    return true;
}

bool InitializeApplication(Application *application, Display *display, Window window, int screenWidth,
                           int screenHeight) {
    application->openGL = (OpenGL *)malloc(sizeof(OpenGL));
    application->textureShader = 0;
    application->model = 0;
    application->camera = 0;

    char textureFilename[128];
    bool result;

    result = InitializeOpenGL(application->openGL, display, window, screenWidth, screenHeight, SCREEN_NEAR,
                              SCREEN_DEPTH, VSYNC_ENABLED);
    if (!result) {
        printf("ERROR: Failed to initialize openGL\n");
        return false;
    }

    application->camera = (Camera *)malloc(sizeof(Camera));
    SetPosition(application->camera, 0.0f, 0.0f, -5.0f);

    Render(application->camera);

    strcpy(textureFilename, "./stone01.tga");

    application->model = (Model *)malloc(sizeof(Model));

    result = InitializeModel(application->model, application->openGL, textureFilename, false);
    if (!result) {
        printf("ERROR: Failed to initialize model\n");
        return false;
    }

    application->textureShader = (TextureShader *)malloc(sizeof(TextureShader));

    result = InitializeTextureShader(application->textureShader, application->openGL);
    if (!result) {
        printf("ERROR: Failed to initialize texture shader\n");
        return false;
    }

    return true;
}
void ShutdownApplication(Application *application) {

    // Release the color shader object.
    auto texture = application->textureShader;
    if (texture) {
        free(texture);
        texture = 0;
    }

    // Release the model object.
    if (application->model) {
        ShutdownModel(application->model);
        free(application->model);
        application->model = 0;
    }

    // Release the camera object.
    if (application->camera) {
        free(application->camera);
        application->camera = 0;
    }

    if (application->openGL) {
        free(application->openGL);
        application->openGL = 0;
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
