
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

    switch (tutorial->tutorial) {
    case MODEL: {
        application->model = (Model *)malloc(sizeof(Model));

        result =
            InitializeModel(application->model, tutorial->models, tutorial->modelLen, tutorial->textures,
                            tutorial->textureLen, tutorial->wrap, tutorial->enableAttribPtr, tutorial->variablesLen);
        if (!result) {
            printf("ERROR: Failed to initialize model\n");
            return false;
        }
        break;
    }
    case SPRITE: {
        Sprite *sprite = (Sprite *)malloc(sizeof(Sprite));
        result = InitializeSprite(*sprite, screenWidth, screenHeight, 150, 150, tutorial->spriteFilename);
        application->sprite = sprite;
        if (!result) {
            printf("ERROR: Failed to initialize sprite\n");
            return false;
        }
        break;
    }
    case BITMAP: {
        Bitmap *bitmap = (Bitmap *)malloc(sizeof(Bitmap));
        result = InitializeBitmap(*bitmap, screenWidth, screenHeight, tutorial->bitmapFilename, 150, 150);
        application->bitmap = bitmap;
        if (!result) {
            printf("ERROR: Failed to initialize bitmap\n");
            return false;
        }
        break;
    }
    case FONT: {
        m_Font *font = (m_Font *)malloc(sizeof(m_Font));
        result = InitializeFont(*font, 0);
        application->font = font;
        if (!result) {
            printf("Failed to initiazle font\n");
            return false;
        }
        application->text = (Text *)malloc(sizeof(Text) * tutorial->textLen);
        application->textLen = tutorial->textLen;
        for (int i = 0; i < application->textLen; i++) {
            TutorialText text = tutorial->textStrings[i];
            result = InitializeText(application->text[i], screenWidth, screenHeight, text.fontSize, font, text.text,
                                    text.posX, text.posY, text.color[0], text.color[1], text.color[2]);
            if (!result) {
                printf("Failed to initialize text1\n");
                return false;
            }
        }

        break;
    }
    default: {
        printf("Unknown tutorial type?\n");
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
