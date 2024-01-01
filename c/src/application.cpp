

#include "application.h"
#include "bitmap.h"
#include "fps.h"
#include "model.h"
#include "opengl.h"
#include "vector.h"
#include <cstdio>
#include <string.h>
static bool InitializeEntityString(Application *application, int screenWidth, int screenHeight) {
    application->entityText = (Text *)malloc(sizeof(Text));

    bool result = InitializeText(*application->entityText, screenWidth, screenHeight, 32, application->font,
                                 "Entities: 0", 10, 50, 1.0f, 1.0f, 0.0f);
    if (!result) {
        printf("ERROR: Failed to initialize entity text\n");
        return false;
    }
    const char *fontVertexShaderName = "./shaders/font.vs";
    const char *fontFragmentShaderName = "./shaders/font.ps";
    const char *fontVariables[2] = {"inputPosition", "inputTexCoord"};

    return true;
}

static bool InitializeFpsString(Application *application, int screenWidth, int screenHeight) {
    application->fps = (FPS *)malloc(sizeof(FPS));
    InitializeFPS(*application->fps);
    application->previousFPS = -1;
    application->fpsText = (Text *)malloc(sizeof(Text));

    bool result = InitializeText(*application->fpsText, screenWidth, screenHeight, 32, application->font, "FPS: 0", 10,
                                 10, 1.0f, 1.0f, 0.0f);
    if (!result) {
        printf("ERROR: Failed to initialize fps text\n");
        return false;
    }
    return true;
}

bool InitializeApplication(Application *application, Display *display, Window window, int screenWidth, int screenHeight,
                           TutorialData *tutorial) {
    application->bitmap = 0;
    application->openGL = (OpenGL *)malloc(sizeof(OpenGL));
    InitializeOpenGL(application->openGL, display, window, screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH,
                     VSYNC_ENABLED);

    application->frustum = (Frustum *)malloc(sizeof(Frustum));
    application->timer = (Timer *)malloc(sizeof(Timer));
    InitializeTimer(*application->timer);

    application->camera = (Camera *)malloc(sizeof(Camera));
    SetPosition(application->camera, tutorial->cameraX, tutorial->cameraY, tutorial->cameraZ);

    RenderCamera(application->camera);
    Get4x4Matrix(application->baseViewMatrix, application->camera->viewMatrix);

    m_Font *font = (m_Font *)malloc(sizeof(m_Font));
    bool result = InitializeFont(*font, 0);
    application->font = font;
    application->mouse = tutorial->mouse;

    const char *fontVertexShaderName = "./shaders/font.vs";
    const char *fontFragmentShaderName = "./shaders/font.ps";
    const char *fontVariables[2] = {"inputPosition", "inputTexCoord"};

    application->fontShader = (Shader *)malloc(sizeof(Shader));
    result = InitializeShader(*application->fontShader, fontVertexShaderName, fontFragmentShaderName, fontVariables, 2);
    if (!result) {
        printf("ERROR: Failed to initialize texture shader\n");
        return false;
    }

    if (!InitializeFpsString(application, screenWidth, screenHeight)) {
        return false;
    }
    printf("INFO: Initialized FPS string\n");

    application->position = (Position *)malloc(sizeof(Position));
    InitializePosition(*application->position);
    if (!InitializeEntityString(application, screenWidth, screenHeight)) {
        return false;
    }

    switch (tutorial->tutorial) {
    case MODEL: {
        Entity *entities = (Entity *)malloc(sizeof(Entity) * tutorial->entityLen);
        TutorialEntity tutEntity;
        for (int i = 0; i < tutorial->entityLen; i++) {
            tutEntity = tutorial->entities[i];
            result = InitializeModel(entities[i].model, tutEntity.model, tutEntity.textures, tutEntity.textureLen,
                                     tutEntity.wrap, tutEntity.enableAttribPtr, tutEntity.shader->variablesLen);
            if (!result) {
                printf("ERROR: Failed to initialize model\n");
                return false;
            }
            entities[i].shader = (Shader *)malloc(sizeof(Shader));
            result = InitializeShader(*entities[i].shader, tutEntity.shader->vertexShaderName,
                                      tutEntity.shader->fragmentShaderName, tutEntity.shader->variables,
                                      tutEntity.shader->variablesLen);
            if (!result) {
                printf("ERROR: Failed to initialize texture shader\n");
                return false;
            }
            if (tutEntity.randomPos) {
                entities[i].model.model->x = (((float)rand() - (float)rand()) / RAND_MAX) * 10.0f;
                entities[i].model.model->y = (((float)rand() - (float)rand()) / RAND_MAX) * 10.0f;
                entities[i].model.model->z = (((float)rand() - (float)rand()) / RAND_MAX) * 10.0f + 5.0f;
            }
        }
        application->entities = entities;
        application->entityLen = tutorial->entityLen;
        printf("INFO: initialzied Model\n");

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
        application->bitmapShader = (Shader *)malloc(sizeof(Shader));
        result = InitializeShader(*application->bitmapShader, tutorial->bitmapShader->vertexShaderName,
                                  tutorial->bitmapShader->fragmentShaderName, tutorial->bitmapShader->variables,
                                  tutorial->bitmapShader->variablesLen);
        if (!result) {
            printf("Failed to initialize bitmap shader\n");
            return false;
        }

        break;
    }
    case BITMAP: {
        Bitmap *bitmap = (Bitmap *)malloc(sizeof(Bitmap));
        result = InitializeBitmap(*bitmap, screenWidth, screenHeight, tutorial->bitmapFilename, 150, 150);
        if (!result) {
            printf("ERROR: Failed to initialize bitmap\n");
            return false;
        }
        printf("Initialized bitmap\n");
        application->bitmap = bitmap;
        application->bitmapShader = (Shader *)malloc(sizeof(Shader));
        result = InitializeShader(*application->bitmapShader, tutorial->bitmapShader->vertexShaderName,
                                  tutorial->bitmapShader->fragmentShaderName, tutorial->bitmapShader->variables,
                                  tutorial->bitmapShader->variablesLen);
        if (!result) {
            printf("Failed to initialize bitmap shader\n");
            return false;
        }
        break;
    }
    case FONT: {
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
        application->textShader = (Shader *)malloc(sizeof(Shader));
        result = InitializeShader(*application->textShader, tutorial->textShader->vertexShaderName,
                                  tutorial->textShader->fragmentShaderName, tutorial->textShader->variables,
                                  tutorial->textShader->variablesLen);
        if (!result) {
            printf("ERROR: Failed to initialize texture shader\n");
            return false;
        }

        break;
    }
    default: {
        printf("Unknown tutorial type?\n");
        return false;
    }
    }

    return true;
}

void ShutdownApplication(Application *application) {
    printf("Shutting down application\n");
    for (int i = 0; i < application->entityLen; i++) {
        ShutdownModel(application->entities[i].model);
        free(application->entities[i].shader);
    }
    free(application->entities);
    printf("Shutdown model\n");
    if (application->bitmap != NULL) {
        printf("%ld\n", (long)application->bitmap);
        ShutdownBitmap(application->bitmap);
        free(application->bitmap);
    }
    if (application->camera) {
        free(application->camera);
    }
    if (application->openGL) {
        free(application->openGL);
    }
    printf("Shutdown application\n");
}

bool UpdateFPS(Application *application) {
    int fps;
    char tempString[16], finalString[16];
    float red, green, blue;
    bool result;

    // Update the fps each frame.
    UpdateFPSPerFrame(*application->fps);

    // Get the current fps.
    fps = application->fps->fps;

    // Check if the fps from the previous frame was the same, if so don't need to update the text string.
    if (application->previousFPS == fps) {
        return true;
    }

    // Store the fps for checking next frame.
    application->previousFPS = fps;

    // Truncate the fps to below 100,000.
    if (fps > 99999) {
        fps = 99999;
    }

    // Convert the fps integer to string format.
    sprintf(tempString, "%d", fps);

    // Setup the fps string.
    strcpy(finalString, "Fps: ");
    strcat(finalString, tempString);

    // If fps is 60 or above set the fps color to green.
    if (fps >= 60) {
        red = 0.0f;
        green = 1.0f;
        blue = 0.0f;
    }

    // If fps is below 60 set the fps color to yellow.
    if (fps < 60) {
        red = 1.0f;
        green = 1.0f;
        blue = 0.0f;
    }

    // If fps is below 30 set the fps color to red.
    if (fps < 30) {
        red = 1.0f;
        green = 0.0f;
        blue = 0.0f;
    }

    // Update the sentence vertex buffer with the new string information.
    result = UpdateText(*application->font, *application->fpsText, finalString, 10, 10, red, green, blue);
    if (!result) {
        return false;
    }

    return true;
}

static bool UpdateMouseStrings(Application *application, int mouseX, int mouseY, bool mousePressed) {
    char tempString[16], finalString[32];
    bool result;

    // Convert the mouse X integer to string format.
    sprintf(tempString, "%d", mouseX);

    // Setup the mouse X string.
    strcpy(finalString, "Mouse X: ");
    strcat(finalString, tempString);

    // Update the sentence vertex buffer with the new string information.
    Text text = application->text[0];
    result = UpdateText(*application->font, text, finalString, 10, 40, text.pixelColor[0], text.pixelColor[1],
                        text.pixelColor[2]);
    if (!result) {
        return false;
    }

    // Convert the mouse Y integer to string format.
    sprintf(tempString, "%d", mouseY);

    // Setup the mouse Y string.
    strcpy(finalString, "Mouse Y: ");
    strcat(finalString, tempString);

    // Update the sentence vertex buffer with the new string information.
    text = application->text[1];
    result = UpdateText(*application->font, text, finalString, 10, 70, text.pixelColor[0], text.pixelColor[1],
                        text.pixelColor[2]);
    if (!result) {
        return false;
    }

    // Setup the mouse button string.
    if (mousePressed) {
        strcpy(finalString, "Mouse Button: Yes");
    } else {
        strcpy(finalString, "Mouse Button: No");
    }

    // Update the sentence vertex buffer with the new string information.
    text = application->text[2];
    result = UpdateText(*application->font, text, finalString, 10, 100, text.pixelColor[0], text.pixelColor[1],
                        text.pixelColor[2]);
    if (!result) {
        return false;
    }

    return true;
}
bool UpdateRenderCountString(Application *application) {
    char tempString[16], finalString[32];
    bool result;

    // Convert the render count integer to string format.
    sprintf(tempString, "%d", application->renderCount);

    // Setup the render count string.
    strcpy(finalString, "Render Count: ");
    strcat(finalString, tempString);

    // Update the sentence vertex buffer with the new string information.
    result = UpdateText(*application->font, *application->entityText, finalString, 10, 40, 1.0f, 1.0f, 1.0f);
    printf("INFO: Updated render count string to '%s' since %d\n", finalString, application->renderCount);
    if (!result) {
        return false;
    }

    return true;
}

bool RenderEntityString(Application *application) {
    TurnZBufferOff();
    EnableAlphaBlending();
    bool result =
        SetTextShaderParameters(*application->fontShader, application->openGL->worldMatrix, application->baseViewMatrix,
                                application->openGL->orthoMatrix, application->entityText->pixelColor);
    if (!result) {
        printf("ERROR: Failed to set text shader params\n");
        return false;
    }
    SetTexture(*application->font->texture);
    RenderText(*application->entityText);

    TurnZBufferOn();
    DisableAlphaBlending();
    return true;
}

bool Frame(Application *application, Input *input,
           bool (*renderApplicationPtr)(Application *application, float rotation), float rotationSpeed) {
    static float rotation = 360.0f;
    application->renderCount = 0;
    bool result;

    if (IsEscapePressed(input) == true) {
        return false;
    }
    rotation -= rotationSpeed * 1.0f;
    if (rotation <= 0.0f) {
        rotation += 360.0f;
    }

    if (!UpdateFPS(application)) {
        return false;
    }
    printf("INFO: Updated fps\n");

    if (application->mouse) {
        printf("INFO: Updating mouse string\n");
        if (!UpdateMouseStrings(application, input->mouseX, input->mouseY, input->mousePressed)) {
            return false;
        }
        printf("INFO: Updated mouse string\n");
    }

    TimerFrame(*application->timer);
    application->position->frameTime = application->timer->frameTime;
    TurnLeft(*application->position, IsLeftArrowPressed(input));
    TurnRight(*application->position, IsRightArrowPressed(input));

    SetRotation(application->camera, 0.0f, application->position->rotationY, 0.0f);
    RenderCamera(application->camera);

    BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
    if (!RenderFpsString(application)) {
        return false;
    }
    printf("INFO: Rendered fps string\n");

    if (!renderApplicationPtr(application, rotation)) {
        return false;
    }

    printf("INFO: Rendered application\n");
    result = UpdateRenderCountString(application);
    if (!result) {
        printf("ERROR: Failed to update render count string\n");
        return false;
    }

    RenderEntityString(application);
    printf("INFO: Rendered count string\n");

    EndScene(application->openGL->display, application->openGL->hwnd);
    printf("Ended scene\n");

    return true;
}

bool RenderFpsString(Application *application) {
    TurnZBufferOff();
    EnableAlphaBlending();
    bool result =
        SetTextShaderParameters(*application->fontShader, application->openGL->worldMatrix, application->baseViewMatrix,
                                application->openGL->orthoMatrix, application->fpsText->pixelColor);
    if (!result) {
        printf("ERROR: Failed to set text shader params\n");
        return false;
    }
    SetTexture(*application->font->texture);
    RenderText(*application->fpsText);

    TurnZBufferOn();
    DisableAlphaBlending();
    return true;
}
