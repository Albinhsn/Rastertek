

#include "application.h"
#include "bitmap.h"
#include "fps.h"
#include "model.h"
#include "opengl.h"
#include <cstdio>
#include <string.h>

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
    const char *fontVertexShaderName = "./shaders/font.vs";
    const char *fontFragmentShaderName = "./shaders/font.ps";
    const char *fontVariables[2] = {"inputPosition", "inputTexCoord"};

    application->fpsShader = (Shader *)malloc(sizeof(Shader));
    result = InitializeShader(*application->fpsShader, fontVertexShaderName, fontFragmentShaderName, fontVariables, 2);
    if (!result) {
        printf("ERROR: Failed to initialize texture shader\n");
        return false;
    }
    return true;
}

bool InitializeApplication(Application *application, Display *display, Window window, int screenWidth, int screenHeight,
                           TutorialData *tutorial) {
    application->openGL = (OpenGL *)malloc(sizeof(OpenGL));

    InitializeOpenGL(application->openGL, display, window, screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH,

                     VSYNC_ENABLED);

    application->camera = (Camera *)malloc(sizeof(Camera));
    SetPosition(application->camera, tutorial->cameraX, tutorial->cameraY, tutorial->cameraZ);

    Render(application->camera);

    m_Font *font = (m_Font *)malloc(sizeof(m_Font));
    bool result = InitializeFont(*font, 0);
    application->font = font;
    application->mouse = tutorial->mouse;

    if (!InitializeFpsString(application, screenWidth, screenHeight)) {
        return false;
    }

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

    if (!UpdateFPS(application)) {
        return false;
    }

    if (application->mouse) {
        if (!UpdateMouseStrings(application, input->mouseX, input->mouseY, input->mousePressed)) {
            return false;
        }
    }

    BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
    if (!RenderFpsString(application)) {
        return false;
    }

    if (!renderApplicationPtr(application, rotation)) {
        return false;
    }

    EndScene(application->openGL->display, application->openGL->hwnd);

    return true;
}

bool RenderFpsString(Application *application) {
    TurnZBufferOff();
    EnableAlphaBlending();
    bool result = SetTextShaderParameters(*application->fpsShader, application->openGL->worldMatrix,
                                          application->camera->viewMatrix, application->openGL->orthoMatrix,
                                          application->fpsText->pixelColor);
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
