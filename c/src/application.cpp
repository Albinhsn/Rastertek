
#include "application.h"

bool RenderApplication() {}
static bool Initialize(Display *, Window, int, int);
static void ShutdownApplication(Application application) {

    // Release the color shader object.
    auto texture = application.texture;
    if (texture) {
        free(texture);
        texture = 0;
    }

    // auto model = application.model;
    // // Release the model object.
    // if (model) {
    //     model->Shutdown();
    //     free(model);
    //     model = 0;
    // }

    // // Release the camera object.
    // if (m_Camera) {
    //     delete m_Camera;
    //     m_Camera = 0;
    // }

    // if (m_OpenGL) {
    //     m_OpenGL->Shutdown();
    //     delete m_OpenGL;
    //     m_OpenGL = 0;
    // }
}
static bool Frame(InputClass *);
