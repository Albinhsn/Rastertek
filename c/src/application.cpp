
#include "application.h"
#include "model.h"
#include "opengl.h"
#include "vector.h"
#include <cstdio>
#include <string.h>

bool RenderApplication(Application *application, float rotation) {
    bool result;

    BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

    switch (application->app) {
    case 5: {
        result = SetShaderParameters5(*application->shader, application->openGL->worldMatrix,
                                      application->camera->viewMatrix, application->openGL->projectionMatrix);
        break;
    }
    case 6: {
        float worldMatrix[16];
        Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);
        MatrixRotationY(worldMatrix, rotation);
        float diffuseColor[4] = {0.0f, 1.0f, 0.0f, 1.0f};
        float lightDirection[3] = {1.0f, 0.0f, 0.0f};
        result = SetShaderParameters6(*application->shader, worldMatrix, application->camera->viewMatrix,
                                      application->openGL->projectionMatrix, lightDirection, diffuseColor);
        break;
    }
    default: {
        float worldMatrix[16];
        Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);
        MatrixRotationY(worldMatrix, rotation);
        float diffuseColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        float lightDirection[3] = {0.0f, 0.0f, 1.0f};
        result = SetShaderParameters6(*application->shader, worldMatrix, application->camera->viewMatrix,
                                      application->openGL->projectionMatrix, lightDirection, diffuseColor);
        break;
    }
    }
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }

    RenderModel(application->model);

    EndScene(application->openGL->display, application->openGL->hwnd);

    return true;
}

bool InitializeApplication5(Application *application, Display *display, Window window, int screenWidth, int screenHeight) {

    application->openGL = (OpenGL *)malloc(sizeof(OpenGL));
    application->shader = 0;
    application->model = 0;
    application->camera = 0;

    char textureFilename[128];
    char modelFilename[128];
    bool result;

    InitializeOpenGL(application->openGL, display, window, screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH,
                     VSYNC_ENABLED);

    application->camera = (Camera *)malloc(sizeof(Camera));
    SetPosition(application->camera, 0.0f, 0.0f, -5.0f);

    Render(application->camera);

    strcpy(modelFilename, "./data/rect.txt");
    strcpy(textureFilename, "./data/blizzard01.tga");

    application->model = (Model *)malloc(sizeof(Model));

    result = InitializeModel(application->model, modelFilename, textureFilename, false);
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
bool InitializeApplication7(Application *application, Display *display, Window window, int screenWidth,
                           int screenHeight) {
    application->openGL = (OpenGL *)malloc(sizeof(OpenGL));
    application->shader = 0;
    application->model = 0;
    application->camera = 0;

    char modelFilename[128];
    char textureFilename[128];
    bool result;

    InitializeOpenGL(application->openGL, display, window, screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH,
                     VSYNC_ENABLED);

    application->camera = (Camera *)malloc(sizeof(Camera));
    SetPosition(application->camera, 0.0f, 0.0f, -5.0f);

    Render(application->camera);

    strcpy(modelFilename, "./data/cube.txt");
    strcpy(textureFilename, "./data/blizzard01.tga");

    application->model = (Model *)malloc(sizeof(Model));

    result = InitializeModel(application->model, modelFilename, textureFilename, false);
    if (!result) {
        printf("ERROR: Failed to initialize model\n");
        return false;
    }

    application->shader = (Shader *)malloc(sizeof(Shader));
    const int len = 3;
    const char *variables[len] = {"inputPosition", "inputTexCoord", "inputNormal"};
    result = InitializeShader(*application->shader, "./shaders/light3.vs", "./shaders/light3.ps", variables, len);
    if (!result) {
        printf("ERROR: Failed to initialize texture shader\n");
        return false;
    }

    return true;
}
bool InitializeApplication(Application *application, Display *display, Window window, int screenWidth,
                           int screenHeight) {
    application->openGL = (OpenGL *)malloc(sizeof(OpenGL));
    application->shader = 0;
    application->model = 0;
    application->camera = 0;

    char modelFilename[128];
    char textureFilename[128];
    bool result;

    InitializeOpenGL(application->openGL, display, window, screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH,
                     VSYNC_ENABLED);

    application->camera = (Camera *)malloc(sizeof(Camera));
    SetPosition(application->camera, 0.0f, 0.0f, -5.0f);

    Render(application->camera);

    strcpy(modelFilename, "./data/cube.txt");
    strcpy(textureFilename, "./data/blizzard01.tga");

    application->model = (Model *)malloc(sizeof(Model));

    result = InitializeModel(application->model, modelFilename, textureFilename, false);
    if (!result) {
        printf("ERROR: Failed to initialize model\n");
        return false;
    }

    application->shader = (Shader *)malloc(sizeof(Shader));
    const int len = 3;
    const char *variables[len] = {"inputPosition", "inputTexCoord", "inputNormal"};
    result = InitializeShader(*application->shader, "./shaders/light3.vs", "./shaders/light3.ps", variables, len);
    if (!result) {
        printf("ERROR: Failed to initialize texture shader\n");
        return false;
    }

    return true;
}

bool InitializeApplication6(Application *application, Display *display, Window window, int screenWidth,
                            int screenHeight) {
    application->openGL = (OpenGL *)malloc(sizeof(OpenGL));
    application->shader = 0;
    application->model = 0;
    application->camera = 0;

    char modelFilename[128];
    char textureFilename[128];
    bool result;

    InitializeOpenGL(application->openGL, display, window, screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH,
                     VSYNC_ENABLED);

    application->camera = (Camera *)malloc(sizeof(Camera));
    SetPosition(application->camera, 0.0f, 0.0f, -5.0f);

    Render(application->camera);

    strcpy(modelFilename, "./data/rect.txt");
    strcpy(textureFilename, "./data/blizzard01.tga");

    application->model = (Model *)malloc(sizeof(Model));

    result = InitializeModel(application->model, modelFilename, textureFilename, false);
    if (!result) {
        printf("ERROR: Failed to initialize model\n");
        return false;
    }

    application->shader = (Shader *)malloc(sizeof(Shader));
    const int len = 3;
    const char *variables[len] = {"inputPosition", "inputTexCoord", "inputNormal"};
    result = InitializeShader(*application->shader, "./shaders/light3.vs", "./shaders/light3.ps", variables, len);
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
    static float rotation = 360.0f;
    bool result;

    if (IsEscapePressed(input) == true) {
        return false;
    }
    rotation -= 0.0174532925f * 1.0f;
    if (rotation <= 0.0f) {
        rotation += 360.0f;
    }

    result = RenderApplication(application, rotation);
    if (!result) {
        return false;
    }

    return true;
}
