#include "opengl.h"

#include "utils.h"
#include "vector.h"

bool LoadExtensionList(OpenGL *openGL) {

    auto glCreateShader = (PFNGLCREATESHADERPROC)glXGetProcAddress((unsigned char *)"glCreateShader");
    if (!glCreateShader) {
        return false;
    }
    openGL->glCreateShader = glCreateShader;

    auto glShaderSource = (PFNGLSHADERSOURCEPROC)glXGetProcAddress((unsigned char *)"glShaderSource");
    if (!glShaderSource) {
        return false;
    }
    openGL->glShaderSource = glShaderSource;

    auto glCompileShader = (PFNGLCOMPILESHADERPROC)glXGetProcAddress((unsigned char *)"glCompileShader");
    if (!glCompileShader) {
        return false;
    }
    openGL->glCompileShader = glCompileShader;

    auto glGetShaderiv = (PFNGLGETSHADERIVPROC)glXGetProcAddress((unsigned char *)"glGetShaderiv");
    if (!glGetShaderiv) {
        return false;
    }
    openGL->glGetShaderiv = glGetShaderiv;

    auto glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glXGetProcAddress((unsigned char *)"glGetShaderInfoLog");
    if (!glGetShaderInfoLog) {
        return false;
    }
    openGL->glGetShaderInfoLog = glGetShaderInfoLog;

    auto glCreateProgram = (PFNGLCREATEPROGRAMPROC)glXGetProcAddress((unsigned char *)"glCreateProgram");
    if (!glCreateProgram) {
        return false;
    }
    openGL->glCreateProgram = glCreateProgram;

    auto glAttachShader = (PFNGLATTACHSHADERPROC)glXGetProcAddress((unsigned char *)"glAttachShader");
    if (!glAttachShader) {
        return false;
    }
    openGL->glAttachShader = glAttachShader;

    auto glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)glXGetProcAddress((unsigned char *)"glBindAttribLocation");
    if (!glBindAttribLocation) {
        return false;
    }
    openGL->glBindAttribLocation = glBindAttribLocation;

    auto glLinkProgram = (PFNGLLINKPROGRAMPROC)glXGetProcAddress((unsigned char *)"glLinkProgram");
    if (!glLinkProgram) {
        return false;
    }
    openGL->glLinkProgram = glLinkProgram;

    auto glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glXGetProcAddress((unsigned char *)"glGetProgramiv");
    if (!glGetProgramiv) {
        return false;
    }
    openGL->glGetProgramiv = glGetProgramiv;

    auto glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glXGetProcAddress((unsigned char *)"glGetProgramInfoLog");
    if (!glGetProgramInfoLog) {
        return false;
    }
    openGL->glGetProgramInfoLog = glGetProgramInfoLog;

    auto glDetachShader = (PFNGLDETACHSHADERPROC)glXGetProcAddress((unsigned char *)"glDetachShader");
    if (!glDetachShader) {
        return false;
    }
    openGL->glDetachShader = glDetachShader;

    auto glDeleteShader = (PFNGLDELETESHADERPROC)glXGetProcAddress((unsigned char *)"glDeleteShader");
    if (!glDeleteShader) {
        return false;
    }
    openGL->glDeleteShader = glDeleteShader;

    auto glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glXGetProcAddress((unsigned char *)"glDeleteProgram");
    if (!glDeleteProgram) {
        return false;
    }
    openGL->glDeleteProgram = glDeleteProgram;

    auto glUseProgram = (PFNGLUSEPROGRAMPROC)glXGetProcAddress((unsigned char *)"glUseProgram");
    if (!glUseProgram) {
        return false;
    }
    openGL->glUseProgram = glUseProgram;

    auto glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glXGetProcAddress((unsigned char *)"glGetUniformLocation");
    if (!glGetUniformLocation) {
        return false;
    }
    openGL->glGetUniformLocation = glGetUniformLocation;

    auto glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glXGetProcAddress((unsigned char *)"glUniformMatrix4fv");
    if (!glUniformMatrix4fv) {
        return false;
    }
    openGL->glUniformMatrix4fv = glUniformMatrix4fv;

    auto glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glXGetProcAddress((unsigned char *)"glGenVertexArrays");
    if (!glGenVertexArrays) {
        return false;
    }
    openGL->glGenVertexArrays = glGenVertexArrays;

    auto glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glXGetProcAddress((unsigned char *)"glBindVertexArray");
    if (!glBindVertexArray) {
        return false;
    }
    openGL->glBindVertexArray = glBindVertexArray;

    auto glGenBuffers = (PFNGLGENBUFFERSPROC)glXGetProcAddress((unsigned char *)"glGenBuffers");
    if (!glGenBuffers) {
        return false;
    }
    openGL->glGenBuffers = glGenBuffers;

    auto glBindBuffer = (PFNGLBINDBUFFERPROC)glXGetProcAddress((unsigned char *)"glBindBuffer");
    if (!glBindBuffer) {
        return false;
    }
    openGL->glBindBuffer = glBindBuffer;

    auto glBufferData = (PFNGLBUFFERDATAPROC)glXGetProcAddress((unsigned char *)"glBufferData");
    if (!glBufferData) {
        return false;
    }
    openGL->glBufferData = glBufferData;

    auto glEnableVertexAttribArray =
        (PFNGLENABLEVERTEXATTRIBARRAYPROC)glXGetProcAddress((unsigned char *)"glEnableVertexAttribArray");
    if (!glEnableVertexAttribArray) {
        return false;
    }
    openGL->glEnableVertexAttribArray = glEnableVertexAttribArray;

    auto glVertexAttribPointer =
        (PFNGLVERTEXATTRIBPOINTERPROC)glXGetProcAddress((unsigned char *)"glVertexAttribPointer");
    if (!glVertexAttribPointer) {
        return false;
    }
    openGL->glVertexAttribPointer = glVertexAttribPointer;

    auto glDisableVertexAttribArray =
        (PFNGLDISABLEVERTEXATTRIBARRAYPROC)glXGetProcAddress((unsigned char *)"glDisableVertexAttribArray");
    if (!glDisableVertexAttribArray) {
        return false;
    }
    openGL->glDisableVertexAttribArray = glDisableVertexAttribArray;

    auto glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glXGetProcAddress((unsigned char *)"glDeleteBuffers");
    if (!glDeleteBuffers) {
        return false;
    }
    openGL->glDeleteBuffers = glDeleteBuffers;

    auto glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glXGetProcAddress((unsigned char *)"glDeleteVertexArrays");
    if (!glDeleteVertexArrays) {
        return false;
    }
    openGL->glDeleteVertexArrays = glDeleteVertexArrays;

    auto glUniform1i = (PFNGLUNIFORM1IPROC)glXGetProcAddress((unsigned char *)"glUniform1i");
    if (!glUniform1i) {
        return false;
    }
    openGL->glUniform1i = glUniform1i;

    auto glActiveTexture = (PFNGLACTIVETEXTUREPROC)glXGetProcAddress((unsigned char *)"glActiveTexture");
    if (!glActiveTexture) {
        return false;
    }
    openGL->glActiveTexture = glActiveTexture;

    auto glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glXGetProcAddress((unsigned char *)"glGenerateMipmap");
    if (!glGenerateMipmap) {
        return false;
    }
    openGL->glGenerateMipmap = glGenerateMipmap;

    auto glUniform2fv = (PFNGLUNIFORM2FVPROC)glXGetProcAddress((unsigned char *)"glUniform2fv");
    if (!glUniform2fv) {
        return false;
    }
    openGL->glUniform2fv = glUniform2fv;

    auto glUniform3fv = (PFNGLUNIFORM3FVPROC)glXGetProcAddress((unsigned char *)"glUniform3fv");
    if (!glUniform3fv) {
        return false;
    }
    openGL->glUniform3fv = glUniform3fv;

    auto glUniform4fv = (PFNGLUNIFORM4FVPROC)glXGetProcAddress((unsigned char *)"glUniform4fv");
    if (!glUniform4fv) {
        return false;
    }
    openGL->glUniform4fv = glUniform4fv;

    auto glMapBuffer = (PFNGLMAPBUFFERPROC)glXGetProcAddress((unsigned char *)"glMapBuffer");
    if (!glMapBuffer) {
        return false;
    }
    openGL->glMapBuffer = glMapBuffer;

    auto glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)glXGetProcAddress((unsigned char *)"glUnmapBuffer");
    if (!glUnmapBuffer) {
        return false;
    }
    openGL->glUnmapBuffer = glUnmapBuffer;

    auto glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((unsigned char *)"glXSwapIntervalEXT");
    if (!glXSwapIntervalEXT) {
        return false;
    }
    openGL->glXSwapIntervalEXT = glXSwapIntervalEXT;

    auto glUniform1f = (PFNGLUNIFORM1FPROC)glXGetProcAddress((unsigned char *)"glUniform1f");
    if (!glUniform1f) {
        return false;
    }
    openGL->glUniform1f = glUniform1f;

    auto glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)glXGetProcAddress((unsigned char *)"glGenFramebuffers");
    if (!glGenFramebuffers) {
        return false;
    }
    openGL->glGenFramebuffers = glGenFramebuffers;

    auto glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)glXGetProcAddress((unsigned char *)"glDeleteFramebuffers");
    if (!glDeleteFramebuffers) {
        return false;
    }
    openGL->glDeleteFramebuffers = glDeleteFramebuffers;

    auto glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)glXGetProcAddress((unsigned char *)"glBindFramebuffer");
    if (!glBindFramebuffer) {
        return false;
    }
    openGL->glBindFramebuffer = glBindFramebuffer;

    auto glFramebufferTexture2D =
        (PFNGLFRAMEBUFFERTEXTURE2DPROC)glXGetProcAddress((unsigned char *)"glFramebufferTexture2D");
    if (!glFramebufferTexture2D) {
        return false;
    }
    openGL->glFramebufferTexture2D = glFramebufferTexture2D;

    auto glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)glXGetProcAddress((unsigned char *)"glGenRenderbuffers");
    if (!glGenRenderbuffers) {
        return false;
    }
    openGL->glGenRenderbuffers = glGenRenderbuffers;

    auto glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)glXGetProcAddress((unsigned char *)"glBindRenderbuffer");
    if (!glBindRenderbuffer) {
        return false;
    }
    openGL->glBindRenderbuffer = glBindRenderbuffer;

    auto glRenderbufferStorage =
        (PFNGLRENDERBUFFERSTORAGEPROC)glXGetProcAddress((unsigned char *)"glRenderbufferStorage");
    if (!glRenderbufferStorage) {
        return false;
    }
    openGL->glRenderbufferStorage = glRenderbufferStorage;

    auto glFramebufferRenderbuffer =
        (PFNGLFRAMEBUFFERRENDERBUFFERPROC)glXGetProcAddress((unsigned char *)"glFramebufferRenderbuffer");
    if (!glFramebufferRenderbuffer) {
        return false;
    }
    openGL->glFramebufferRenderbuffer = glFramebufferRenderbuffer;

    auto glDrawBuffers = (PFNGLDRAWBUFFERSARBPROC)glXGetProcAddress((unsigned char *)"glDrawBuffers");
    if (!glDrawBuffers) {
        return false;
    }
    openGL->glDrawBuffers = glDrawBuffers;

    auto glDeleteRenderbuffers =
        (PFNGLDELETERENDERBUFFERSPROC)glXGetProcAddress((unsigned char *)"glDeleteRenderbuffers");
    if (!glDeleteRenderbuffers) {
        return false;
    }
    openGL->glDeleteRenderbuffers = glDeleteRenderbuffers;

    auto glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)glXGetProcAddress((unsigned char *)"glBlendFuncSeparate");
    if (!glBlendFuncSeparate) {
        return false;
    }
    openGL->glBlendFuncSeparate = glBlendFuncSeparate;

    return true;
}

bool InitializeOpenGL(OpenGL *openGL, Display *display, Window win, int screenWidth, int screenHeight, float screenNear,
                      float screenDepth, bool vsync) {
    openGL->screenWidth = screenWidth;
    openGL->screenHeight = screenWidth;
    openGL->display = display;
    openGL->hwnd = win;

    if (!LoadExtensionList(openGL)) {
        return false;
    }

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    GLXDrawable drawable = glXGetCurrentDrawable();
    if (vsync) {
        openGL->glXSwapIntervalEXT(openGL->display, drawable, 1);
    } else {
        openGL->glXSwapIntervalEXT(openGL->display, drawable, 0);
    }
    BuildIdentityMatrix(openGL->worldMatrix);

    float fov = PI / 4.0f;
    float screenAspect = (float)screenWidth / (float)screenHeight;

    BuildPerspectiveFovMatrix(openGL->projectionMatrix, fov, screenAspect, screenNear, screenDepth);
    BuildOrthoMatrix(openGL->orthoMatrix, (float)screenWidth, (float)screenHeight, screenNear, screenDepth);

    return true;
}

void BeginScene(float red, float green, float blue, float alpha) {

    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void EndScene(Display *display, Window hwnd) { glXSwapBuffers(display, hwnd); }

void TurnZBufferOn() {
    // Enable depth testing.
    glEnable(GL_DEPTH_TEST);
}
void TurnZBufferOff() {
    // Disable depth testing.
    glDisable(GL_DEPTH_TEST);
}

void EnableAlphaBlending(OpenGL *openGL) {
    // Enable alpha blending.
    glEnable(GL_BLEND);

    // Set the blending equation.
    openGL->glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
}
void DisableAlphaBlending() {
    // Disable alpha blending.
    glDisable(GL_BLEND);
}

void SetBackBufferRenderTarget(OpenGL *openGL) {
    openGL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return;
}
void ResetViewport(int screenWidth, int screenHeight) { glViewport(0, 0, screenWidth, screenHeight); }

void EnableClipping() {
    // Enable clip plane 0.
    glEnable(GL_CLIP_DISTANCE0);
}
void DisableClipping() {
    // Disable clip plane 0.
    glDisable(GL_CLIP_DISTANCE0);
}
