
#include "application.h"
#include "bitmap.h"
#include "model.h"
#include "opengl.h"
#include "vector.h"
#include <cstdio>
#include <string.h>

bool InitializeApplication(Application *application, Display *display, Window window, int screenWidth, int screenHeight,
                           TutorialData *tutorial) {
    application->openGL = (OpenGL *)malloc(sizeof(OpenGL));

    bool result;

    InitializeOpenGL(application->openGL, display, window, screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH,
                     VSYNC_ENABLED);

    application->camera = (Camera *)malloc(sizeof(Camera));
    SetPosition(application->camera, tutorial->cameraX, tutorial->cameraY, tutorial->cameraZ);

    Render(application->camera);
    // Model
    if (tutorial->modelLen) {
        application->model = (Model *)malloc(sizeof(Model));

        result =
            InitializeModel(application->model, tutorial->models, tutorial->modelLen, tutorial->textures,
                            tutorial->textureLen, tutorial->wrap, tutorial->enableAttribPtr, tutorial->variablesLen);
        if (!result) {
            printf("ERROR: Failed to initialize model\n");
            return false;
        }
        // Bitmap
    } else {
        Bitmap *bitmap = (Bitmap *)malloc(sizeof(Bitmap));
        result = InitializeBitmap(*bitmap, screenWidth, screenHeight, tutorial->bitmapFilename, 150, 150);
        application->bitmap = bitmap;
        if (!result) {
            printf("ERROR: Failed to initialize bitmap\n");
            return false;
        }
    }

    application->shader = (Shader *)malloc(sizeof(Shader));
    result = InitializeShader(*application->shader, tutorial->vertexShaderName, tutorial->fragmentShaderName,
                              tutorial->variables, tutorial->variablesLen);
    if (!result) {
        printf("ERROR: Failed to initialize texture shader\n");
        return false;
    }

    return true;
}

void ShutdownApplication(Application *application) {
    printf("Shutting down application\n");
    if (application->shader) {
        free(application->shader);
    }
    if (application->bitmap) {
        ShutdownBitmap(application->bitmap);
        free(application->bitmap);
    }
    if (application->model) {
        ShutdownModel(application->model);
        free(application->model);
        printf("Shut down model\n");
    }
    if (application->camera) {
        free(application->camera);
    }
    if (application->openGL) {
        free(application->openGL);
    }
}

bool Frame(Application *application, Input *input,
           bool (*renderApplicationPtr)(Application *application, float rotation), float rotationSpeed) {
    static float rotation = 360.0f;
    bool result;

    if (IsEscapePressed(input) == true) {
        return false;
    }
    rotation -= rotationSpeed * 1.0f;
    if (rotation <= 0.0f) {
        rotation += 360.0f;
    }

    result = renderApplicationPtr(application, rotation);
    if (!result) {
        return false;
    }

    return true;
}
