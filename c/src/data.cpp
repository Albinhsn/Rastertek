#include "data.h"
#include "frustum.h"
#include "opengl.h"
#include "sprite.h"
#include "texture.h"
#include "vector.h"

static void enableAttribPtr5() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (3 * sizeof(float)));
}
static void enableAttribPtr6() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (5 * sizeof(float)));
}
static void enableAttribPtr7() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (5 * sizeof(float)));
}
static void enableAttribPtr8() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (5 * sizeof(float)));
}
static void enableAttribPtr10() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (5 * sizeof(float)));
}
static void enableAttribPtr11() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (5 * sizeof(float)));
}
static void enableAttribPtr20() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (5 * sizeof(float)));
    glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (8 * sizeof(float)));
    glVertexAttribPointer(4, 3, GL_FLOAT, false, sizeof(VertexTypeNTB), (unsigned char *)NULL + (11 * sizeof(float)));
}
static bool renderApplicationPtr23(Application *application, float rotation) {

    float rotateMatrix[16], translateMatrix[16], worldMatrix[16];
    MatrixRotationY(rotateMatrix, rotation);

    ConstructFrustum(*application->frustum, SCREEN_DEPTH, application->camera->viewMatrix,
                     application->openGL->projectionMatrix);

    for (int i = 0; i < application->entityLen; i++) {
        Entity entity = application->entities[i];
        bool renderModel =
            CheckCube(*application->frustum, entity.model.model->x, entity.model.model->y, entity.model.model->z, 1.0f);
        if (renderModel) {
            MatrixTranslation(translateMatrix, entity.model.model->x, entity.model.model->y, entity.model.model->z);
            MatrixMultiply(worldMatrix, rotateMatrix, translateMatrix);
            bool result = SetShaderParameters5(*application->entities[i].shader, worldMatrix,
                                               application->camera->viewMatrix, application->openGL->projectionMatrix);
            if (!result) {
                return false;
            }
            RenderModel(application->entities[i].model);
            application->renderCount++;
        }
    }

    return true;
}
static bool renderApplicationPtr22(Application *application, float rotation) {

    float rotateMatrix[16], translateMatrix[16], worldMatrix[16];
    MatrixRotationY(rotateMatrix, rotation);
    float diffuseLightColor[4] = {1.0f, 0.753f, 0.796f, 1.0f};
    float lightDirection[3] = {0.0f, 0.0f, 1.0f};

    MatrixTranslation(translateMatrix, 0.0f, 1.0f, 0.0f);
    MatrixMultiply(worldMatrix, rotateMatrix, translateMatrix);
    bool result = SetShaderParameters5(*application->entities[0].shader, worldMatrix, application->camera->viewMatrix,
                                       application->openGL->projectionMatrix);
    if (!result) {
        return false;
    }
    RenderModel(application->entities[0].model);
    printf("Rendered model 1\n");

    MatrixTranslation(translateMatrix, -1.5f, -1.0f, 0.0f);
    MatrixMultiply(worldMatrix, rotateMatrix, translateMatrix);

    result = SetShaderParameters6(*application->entities[1].shader, worldMatrix, application->camera->viewMatrix,
                                  application->openGL->projectionMatrix, lightDirection, diffuseLightColor);
    if (!result) {
        return false;
    }
    RenderModel(application->entities[1].model);
    printf("Rendered model 2\n");

    MatrixTranslation(translateMatrix, 1.5f, -1.0f, 0.0f);
    MatrixMultiply(worldMatrix, rotateMatrix, translateMatrix);
    result = SetShaderParameters20(*application->entities[2].shader, worldMatrix, application->camera->viewMatrix,
                                   application->openGL->projectionMatrix, lightDirection, diffuseLightColor);
    if (!result) {
        return false;
    }
    RenderModel(application->entities[2].model);

    return true;
}
static bool renderApplicationPtr21(Application *application, float rotation) {

    Shader shader = *application->entities[0].shader;
    Model model = application->entities[0].model;

    float worldMatrix[16];
    Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);
    MatrixRotationY(worldMatrix, rotation);

    float diffuseLightColor[4] = {1.0f, 0.753f, 0.796f, 1.0f};
    float lightDirection[3] = {0.0f, 0.0f, 1.0f};
    Vector3 cameraPos = application->camera->position;
    float cameraPosition[3] = {cameraPos.x, cameraPos.x, cameraPos.z};
    float specularColor[4] = {1.0f, 0.753f, 0.796f, 1.0f};

    bool result = SetShaderParameters21(shader, worldMatrix, application->camera->viewMatrix,
                                        application->openGL->projectionMatrix, lightDirection, diffuseLightColor,
                                        cameraPosition, specularColor, 32.0f);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    return true;
}
static bool renderApplicationPtr20(Application *application, float rotation) {
    Shader shader = *application->entities[0].shader;
    Model model = application->entities[0].model;

    float worldMatrix[16];
    Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);
    MatrixRotationY(worldMatrix, rotation);

    float diffuseLightColor[4] = {1.0f, 0.753f, 0.796f, 1.0f};
    float lightDirection[3] = {0.0f, 0.0f, 1.0f};

    bool result = SetShaderParameters20(shader, worldMatrix, application->camera->viewMatrix,
                                        application->openGL->projectionMatrix, lightDirection, diffuseLightColor);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    return true;
}
static bool renderApplicationPtr19(Application *application, float rotation) {
    Shader shader = *application->entities[0].shader;
    Model model = application->entities[0].model;

    bool result = SetShaderParameters19(shader, application->openGL->worldMatrix, application->camera->viewMatrix,
                                        application->openGL->projectionMatrix);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    return true;
}
static bool renderApplicationPtr18(Application *application, float rotation) {

    Shader shader = *application->entities[0].shader;
    Model model = application->entities[0].model;

    bool result = SetShaderParameters17(shader, application->openGL->worldMatrix, application->camera->viewMatrix,
                                        application->openGL->projectionMatrix);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    return true;
}
static bool renderApplicationPtr17(Application *application, float rotation) {

    Shader shader = *application->entities[0].shader;
    Model model = application->entities[0].model;

    bool result = SetShaderParameters17(shader, application->openGL->worldMatrix, application->camera->viewMatrix,
                                        application->openGL->projectionMatrix);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    return true;
}
static bool renderApplicationPtr16(Application *application, float rotation) {
    bool result;
    Shader shader = *application->textShader;

    TurnZBufferOff();
    EnableAlphaBlending();
    for (int i = 0; i < application->textLen; i++) {
        result = SetShaderParameters14(shader, application->openGL->worldMatrix, application->camera->viewMatrix,
                                       application->openGL->orthoMatrix, application->text[i].pixelColor);
        if (!result) {
            printf("Failed to set shader params\n");
            return false;
        }
        SetTexture(*application->font->texture);
        RenderText(application->text[i]);
    }

    TurnZBufferOn();
    DisableAlphaBlending();

    return true;
}
static bool renderApplicationPtr15(Application *application, float rotation) { return true; }
static bool renderApplicationPtr14(Application *application, float rotation) {

    Shader shader = *application->textShader;

    TurnZBufferOff();
    EnableAlphaBlending();
    for (int i = 0; i < application->textLen; i++) {
        bool result = SetShaderParameters14(shader, application->openGL->worldMatrix, application->camera->viewMatrix,
                                            application->openGL->orthoMatrix, application->text[i].pixelColor);
        if (!result) {
            printf("Failed to set shader params\n");
            return false;
        }
        SetTexture(*application->font->texture);
        RenderText(application->text[i]);
    }

    TurnZBufferOn();
    DisableAlphaBlending();

    return true;
}
static bool renderApplicationPtr13(Application *application, float rotation) {

    Shader shader = *application->bitmapShader;
    TurnZBufferOff();

    bool result = SetShaderParameters12(shader, application->openGL->worldMatrix, application->camera->viewMatrix,
                                        application->openGL->orthoMatrix);
    if (!result) {
        printf("Failed to set shader params\n");
        return false;
    }
    RenderSprite(*application->sprite);

    TurnZBufferOn();

    return true;
}
static bool renderApplicationPtr12(Application *application, float rotation) {
    Shader shader = *application->bitmapShader;

    TurnZBufferOff();

    printf("Setting shader params\n");
    bool result = SetShaderParameters12(shader, application->openGL->worldMatrix, application->camera->viewMatrix,
                                        application->openGL->orthoMatrix);
    if (!result) {
        printf("Failed to set shader params\n");
        return false;
    }
    RenderBitmap(*application->bitmap);

    TurnZBufferOn();

    return true;
}
static bool renderApplicationPtr11(Application *application, float rotation) {
    Shader shader = *application->entities[0].shader;
    Model model = application->entities[0].model;
    // float diffuseColorArray[20] = {1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //                                1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.753f, 0.796f};
    float diffuseColorArray[4] = {1.0f, 0.753f, 0.796f, 1.0f};
    // float lightPositionArray[15] = {-3.0f, 1.0f, 3.0f, 3.0f,  1.0f, 3.0f, -3.0f, 1.0f,
    //                                 -3.0f, 3.0f, 1.0f, -3.0f, 1.5f, 1.0f, 1.5f};
    float lightPositionArray[3] = {0.0f, 1.0f, 0.0f};
    int numLights = 1;
    bool result =
        SetShaderParameters11(shader, application->openGL->worldMatrix, application->camera->viewMatrix,
                              application->openGL->projectionMatrix, diffuseColorArray, lightPositionArray, numLights);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    return true;
}

static bool renderApplicationPtr10(Application *application, float rotation) {
    Shader shader = *application->entities[0].shader;
    Model model = application->entities[0].model;

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

    bool result = SetShaderParameters10(shader, worldMatrix, application->camera->viewMatrix,
                                        application->openGL->projectionMatrix, lightDirection, diffuseLightColor,
                                        ambientLight, cameraPosition, specularColor, specularPower);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    MatrixScale(scaleMatrix, 0.5f, 0.5f, 0.5f);
    MatrixRotationY(rotateMatrix, rotation);
    MatrixTranslation(translateMatrix, -2.5f, 0.0f, -2.0f);

    MatrixMultiply(srMatrix, scaleMatrix, rotateMatrix);
    MatrixMultiply(worldMatrix, srMatrix, translateMatrix);
    result = SetShaderParameters10(shader, worldMatrix, application->camera->viewMatrix,
                                   application->openGL->projectionMatrix, lightDirection, diffuseLightColor,
                                   ambientLight, cameraPosition, specularColor, specularPower);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    return true;
}
static bool renderApplicationPtr9(Application *application, float rotation) {
    Shader shader = *application->entities[0].shader;
    Model model = application->entities[0].model;

    float worldMatrix[16], rotateMatrix[16], translateMatrix[16], scaleMatrix[16], srMatrix[16];
    Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);

    float diffuseColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightDirection[3] = {1.0f, 0.0f, 0.0f};
    float ambientLight[4] = {0.15f, 0.15f, 0.15f, 1.0f};

    MatrixRotationY(rotateMatrix, rotation);
    MatrixTranslation(translateMatrix, 2.5f, 0.0f, -2.0f);
    MatrixMultiply(worldMatrix, rotateMatrix, translateMatrix);

    bool result =
        SetShaderParameters9(shader, worldMatrix, application->camera->viewMatrix,
                             application->openGL->projectionMatrix, lightDirection, diffuseColor, ambientLight);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    MatrixScale(scaleMatrix, 0.5f, 0.5f, 0.5f);
    MatrixRotationY(rotateMatrix, rotation);
    MatrixTranslation(translateMatrix, -2.5f, 0.0f, -2.0f);

    MatrixMultiply(srMatrix, scaleMatrix, rotateMatrix);
    MatrixMultiply(worldMatrix, srMatrix, translateMatrix);
    result = SetShaderParameters9(shader, worldMatrix, application->camera->viewMatrix,
                                  application->openGL->projectionMatrix, lightDirection, diffuseColor, ambientLight);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);
    return true;
}
static bool renderApplicationPtr8(Application *application, float rotation) {

    Shader shader = *application->entities[0].shader;
    Model model = application->entities[0].model;

    float worldMatrix[16], rotateMatrix[16], translateMatrix[16], scaleMatrix[16], srMatrix[16];
    Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);

    float diffuseColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightDirection[3] = {0.0f, 0.0f, 1.0f};

    MatrixRotationY(rotateMatrix, rotation);
    float a = cosf(rotation) * 2;
    float b = sinf(rotation) * 2;
    MatrixTranslation(translateMatrix, a, 0.0f, b);
    MatrixMultiply(worldMatrix, application->openGL->worldMatrix, translateMatrix);

    bool result = SetShaderParameters6(shader, worldMatrix, application->camera->viewMatrix,
                                       application->openGL->projectionMatrix, lightDirection, diffuseColor);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    MatrixScale(scaleMatrix, 0.5f, 0.5f, 0.5f);
    // MatrixRotationY(rotateMatrix, rotation);
    MatrixTranslation(translateMatrix, -a, 0.0f, -b);

    // MatrixMultiply(srMatrix, scaleMatrix, rotateMatrix);
    MatrixMultiply(worldMatrix, scaleMatrix, translateMatrix);
    result = SetShaderParameters6(shader, worldMatrix, application->camera->viewMatrix,
                                  application->openGL->projectionMatrix, lightDirection, diffuseColor);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    return true;
}
static bool renderApplicationPtr7(Application *application, float rotation) {

    Shader shader = *application->entities[0].shader;
    Model model = application->entities[0].model;

    float worldMatrix[16];
    Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);
    MatrixRotationY(worldMatrix, rotation);
    float diffuseColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightDirection[3] = {1.0f, 0.0f, 0.0f};
    bool result = SetShaderParameters6(shader, worldMatrix, application->camera->viewMatrix,
                                       application->openGL->projectionMatrix, lightDirection, diffuseColor);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    return true;
}
static bool renderApplicationPtr6(Application *application, float rotation) {

    Shader shader = *application->entities[0].shader;
    Model model = application->entities[0].model;

    float worldMatrix[16];
    Get4x4Matrix(worldMatrix, application->openGL->worldMatrix);
    MatrixRotationY(worldMatrix, rotation);
    float diffuseColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightDirection[3] = {1.0f, 0.0f, 0.0f};
    bool result = SetShaderParameters6(shader, worldMatrix, application->camera->viewMatrix,
                                       application->openGL->projectionMatrix, lightDirection, diffuseColor);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    return true;
}

static bool renderApplicationPtr5(Application *application, float rotation) {
    Shader shader = *application->entities[0].shader;
    Model model = application->entities[0].model;

    bool result = SetShaderParameters5(shader, application->openGL->worldMatrix, application->camera->viewMatrix,
                                       application->openGL->projectionMatrix);
    if (!result) {
        printf("ERROR: Failed to set shader params\n");
        return false;
    }
    RenderModel(model);

    return true;
}

TutorialData *Tutorial5() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;

    tutorial->entityLen = 1;
    tutorial->entities = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/texture.vs";
    shader->fragmentShaderName = "./shaders/texture.ps";

    shader->variablesLen = 2;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";

    TutorialEntity *entity = (TutorialEntity *)malloc(sizeof(TutorialEntity));
    entity->shader = shader;
    entity->model = "./data/triangle.txt";
    entity->textureLen = 1;
    entity->textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity->textures[0] = "./data/blizzard01.tga";
    entity->enableAttribPtr = &enableAttribPtr5;
    entity->wrap = false;

    tutorial->entities[0] = *entity;

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -5.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr5;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}

TutorialData *Tutorial6() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;
    tutorial->entityLen = 1;
    tutorial->entities = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/light3.vs";
    shader->fragmentShaderName = "./shaders/light3.ps";

    shader->variablesLen = 3;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    shader->variables[2] = "inputNormal";

    TutorialEntity *entity = (TutorialEntity *)malloc(sizeof(TutorialEntity));
    entity->shader = shader;
    entity->model = "./data/cube.txt";
    entity->textureLen = 1;
    entity->textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity->textures[0] = "./data/blizzard01.tga";
    entity->enableAttribPtr = &enableAttribPtr6;
    entity->wrap = false;

    tutorial->entities[0] = *entity;

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -5.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr6;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial7() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;
    tutorial->entityLen = 1;
    tutorial->entities = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/light3.vs";
    shader->fragmentShaderName = "./shaders/light3.ps";

    shader->variablesLen = 3;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    shader->variables[2] = "inputNormal";

    TutorialEntity *entity = (TutorialEntity *)malloc(sizeof(TutorialEntity));
    entity->shader = shader;
    entity->model = "./data/cube.txt";
    entity->textureLen = 1;
    entity->textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity->textures[0] = "./data/blizzard01.tga";
    entity->enableAttribPtr = &enableAttribPtr6;
    entity->wrap = false;

    tutorial->entities[0] = *entity;

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -5.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr7;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial8() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;
    tutorial->entityLen = 1;
    tutorial->entities = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/light3.vs";
    shader->fragmentShaderName = "./shaders/light3.ps";

    shader->variablesLen = 3;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    shader->variables[2] = "inputNormal";

    TutorialEntity *entity = (TutorialEntity *)malloc(sizeof(TutorialEntity));
    entity->shader = shader;
    entity->model = "./data/cube.txt";
    entity->textureLen = 1;
    entity->textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity->textures[0] = "./data/ball01.tga";
    entity->enableAttribPtr = &enableAttribPtr8;
    entity->wrap = false;

    tutorial->entities[0] = *entity;

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr8;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial10() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;
    tutorial->entityLen = 1;
    tutorial->entities = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/light2.vs";
    shader->fragmentShaderName = "./shaders/light2.ps";

    shader->variablesLen = 3;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    shader->variables[2] = "inputNormal";

    TutorialEntity *entity = (TutorialEntity *)malloc(sizeof(TutorialEntity));
    entity->shader = shader;
    entity->model = "./data/sphere.txt";
    entity->textureLen = 1;
    entity->textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity->textures[0] = "./data/stone01.tga";
    entity->enableAttribPtr = &enableAttribPtr10;
    entity->wrap = true;

    tutorial->entities[0] = *entity;

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr10;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial11() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;
    tutorial->entityLen = 1;
    tutorial->entities = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/light4.vs";
    shader->fragmentShaderName = "./shaders/light4.ps";

    shader->variablesLen = 3;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    shader->variables[2] = "inputNormal";

    TutorialEntity *entity = (TutorialEntity *)malloc(sizeof(TutorialEntity));
    entity->shader = shader;
    entity->model = "./data/plane.txt";
    entity->textureLen = 1;
    entity->textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity->textures[0] = "./data/stone01.tga";
    entity->enableAttribPtr = &enableAttribPtr11;
    entity->wrap = true;

    tutorial->entities[0] = *entity;

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 2.0f;
    tutorial->cameraZ = -12.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr11;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial9() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;
    tutorial->entityLen = 1;
    tutorial->entities = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/light.vs";
    shader->fragmentShaderName = "./shaders/light.ps";

    shader->variablesLen = 3;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    shader->variables[2] = "inputNormal";

    TutorialEntity *entity = (TutorialEntity *)malloc(sizeof(TutorialEntity));
    entity->shader = shader;
    entity->model = "./data/cube.txt";
    entity->textureLen = 1;
    entity->textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity->textures[0] = "./data/stone01.tga";
    entity->enableAttribPtr = &enableAttribPtr8;
    entity->wrap = true;

    tutorial->entities[0] = *entity;

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr9;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial12() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = BITMAP;

    tutorial->bitmapFilename = "./data/blizzard01.tga";

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/texture.vs";
    shader->fragmentShaderName = "./shaders/texture.ps";

    shader->variablesLen = 2;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    tutorial->bitmapShader = shader;

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr12;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}

TutorialData *Tutorial13() {
    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = SPRITE;

    tutorial->spriteFilename = "./data/sprite_data_01.txt";
    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/texture.vs";
    shader->fragmentShaderName = "./shaders/texture.ps";

    shader->variablesLen = 2;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    tutorial->bitmapShader = shader;

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr13;

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

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/font.vs";
    shader->fragmentShaderName = "./shaders/font.ps";

    shader->variablesLen = 2;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    tutorial->textShader = shader;

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 0.0f;
    tutorial->cameraZ = -5.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr14;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial15() {

    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = FONT;

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/font.vs";
    shader->fragmentShaderName = "./shaders/font.ps";

    shader->variablesLen = 2;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 0.0f;
    tutorial->cameraZ = -5.0f;
    tutorial->textShader = shader;

    tutorial->renderApplicationPtr = &renderApplicationPtr15;

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

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/font.vs";
    shader->fragmentShaderName = "./shaders/font.ps";

    shader->variablesLen = 2;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 0.0f;
    tutorial->cameraZ = -10.0f;
    tutorial->textShader = shader;

    tutorial->renderApplicationPtr = &renderApplicationPtr16;
    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = true;

    return tutorial;
}
TutorialData *Tutorial17() {

    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));
    tutorial->tutorial = MODEL;

    tutorial->entityLen = 1;
    tutorial->entities = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/multitexture.vs";
    shader->fragmentShaderName = "./shaders/multitexture.ps";

    shader->variablesLen = 3;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    shader->variables[2] = "inputNormal";

    TutorialEntity *entity = (TutorialEntity *)malloc(sizeof(TutorialEntity));
    entity->shader = shader;
    entity->model = "./data/square.txt";
    entity->textureLen = 2;
    entity->textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity->textures[0] = "./data/stone01.tga";
    entity->textures[1] = "./data/blizzard01.tga";
    entity->enableAttribPtr = &enableAttribPtr7;
    entity->wrap = false;

    tutorial->entities[0] = *entity;

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -5.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr17;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial18() {

    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));
    tutorial->tutorial = MODEL;

    tutorial->entityLen = 1;
    tutorial->entities = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/lightmap.vs";
    shader->fragmentShaderName = "./shaders/lightmap.ps";

    shader->variablesLen = 3;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    shader->variables[2] = "inputNormal";

    TutorialEntity *entity = (TutorialEntity *)malloc(sizeof(TutorialEntity));
    entity->shader = shader;
    entity->model = "./data/square.txt";
    entity->textureLen = 2;
    entity->textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity->textures[0] = "./data/stone01.tga";
    entity->textures[1] = "./data/light01.tga";
    entity->enableAttribPtr = &enableAttribPtr7;
    entity->wrap = false;

    tutorial->entities[0] = *entity;

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -5.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr18;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial19() {

    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));
    tutorial->tutorial = MODEL;

    tutorial->entityLen = 1;
    tutorial->entities = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/alphamap.vs";
    shader->fragmentShaderName = "./shaders/alphamap.ps";

    shader->variablesLen = 3;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    shader->variables[2] = "inputNormal";

    TutorialEntity *entity = (TutorialEntity *)malloc(sizeof(TutorialEntity));
    entity->shader = shader;
    entity->model = "./data/square.txt";
    entity->textureLen = 3;
    entity->textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity->textures[0] = "./data/stone01.tga";
    entity->textures[1] = "./data/dirt01.tga";
    entity->textures[2] = "./data/alpha01.tga";
    entity->enableAttribPtr = &enableAttribPtr7;
    entity->wrap = false;

    tutorial->entities[0] = *entity;

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -5.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr19;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial20() {

    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));

    tutorial->tutorial = MODEL;

    tutorial->entityLen = 1;
    tutorial->entities = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/normalmap.vs";
    shader->fragmentShaderName = "./shaders/normalmap.ps";

    shader->variablesLen = 5;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    shader->variables[2] = "inputNormal";
    shader->variables[3] = "inputTangent";
    shader->variables[4] = "inputBinormal";

    TutorialEntity *entity = (TutorialEntity *)malloc(sizeof(TutorialEntity));
    entity->shader = shader;
    entity->model = "./data/sphere.txt";
    entity->textureLen = 2;
    entity->textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity->textures[0] = "./data/stone01.tga";
    entity->textures[1] = "./data/normal01.tga";
    entity->enableAttribPtr = &enableAttribPtr20;
    entity->wrap = true;

    tutorial->entities[0] = *entity;

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr20;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial21() {

    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));
    tutorial->tutorial = MODEL;

    tutorial->entityLen = 1;
    tutorial->entities = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);

    TutorialShader *shader = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader->vertexShaderName = "./shaders/specmap.vs";
    shader->fragmentShaderName = "./shaders/specmap.ps";

    shader->variablesLen = 5;
    shader->variables = (const char **)malloc(sizeof(char *) * shader->variablesLen);
    shader->variables[0] = "inputPosition";
    shader->variables[1] = "inputTexCoord";
    shader->variables[2] = "inputNormal";
    shader->variables[3] = "inputTangent";
    shader->variables[4] = "inputBinormal";

    TutorialEntity *entity = tutorial->entities;
    entity[0].shader = shader;
    entity[0].model = "./data/cube.txt";
    entity[0].textureLen = 3;
    entity[0].textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity[0].textures[0] = "./data/stone02.tga";
    entity[0].textures[1] = "./data/normal02.tga";
    entity[0].textures[2] = "./data/spec02.tga";
    entity[0].enableAttribPtr = &enableAttribPtr20;
    entity[0].wrap = true;

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr21;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial22() {

    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));
    tutorial->tutorial = MODEL;

    tutorial->entityLen = 3;

    TutorialShader *shader1 = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader1->vertexShaderName = "./shaders/texture.vs";
    shader1->fragmentShaderName = "./shaders/texture.ps";

    shader1->variablesLen = 5;
    shader1->variables = (const char **)malloc(sizeof(char *) * shader1->variablesLen);
    shader1->variables[0] = "inputPosition";
    shader1->variables[1] = "inputTexCoord";

    TutorialEntity *entity = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);
    entity[0].shader = shader1;
    entity[0].model = "./data/sphere.txt";
    entity[0].textureLen = 1;
    entity[0].textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity[0].textures[0] = "./data/stone01.tga";
    entity[0].enableAttribPtr = &enableAttribPtr5;
    entity[0].wrap = true;

    TutorialShader *shader2 = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader2->vertexShaderName = "./shaders/light3.vs";
    shader2->fragmentShaderName = "./shaders/light3.ps";

    shader2->variablesLen = 3;
    shader2->variables = (const char **)malloc(sizeof(char *) * shader2->variablesLen);
    shader2->variables[0] = "inputPosition";
    shader2->variables[1] = "inputTexCoord";
    shader1->variables[2] = "inputNormal";

    entity[1].shader = shader2;
    entity[1].model = "./data/sphere.txt";
    entity[1].textureLen = 1;
    entity[1].textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity[1].textures[0] = "./data/stone01.tga";
    entity[1].enableAttribPtr = &enableAttribPtr6;
    entity[1].wrap = true;

    TutorialShader *shader3 = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader3->vertexShaderName = "./shaders/normalmap.vs";
    shader3->fragmentShaderName = "./shaders/normalmap.ps";

    shader3->variablesLen = 5;
    shader3->variables = (const char **)malloc(sizeof(char *) * shader3->variablesLen);
    shader3->variables[0] = "inputPosition";
    shader3->variables[1] = "inputTexCoord";
    shader3->variables[2] = "inputNormal";
    shader3->variables[3] = "inputTangent";
    shader3->variables[4] = "inputBinormal";

    entity[2].shader = shader3;
    entity[2].model = "./data/sphere.txt";
    entity[2].textureLen = 2;
    entity[2].textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
    entity[2].textures[0] = "./data/stone01.tga";
    entity[2].textures[1] = "./data/normal01.tga";
    entity[2].enableAttribPtr = &enableAttribPtr20;
    entity[2].wrap = true;

    tutorial->entities = entity;

    tutorial->cameraX = 0.0f;
    tutorial->cameraX = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr22;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
TutorialData *Tutorial23() {

    TutorialData *tutorial = (TutorialData *)malloc(sizeof(TutorialData));
    tutorial->tutorial = MODEL;

    tutorial->entityLen = 10;

    TutorialShader *shader1 = (TutorialShader *)malloc(sizeof(TutorialShader));
    shader1->vertexShaderName = "./shaders/texture.vs";
    shader1->fragmentShaderName = "./shaders/texture.ps";

    shader1->variablesLen = 2;
    shader1->variables = (const char **)malloc(sizeof(char *) * shader1->variablesLen);
    shader1->variables[0] = "inputPosition";
    shader1->variables[1] = "inputTexCoord";

    TutorialEntity *entity = (TutorialEntity *)malloc(sizeof(TutorialEntity) * tutorial->entityLen);
    for (int i = 0; i < tutorial->entityLen; ++i) {
        entity[i].shader = shader1;
        entity[i].model = "./data/cube.txt";
        entity[i].textureLen = 1;
        entity[i].textures = (const char **)malloc(sizeof(char *) * entity->textureLen);
        entity[i].textures[0] = "./data/stone01.tga";
        entity[i].enableAttribPtr = &enableAttribPtr5;
        entity[i].wrap = true;
        entity[i].randomPos = true;
    }

    tutorial->entities = entity;

    tutorial->cameraX = 0.0f;
    tutorial->cameraY = 0.0f;
    tutorial->cameraZ = -10.0f;

    tutorial->renderApplicationPtr = &renderApplicationPtr23;

    tutorial->rotationSpeed = 0.0174532925f;
    tutorial->mouse = false;

    return tutorial;
}
void ShutdownTutorial(TutorialData *tutorial) {
    for (int i = 0; i < tutorial->entityLen; i++) {
        free(tutorial->entities[i].textures);
        free(tutorial->entities[i].shader->variables);
        free(tutorial->entities[i].shader);
    }
    free(tutorial->entities);
    if (tutorial->textShader) {
        free(tutorial->textShader);
    }
}
