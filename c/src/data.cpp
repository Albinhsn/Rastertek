#include "data.h"

static void enableAttribPtr5() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType), (unsigned char *)NULL + (3 * sizeof(float)));
}
static void enableAttribPtr6() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexType), (unsigned char *)NULL + (5 * sizeof(float)));
}
static void enableAttribPtr7() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexType), (unsigned char *)NULL + (5 * sizeof(float)));
}
static void enableAttribPtr8() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexType), (unsigned char *)NULL + (5 * sizeof(float)));
}
static bool renderApplicationPtr9(Application *application, float rotation) {

    BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
    float worldMatrix[16], rotateMatrix[16], translateMatrix[16], scaleMatrix[16], srMatrix[16];
    Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);

    float diffuseColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightDirection[3] = {1.0f, 0.0f, 0.0f};
    float ambientLight[4] = {0.15f, 0.15f, 0.15f, 1.0f};

    MatrixRotationY(rotateMatrix, rotation);
    MatrixTranslation(translateMatrix, 2.5f, 0.0f, -2.0f);
    MatrixMultiply(worldMatrix, rotateMatrix, translateMatrix);

    bool result = SetShaderParameters9(*application->shader, worldMatrix, application->camera->viewMatrix,
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

    EndScene(application->openGL->display, application->openGL->hwnd);

    return true;
}
static bool renderApplicationPtr8(Application *application, float rotation) {
    BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
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

    EndScene(application->openGL->display, application->openGL->hwnd);

    return true;
}
static bool renderApplicationPtr7(Application *application, float rotation) {
    BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
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

    EndScene(application->openGL->display, application->openGL->hwnd);

    return true;
}
static bool renderApplicationPtr6(Application *application, float rotation) {
    BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
    float worldMatrix[16];
    Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);
    MatrixRotationY(worldMatrix, rotation);
    float diffuseColor[4] = {0.0f, 1.0f, 0.0f, 1.0f};
    float lightDirection[3] = {1.0f, 0.0f, 0.0f};
    bool result = SetShaderParameters6(*application->shader, worldMatrix, application->camera->viewMatrix,
                                       application->openGL->projectionMatrix, lightDirection, diffuseColor);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(application->model);

    EndScene(application->openGL->display, application->openGL->hwnd);

    return true;
}

static bool renderApplicationPtr5(Application *application, float rotation) {
    BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
    bool result = SetShaderParameters5(*application->shader, application->openGL->worldMatrix,
                                       application->camera->viewMatrix, application->openGL->projectionMatrix);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(application->model);

    EndScene(application->openGL->display, application->openGL->hwnd);

    return true;
}

TutorialData *Tutorial5() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->modelLen = 1;
    tutorial->models = (const char **)malloc(sizeof(char *) * tutorial->modelLen);
    tutorial->models[0] = "./data/rect.txt";

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

    return tutorial;
}

TutorialData *Tutorial6() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->modelLen = 1;
    tutorial->models = (const char **)malloc(sizeof(char *) * tutorial->modelLen);
    tutorial->models[0] = "./data/rect.txt";

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

    return tutorial;
}
TutorialData *Tutorial7() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

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

    return tutorial;
}
TutorialData *Tutorial8() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

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

    return tutorial;
}
TutorialData *Tutorial9() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

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

    return tutorial;
}
void ShutdownTutorial(TutorialData *tutorial) {
    free(tutorial->models);
    free(tutorial->textures);
    free(tutorial->variables);
}
