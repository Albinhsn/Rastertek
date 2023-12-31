#include "data.h"
#include "opengl.h"
#include "sprite.h"
#include "texture.h"

static void enableAttribPtr5() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexTypeN), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexTypeN), (unsigned char *)NULL + (3 * sizeof(float)));
}
static void enableAttribPtr6() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexTypeN), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexTypeN), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexTypeN), (unsigned char *)NULL + (5 * sizeof(float)));
}
static void enableAttribPtr7() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexTypeN), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexTypeN), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexTypeN), (unsigned char *)NULL + (5 * sizeof(float)));
}
static void enableAttribPtr8() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexTypeN), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexTypeN), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexTypeN), (unsigned char *)NULL + (5 * sizeof(float)));
}
static void enableAttribPtr10() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexTypeN), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexTypeN), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexTypeN), (unsigned char *)NULL + (5 * sizeof(float)));
}
static void enableAttribPtr11() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexTypeN), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexTypeN), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexTypeN), (unsigned char *)NULL + (5 * sizeof(float)));
}
static bool renderApplicationPtr16(Application *application, float rotation) {
    bool result;

    TurnZBufferOff();
    EnableAlphaBlending();
    for (int i = 0; i < application->textLen; i++) {
        result = SetShaderParameters14(*application->shader, application->openGL->worldMatrix,
                                       application->camera->viewMatrix, application->openGL->orthoMatrix,
                                       application->text[i].pixelColor);
        if (!result) {
            printf("Failed to set shader params\n");
            return false;
        }
        SetTexture(application->font->texture);
        RenderText(application->text[i]);
    }

    TurnZBufferOn();
    DisableAlphaBlending();

    return true;
}
static bool renderApplicationPtr15(Application *application, float rotation) { return true; }
static bool renderApplicationPtr14(Application *application, float rotation) {
    TurnZBufferOff();
    EnableAlphaBlending();
    for (int i = 0; i < application->textLen; i++) {
        bool result = SetShaderParameters14(*application->shader, application->openGL->worldMatrix,
                                            application->camera->viewMatrix, application->openGL->orthoMatrix,
                                            application->text[i].pixelColor);
        if (!result) {
            printf("Failed to set shader params\n");
            return false;
        }
        SetTexture(application->font->texture);
        RenderText(application->text[i]);
    }

    TurnZBufferOn();
    DisableAlphaBlending();

    return true;
}
static bool renderApplicationPtr13(Application *application, float rotation) {
    TurnZBufferOff();

    bool result = SetShaderParameters12(*application->shader, application->openGL->worldMatrix,
                                        application->camera->viewMatrix, application->openGL->orthoMatrix);
    if (!result) {
        printf("Failed to set shader params\n");
        return false;
    }
    RenderSprite(*application->sprite);

    TurnZBufferOn();

    return true;
}
static bool renderApplicationPtr12(Application *application, float rotation) {
    TurnZBufferOff();

    bool result = SetShaderParameters12(*application->shader, application->openGL->worldMatrix,
                                        application->camera->viewMatrix, application->openGL->orthoMatrix);
    if (!result) {
        return false;
    }
    RenderBitmap(*application->bitmap);

    TurnZBufferOn();

    return true;
}
static bool renderApplicationPtr11(Application *application, float rotation) {
    // float diffuseColorArray[20] = {1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //                                1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.753f, 0.796f};
    float diffuseColorArray[4] = {1.0f, 0.753f, 0.796f, 1.0f};
    // float lightPositionArray[15] = {-3.0f, 1.0f, 3.0f, 3.0f,  1.0f, 3.0f, -3.0f, 1.0f,
    //                                 -3.0f, 3.0f, 1.0f, -3.0f, 1.5f, 1.0f, 1.5f};
    float lightPositionArray[3] = {0.0f, 1.0f, 0.0f};
    int numLights = 1;
    bool result =
        SetShaderParameters11(*application->shader, application->openGL->worldMatrix, application->camera->viewMatrix,
                              application->openGL->projectionMatrix, diffuseColorArray, lightPositionArray, numLights);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(application->model);

    return true;
}

static bool renderApplicationPtr10(Application *application, float rotation) {
    float worldMatrix[16], rotateMatrix[16], translateMatrix[16], scaleMatrix[16], srMatrix[16];
    Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);

    float diffuseLightColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightDirection[3] = {0.0f, 1.0f, 0.0f};
    float ambientLight[4] = {0.15f, 0.15f, 0.15f, 1.0f};
    float specularColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float cameraPosition[3] = {application->camera->position.x, application->camera->position.y,
                               application->camera->position.z};
    float specularPower = 32.0f;

    MatrixRotationY(rotateMatrix, rotation);
    MatrixTranslation(translateMatrix, 2.5f, 0.0f, -2.0f);
    MatrixMultiply(worldMatrix, rotateMatrix, translateMatrix);

    bool result = SetShaderParameters10(*application->shader, worldMatrix, application->camera->viewMatrix,
                                        application->openGL->projectionMatrix, lightDirection, diffuseLightColor,
                                        ambientLight, cameraPosition, specularColor, specularPower);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(application->model);

    MatrixScale(scaleMatrix, 0.5f, 0.5f, 0.5f);
    MatrixRotationY(rotateMatrix, rotation);
    MatrixTranslation(translateMatrix, -2.5f, 0.0f, -2.0f);

    MatrixMultiply(srMatrix, scaleMatrix, rotateMatrix);
    MatrixMultiply(worldMatrix, srMatrix, translateMatrix);
    result = SetShaderParameters10(*application->shader, worldMatrix, application->camera->viewMatrix,
                                   application->openGL->projectionMatrix, lightDirection, diffuseLightColor,
                                   ambientLight, cameraPosition, specularColor, specularPower);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(application->model);

    return true;
}
static bool renderApplicationPtr9(Application *application, float rotation) {
    float worldMatrix[16], rotateMatrix[16], translateMatrix[16], scaleMatrix[16], srMatrix[16];
    Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);

    float diffuseColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightDirection[3] = {1.0f, 0.0f, 0.0f};
    float ambientLight[4] = {0.15f, 0.15f, 0.15f, 1.0f};

    MatrixRotationY(rotateMatrix, rotation);
    MatrixTranslation(translateMatrix, 2.5f, 0.0f, -2.0f);
    MatrixMultiply(worldMatrix, rotateMatrix, translateMatrix);

    bool result =
        SetShaderParameters9(*application->shader, worldMatrix, application->camera->viewMatrix,
                             application->openGL->projectionMatrix, lightDirection, diffuseColor, ambientLight);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(application->model);

    MatrixScale(scaleMatrix, 0.5f, 0.5f, 0.5f);
    MatrixRotationY(rotateMatrix, rotation);
    MatrixTranslation(translateMatrix, -2.5f, 0.0f, -2.0f);

    MatrixMultiply(srMatrix, scaleMatrix, rotateMatrix);
    MatrixMultiply(worldMatrix, srMatrix, translateMatrix);
    result = SetShaderParameters9(*application->shader, worldMatrix, application->camera->viewMatrix,
                                  application->openGL->projectionMatrix, lightDirection, diffuseColor, ambientLight);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(application->model);
    return true;
}
static bool renderApplicationPtr8(Application *application, float rotation) {

    float worldMatrix[16], rotateMatrix[16], translateMatrix[16], scaleMatrix[16], srMatrix[16];
    Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);

    float diffuseColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightDirection[3] = {0.0f, 0.0f, 1.0f};

    MatrixRotationY(rotateMatrix, rotation);
    float a = cosf(rotation) * 2;
    float b = sinf(rotation) * 2;
    MatrixTranslation(translateMatrix, a, 0.0f, b);
    MatrixMultiply(worldMatrix, application->openGL->worldMatrix, translateMatrix);

    bool result = SetShaderParameters6(*application->shader, worldMatrix, application->camera->viewMatrix,
                                       application->openGL->projectionMatrix, lightDirection, diffuseColor);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(application->model);

    MatrixScale(scaleMatrix, 0.5f, 0.5f, 0.5f);
    // MatrixRotationY(rotateMatrix, rotation);
    MatrixTranslation(translateMatrix, -a, 0.0f, -b);

    // MatrixMultiply(srMatrix, scaleMatrix, rotateMatrix);
    MatrixMultiply(worldMatrix, scaleMatrix, translateMatrix);
    result = SetShaderParameters6(*application->shader, worldMatrix, application->camera->viewMatrix,
                                  application->openGL->projectionMatrix, lightDirection, diffuseColor);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(application->model);

    return true;
}
static bool renderApplicationPtr7(Application *application, float rotation) {
    float worldMatrix[16];
    Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);
    MatrixRotationY(worldMatrix, rotation);
    float diffuseColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightDirection[3] = {1.0f, 0.0f, 0.0f};
    bool result = SetShaderParameters6(*application->shader, worldMatrix, application->camera->viewMatrix,
                                       application->openGL->projectionMatrix, lightDirection, diffuseColor);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(application->model);

    return true;
}
static bool renderApplicationPtr6(Application *application, float rotation) {
    float worldMatrix[16];
    Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);
    MatrixRotationY(worldMatrix, rotation);
    float diffuseColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightDirection[3] = {1.0f, 0.0f, 0.0f};
    bool result = SetShaderParameters6(*application->shader, worldMatrix, application->camera->viewMatrix,
                                       application->openGL->projectionMatrix, lightDirection, diffuseColor);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(application->model);

    return true;
}

static bool renderApplicationPtr5(Application *application, float rotation) {
    bool result = SetShaderParameters5(*application->shader, application->openGL->worldMatrix,
                                       application->camera->viewMatrix, application->openGL->projectionMatrix);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(application->model);

    return true;
}

TutorialData *Tutorial5() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;

    tutorial->modelLen = 1;
    tutorial->models = (const char **)malloc(sizeof(char *) * tutorial->modelLen);
    tutorial->models[0] = "./data/triangle.txt";

    tutorial->textureLen = 1;
    tutorial->textures = (const char **)malloc(sizeof(char *) * tutorial->textureLen);
    tutorial->textures[0] = "./data/blizzard01.tga";

    tutorial->vertexShaderName = "./shaders/texture.vs";
    tutorial->fragmentShaderName = "./shaders/texture.ps";

    tutorial->variablesLen = 2;
    tutorial->variables = (const char **)malloc(sizeof(char *) * tutorial->variablesLen);
    tutorial->variables[0] = "inputPosition";
    tutorial->variables[1] = "inputTexCoord";

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -5.0f;

    tutorial->enableAttribPtr = &enableAttribPtr5;
    tutorial->renderApplicationPtr = &renderApplicationPtr5;

    tutorial->wrap = false;
    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}

TutorialData *Tutorial6() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;
    tutorial->modelLen = 1;
    tutorial->models = (const char **)malloc(sizeof(char *) * tutorial->modelLen);
    tutorial->models[0] = "./data/cube.txt";

    tutorial->textureLen = 1;
    tutorial->textures = (const char **)malloc(sizeof(char *) * tutorial->textureLen);
    tutorial->textures[0] = "./data/blizzard01.tga";

    tutorial->vertexShaderName = "./shaders/light3.vs";
    tutorial->fragmentShaderName = "./shaders/light3.ps";

    tutorial->variablesLen = 3;
    tutorial->variables = (const char **)malloc(sizeof(char *) * tutorial->variablesLen);
    tutorial->variables[0] = "inputPosition";
    tutorial->variables[1] = "inputTexCoord";
    tutorial->variables[2] = "inputNormal";

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -5.0f;

    tutorial->enableAttribPtr = &enableAttribPtr6;
    tutorial->renderApplicationPtr = &renderApplicationPtr6;

    tutorial->wrap = false;
    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial7() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;
    tutorial->modelLen = 1;
    tutorial->models = (const char **)malloc(sizeof(char *) * tutorial->modelLen);
    tutorial->models[0] = "./data/cube.txt";

    tutorial->textureLen = 1;
    tutorial->textures = (const char **)malloc(sizeof(char *) * tutorial->textureLen);
    tutorial->textures[0] = "./data/blizzard01.tga";

    tutorial->vertexShaderName = "./shaders/light3.vs";
    tutorial->fragmentShaderName = "./shaders/light3.ps";

    tutorial->variablesLen = 3;
    tutorial->variables = (const char **)malloc(sizeof(char *) * tutorial->variablesLen);
    tutorial->variables[0] = "inputPosition";
    tutorial->variables[1] = "inputTexCoord";
    tutorial->variables[2] = "inputNormal";

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -5.0f;

    tutorial->enableAttribPtr = &enableAttribPtr7;
    tutorial->renderApplicationPtr = &renderApplicationPtr7;

    tutorial->wrap = false;
    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial8() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;
    tutorial->modelLen = 1;
    tutorial->models = (const char **)malloc(sizeof(char *) * tutorial->modelLen);
    tutorial->models[0] = "./data/cube.txt";

    tutorial->textureLen = 1;
    tutorial->textures = (const char **)malloc(sizeof(char *) * tutorial->textureLen);
    tutorial->textures[0] = "./data/ball01.tga";

    tutorial->vertexShaderName = "./shaders/light3.vs";
    tutorial->fragmentShaderName = "./shaders/light3.ps";

    tutorial->variablesLen = 3;
    tutorial->variables = (const char **)malloc(sizeof(char *) * tutorial->variablesLen);
    tutorial->variables[0] = "inputPosition";
    tutorial->variables[1] = "inputTexCoord";
    tutorial->variables[2] = "inputNormal";

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->enableAttribPtr = &enableAttribPtr8;
    tutorial->renderApplicationPtr = &renderApplicationPtr8;

    tutorial->wrap = false;
    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial10() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;
    tutorial->modelLen = 1;
    tutorial->models = (const char **)malloc(sizeof(char *) * tutorial->modelLen);
    tutorial->models[0] = "./data/sphere.txt";

    tutorial->textureLen = 1;
    tutorial->textures = (const char **)malloc(sizeof(char *) * tutorial->textureLen);
    tutorial->textures[0] = "./data/stone01.tga";

    tutorial->vertexShaderName = "./shaders/light2.vs";
    tutorial->fragmentShaderName = "./shaders/light2.ps";

    tutorial->variablesLen = 3;
    tutorial->variables = (const char **)malloc(sizeof(char *) * tutorial->variablesLen);
    tutorial->variables[0] = "inputPosition";
    tutorial->variables[1] = "inputTexCoord";
    tutorial->variables[2] = "inputNormal";

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->enableAttribPtr = &enableAttribPtr10;
    tutorial->renderApplicationPtr = &renderApplicationPtr10;

    tutorial->wrap = true;
    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial11() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;
    tutorial->modelLen = 1;
    tutorial->models = (const char **)malloc(sizeof(char *) * tutorial->modelLen);
    tutorial->models[0] = "./data/plane.txt";

    tutorial->textureLen = 1;
    tutorial->textures = (const char **)malloc(sizeof(char *) * tutorial->textureLen);
    tutorial->textures[0] = "./data/stone01.tga";

    tutorial->vertexShaderName = "./shaders/light4.vs";
    tutorial->fragmentShaderName = "./shaders/light4.ps";

    tutorial->variablesLen = 3;
    tutorial->variables = (const char **)malloc(sizeof(char *) * tutorial->variablesLen);
    tutorial->variables[0] = "inputPosition";
    tutorial->variables[1] = "inputTexCoord";
    tutorial->variables[2] = "inputNormal";

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 2.0f;
    tutorial->cameraZ = -12.0f;

    tutorial->enableAttribPtr = &enableAttribPtr11;
    tutorial->renderApplicationPtr = &renderApplicationPtr11;

    tutorial->wrap = false;
    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial9() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;

    tutorial->modelLen = 1;
    tutorial->models = (const char **)malloc(sizeof(char *) * tutorial->modelLen);
    tutorial->models[0] = "./data/cube.txt";

    tutorial->textureLen = 1;
    tutorial->textures = (const char **)malloc(sizeof(char *) * tutorial->textureLen);
    tutorial->textures[0] = "./data/stone01.tga";

    tutorial->vertexShaderName = "./shaders/light.vs";
    tutorial->fragmentShaderName = "./shaders/light.ps";

    tutorial->variablesLen = 3;
    tutorial->variables = (const char **)malloc(sizeof(char *) * tutorial->variablesLen);
    tutorial->variables[0] = "inputPosition";
    tutorial->variables[1] = "inputTexCoord";
    tutorial->variables[2] = "inputNormal";

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->enableAttribPtr = &enableAttribPtr8;
    tutorial->renderApplicationPtr = &renderApplicationPtr9;

    tutorial->wrap = false;
    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial12() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = BITMAP;

    tutorial->bitmapFilename = "./data/blizzard01.tga";
    tutorial->vertexShaderName = "./shaders/texture.vs";
    tutorial->fragmentShaderName = "./shaders/texture.ps";

    tutorial->variablesLen = 3;
    tutorial->variables = (const char **)malloc(sizeof(char *) * tutorial->variablesLen);
    tutorial->variables[0] = "inputPosition";
    tutorial->variables[1] = "inputTexCoord";
    tutorial->variables[2] = "inputNormal";

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->enableAttribPtr = &enableAttribPtr5;
    tutorial->renderApplicationPtr = &renderApplicationPtr12;

    tutorial->wrap = false;
    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}

TutorialData *Tutorial13() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = SPRITE;

    tutorial->spriteFilename = "./data/sprite_data_01.txt";

    tutorial->vertexShaderName = "./shaders/texture.vs";
    tutorial->fragmentShaderName = "./shaders/texture.ps";

    tutorial->variablesLen = 3;
    tutorial->variables = (const char **)malloc(sizeof(char *) * tutorial->variablesLen);
    tutorial->variables[0] = "inputPosition";
    tutorial->variables[1] = "inputTexCoord";
    tutorial->variables[2] = "inputNormal";

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->enableAttribPtr = &enableAttribPtr5;
    tutorial->renderApplicationPtr = &renderApplicationPtr13;

    tutorial->wrap = false;
    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial14() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = FONT;

    tutorial->textLen = 3;
    tutorial->textStrings = (TutorialText *)malloc(sizeof(TutorialText) * tutorial->textLen);
    tutorial->textStrings[0] = (TutorialText){"Hello", {0.0f, 1.0f, 0.0f, 1.0f}, 32, 100, 10};
    tutorial->textStrings[1] = (TutorialText){"Goodbye", {1.0f, 1.0f, 0.0f, 1.0f}, 32, 100, 50};
    tutorial->textStrings[2] = (TutorialText){"Cya", {1.0f, 1.0f, 0.0f, 1.0f}, 32, 100, 100};

    tutorial->vertexShaderName = "./shaders/font.vs";
    tutorial->fragmentShaderName = "./shaders/font.ps";

    tutorial->variablesLen = 2;
    tutorial->variables = (const char **)malloc(sizeof(char *) * tutorial->variablesLen);
    tutorial->variables[0] = "inputPosition";
    tutorial->variables[1] = "inputTexCoord";

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 0.0f;
    tutorial->cameraZ = -5.0f;

    tutorial->enableAttribPtr = &enableAttribPtr5;
    tutorial->renderApplicationPtr = &renderApplicationPtr14;

    tutorial->wrap = false;
    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial15() {

    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = FONT;

    tutorial->vertexShaderName = "./shaders/font.vs";
    tutorial->fragmentShaderName = "./shaders/font.ps";

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 0.0f;
    tutorial->cameraZ = -5.0f;

    tutorial->enableAttribPtr = &enableAttribPtr5;
    tutorial->renderApplicationPtr = &renderApplicationPtr15;

    tutorial->wrap = false;
    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial16() {

    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = FONT;

    tutorial->textLen = 3;
    tutorial->textStrings = (TutorialText *)malloc(sizeof(TutorialText) * tutorial->textLen);
    tutorial->textStrings[0] = (TutorialText){"Mouse X: 0", {0.0f, 1.0f, 0.0f, 1.0f}, 32, 10, 40};
    tutorial->textStrings[1] = (TutorialText){"Mouse Y: 0", {1.0f, 1.0f, 0.0f, 1.0f}, 32, 10, 70};
    tutorial->textStrings[2] = (TutorialText){"Mouse Button: No", {1.0f, 1.0f, 0.0f, 1.0f}, 32, 10, 100};

    tutorial->vertexShaderName = "./shaders/font.vs";
    tutorial->fragmentShaderName = "./shaders/font.ps";

    tutorial->variablesLen = 2;
    tutorial->variables = (const char **)malloc(sizeof(char *) * tutorial->variablesLen);
    tutorial->variables[0] = "inputPosition";
    tutorial->variables[1] = "inputTexCoord";

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->enableAttribPtr = &enableAttribPtr5;
    tutorial->renderApplicationPtr = &renderApplicationPtr16;

    tutorial->wrap = false;
    tutorial->rotationSpeed = 0.0174532925f;

    tutorial->mouse = true;

    return tutorial;
}
void ShutdownTutorial(TutorialData *tutorial) {
    free(tutorial->models);
    free(tutorial->textures);
    free(tutorial->variables);
}
