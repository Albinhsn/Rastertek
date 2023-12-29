#include "opengl.h"

#include "utils.h"
#include "vector.h"
#include <GL/gl.h>
#include <stdio.h>

uint glCreateShader(uint shaderType) {
    auto glCreateShader = (PFNGLCREATESHADERPROC)glXGetProcAddress((unsigned char *)"glCreateShader");
    if (!glCreateShader) {
        return false;
    }
    return glCreateShader(shaderType);
}

void glShaderSource(uint shader, const char *buffer) {
    auto glShaderSource = (PFNGLSHADERSOURCEPROC)glXGetProcAddress((unsigned char *)"glShaderSource");
    if (!glShaderSource) {
        printf("ERROR: Unable to cast glShaderSource\n");
        exit(2);
    }
    glShaderSource(shader, 1, &buffer, NULL);
}

void glCompileShader(uint shader) {
    auto glCompileShader = (PFNGLCOMPILESHADERPROC)glXGetProcAddress((unsigned char *)"glCompileShader");
    if (!glCompileShader) {
        printf("ERROR: Unable to cast glCompileShader\n");
        exit(2);
    }
    glCompileShader(shader);
}

void glGetShaderiv(uint shader, uint pname, int *status) {
    auto glGetShaderiv = (PFNGLGETSHADERIVPROC)glXGetProcAddress((unsigned char *)"glGetShaderiv");
    if (!glGetShaderiv) {
        printf("ERROR: Unable to cast glGetShaderiv\n");
        exit(2);
    }
    glGetShaderiv(shader, pname, status);
}

char *glGetShaderInfoLog(uint shaderId) {
    int logSize;
    char *infoLog;

    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);
    logSize++;

    infoLog = new char[logSize];
    infoLog[logSize - 1] = '\0';

    auto glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glXGetProcAddress((unsigned char *)"glGetShaderInfoLog");
    if (!glGetShaderInfoLog) {
        printf("ERROR: Unable to cast glGetShaderInfoLog\n");
        exit(2);
    }
    glGetShaderInfoLog(shaderId, logSize, NULL, infoLog);

    return infoLog;
}

uint glCreateProgram() {
    auto glCreateProgram = (PFNGLCREATEPROGRAMPROC)glXGetProcAddress((unsigned char *)"glCreateProgram");
    if (!glCreateProgram) {
        printf("ERROR: Unable to cast glCreateProgram\n");
        exit(2);
    }
    return glCreateProgram();
}

void glAttachShaders(uint shaderProgram, uint vShader, uint fShader) {
    auto glAttachShader = (PFNGLATTACHSHADERPROC)glXGetProcAddress((unsigned char *)"glAttachShader");
    if (!glAttachShader) {
        printf("ERROR: Unable to cast attachShader\n");
        exit(2);
    }
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
}

void glBindAttribLocation(uint shaderProgram, int location, const char *variableName) {
    auto glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)glXGetProcAddress((unsigned char *)"glBindAttribLocation");
    if (!glBindAttribLocation) {
        printf("ERROR: Unable to cast bindAttribLocation\n");
        exit(2);
    }

    glBindAttribLocation(shaderProgram, location, variableName);
}

void glLinkProgram(uint shaderProgram) {
    auto glLinkProgram = (PFNGLLINKPROGRAMPROC)glXGetProcAddress((unsigned char *)"glLinkProgram");
    if (!glLinkProgram) {
        printf("ERROR: Unable to cast glLinkProgram\n");
        exit(2);
    }
    glLinkProgram(shaderProgram);
}

void glGetProgramiv(uint shaderProgram, uint pname, int *status) {
    auto glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glXGetProcAddress((unsigned char *)"glGetProgramiv");
    if (!glGetProgramiv) {
        printf("ERROR: Unable to cast glGetProgramiv\n");
        exit(2);
    }
    glGetProgramiv(shaderProgram, pname, status);
}

char *glGetProgramInfoLog(uint programId) {
    int logSize;
    char *infoLog;

    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);
    logSize++;

    infoLog = new char[logSize];
    infoLog[logSize - 1] = '\0';

    // Now retrieve the info log.
    auto glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glXGetProcAddress((unsigned char *)"glGetProgramInfoLog");
    if (!glGetProgramInfoLog) {
        printf("ERROR: Unable to cast GetProgramInfoLog\n");
        exit(2);
    }
    glGetProgramInfoLog(programId, logSize, NULL, infoLog);

    return infoLog;
}

void glDetachShader(uint program, uint shader) {
    auto glDetachShader = (PFNGLDETACHSHADERPROC)glXGetProcAddress((unsigned char *)"glDetachShader");
    if (!glDetachShader) {
        printf("ERROR: Unable to cast glDetachShader\n");
        exit(2);
    }
    glDetachShader(program, shader);
}

void glDeleteShader(uint shader) {

    auto glDeleteShader = (PFNGLDELETESHADERPROC)glXGetProcAddress((unsigned char *)"glDeleteShader");
    if (!glDeleteShader) {
        printf("ERROR: Unable to cast glDeleteShader\n");
        exit(2);
    }
    glDeleteShader(shader);
}
void glDeleteProgram(uint program) {
    auto glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glXGetProcAddress((unsigned char *)"glDeleteProgram");
    if (!glDeleteProgram) {
        printf("ERROR: Unable to cast glDeleteShader\n");
        exit(2);
    }
    glDeleteProgram(program);
}

void glUseProgram(uint program) {
    auto glUseProgram = (PFNGLUSEPROGRAMPROC)glXGetProcAddress((unsigned char *)"glUseProgram");
    if (!glUseProgram) {
        printf("ERROR: Unable to cast glDeleteShader\n");
        exit(2);
    }
    glUseProgram(program);
}

int glGetUniformLocation(uint program, const char *variableName) {
    auto glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glXGetProcAddress((unsigned char *)"glGetUniformLocation");
    if (!glGetUniformLocation) {
        printf("ERROR: Unable to cast glGetUniformLocation\n");
        exit(2);
    }
    return glGetUniformLocation(program, variableName);
}

void glUniformMatrix4fv(int location, int count, bool transpose, const float *matrix) {
    auto glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glXGetProcAddress((unsigned char *)"glUniformMatrix4fv");
    if (!glUniformMatrix4fv) {
        printf("ERROR: Unable to cast glUniformMatrix4fv\n");
        exit(2);
    }
    glUniformMatrix4fv(location, count, transpose, matrix);
}

void glGenVertexArrays(int n, uint *buffer) {
    auto glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glXGetProcAddress((unsigned char *)"glGenVertexArrays");
    if (!glGenVertexArrays) {
        printf("ERROR: Unable to cast glGenVertexArrays\n");
        exit(2);
    }
    glGenVertexArrays(n, buffer);
}

void glBindVertexArray(uint buffer) {

    auto glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glXGetProcAddress((unsigned char *)"glBindVertexArray");
    if (!glBindVertexArray) {
        printf("ERROR: Unable to cast glBindVertexArray\n");
        exit(2);
    }
    glBindVertexArray(buffer);
}

void glGenBuffers(int n, uint *buffer) {
    auto glGenBuffers = (PFNGLGENBUFFERSPROC)glXGetProcAddress((unsigned char *)"glGenBuffers");
    if (!glGenBuffers) {
        printf("ERROR: Unable to cast glGenBuffers\n");
        exit(2);
    }
    glGenBuffers(n, buffer);
}

void glBindBuffer(GLenum target, GLuint buffer) {
    auto glBindBuffer = (PFNGLBINDBUFFERPROC)glXGetProcAddress((unsigned char *)"glBindBuffer");
    if (!glBindBuffer) {
        printf("ERROR: Unable to cast glBindBuffer\n");
        exit(2);
    }
    glBindBuffer(target, buffer);
}
void glBufferData(GLenum target, size_t size, void *data, GLenum usage) {

    auto glBufferData = (PFNGLBUFFERDATAPROC)glXGetProcAddress((unsigned char *)"glBufferData");
    if (!glBufferData) {
        printf("ERROR: Unable to cast glBufferData\n");
        exit(2);
    }
    glBufferData(target, size, data, usage);
}

void glEnableVertexAttribArray(uint index) {

    auto glEnableVertexAttribArray =
        (PFNGLENABLEVERTEXATTRIBARRAYPROC)glXGetProcAddress((unsigned char *)"glEnableVertexAttribArray");
    if (!glEnableVertexAttribArray) {
        printf("ERROR: Unable to cast glEnableVertexAttribArray\n");
        exit(2);
    }
    glEnableVertexAttribArray(index);
}

void glVertexAttribPointer(uint index, int size, GLenum type, bool normalized, size_t stride, void *pointer) {
    auto glVertexAttribPointer =
        (PFNGLVERTEXATTRIBPOINTERPROC)glXGetProcAddress((unsigned char *)"glVertexAttribPointer");
    if (!glVertexAttribPointer) {
        printf("ERROR: Unable to cast glVertexAttribArray\n");
        exit(2);
    }
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void glDisableVertexAttribArray(uint index) {
    auto glDisableVertexAttribArray =
        (PFNGLDISABLEVERTEXATTRIBARRAYPROC)glXGetProcAddress((unsigned char *)"glDisableVertexAttribArray");
    if (!glDisableVertexAttribArray) {
        printf("ERROR: Unable to cast glDisableVertexAttribArray\n");
        exit(2);
    }
    glDisableVertexAttribArray(index);
}

void glDeleteBuffers(int n, uint *buffers) {
    auto glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glXGetProcAddress((unsigned char *)"glDeleteBuffers");
    if (!glDeleteBuffers) {
        printf("ERROR: Unable to cast glDeleteBuffers\n");
        exit(2);
    }
    glDeleteBuffers(n, buffers);
}

void glDeleteVertexArrays(int n, uint *arrays) {
    auto glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glXGetProcAddress((unsigned char *)"glDeleteVertexArrays");
    if (!glDeleteVertexArrays) {
        printf("ERROR: Unable to cast glDeleteVertexArrays\n");
        exit(2);
    }
    glDeleteVertexArrays(n, arrays);
}

void glUniform1i(int location, int v0) {
    auto glUniform1i = (PFNGLUNIFORM1IPROC)glXGetProcAddress((unsigned char *)"glUniform1i");
    if (!glUniform1i) {
        printf("ERROR: Unable to cast glUniform1i\n");
        exit(2);
    }
    glUniform1i(location, v0);
}

void glGenerateMipmap(GLenum target) {
    auto glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glXGetProcAddress((unsigned char *)"glGenerateMipmap");
    if (!glGenerateMipmap) {
        printf("ERROR: Unable to cast glGenerateMipmap\n");
        exit(2);
    }
    glGenerateMipmap(target);
}
void glUniform2fv(int location, int count, float *value) {
    auto glUniform2fv = (PFNGLUNIFORM2FVPROC)glXGetProcAddress((unsigned char *)"glUniform2fv");
    if (!glUniform2fv) {
        printf("ERROR: Unable to cast glUniform2fv\n");
        exit(2);
    }
    glUniform2fv(location, count, value);
}
void glUniform3fv(int location, int count, float *value) {
    auto glUniform3fv = (PFNGLUNIFORM3FVPROC)glXGetProcAddress((unsigned char *)"glUniform3fv");
    if (!glUniform3fv) {
        printf("ERROR: Unable to cast glUniform3fv\n");
        exit(2);
    }
    glUniform3fv(location, count, value);
}
void glUniform4fv(int location, int count, float *value) {
    auto glUniform4fv = (PFNGLUNIFORM4FVPROC)glXGetProcAddress((unsigned char *)"glUniform4fv");
    if (!glUniform4fv) {
        printf("ERROR: Unable to cast glUniform4fv\n");
        exit(2);
    }
    glUniform4fv(location, count, value);
}

void *glMapBuffer(GLenum target, GLenum access) {
    auto glMapBuffer = (PFNGLMAPBUFFERPROC)glXGetProcAddress((unsigned char *)"glMapBuffer");
    if (!glMapBuffer) {
        printf("ERROR: Unable to cast glMapBuffer\n");
        exit(2);
    }
    return glMapBuffer(target, access);
}
void glUnmapBuffer(GLenum target) {
    auto glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)glXGetProcAddress((unsigned char *)"glUnmapBuffer");
    if (!glUnmapBuffer) {
        printf("ERROR: Unable to cast glUnmapBuffer\n");
        exit(2);
    }
    glUnmapBuffer(target);
}
void glXSwapIntervalEXT(Display *dpy, GLXDrawable drawable, int interval) {
    auto glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((unsigned char *)"glXSwapIntervalEXT");
    if (!glXSwapIntervalEXT) {
        printf("ERROR: Unable to cast glXSwapIntervalEXT\n");
        exit(2);
    }
    glXSwapIntervalEXT(dpy, drawable, interval);
}

void glUniform1f(GLint location, GLfloat v0) {
    auto glUniform1f = (PFNGLUNIFORM1FPROC)glXGetProcAddress((unsigned char *)"glUniform1f");
    if (!glUniform1f) {
        printf("ERROR: Unable to cast glUniform1f\n");
        exit(2);
    }
    glUniform1f(location, v0);
}

void glGenFramebuffers(int n, uint *framebuffers) {
    auto glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)glXGetProcAddress((unsigned char *)"glGenFramebuffers");
    if (!glGenFramebuffers) {
        printf("ERROR: Unable to cast glGenFramebuffers\n");
        exit(2);
    }
    glGenFramebuffers(n, framebuffers);
}

void glDeleteFrameBuffers(int n, uint *framebuffers) {
    auto glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)glXGetProcAddress((unsigned char *)"glDeleteFramebuffers");
    if (!glDeleteFramebuffers) {
        printf("ERROR: Unable to cast glDeleteFramebuffers\n");
        exit(2);
    }
    glDeleteFramebuffers(n, framebuffers);
}

void glBindFramebuffer(GLenum target, uint framebuffer) {
    auto glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)glXGetProcAddress((unsigned char *)"glBindFramebuffer");
    if (!glBindFramebuffer) {
        printf("ERROR: Unable to cast glBindFramebuffer\n");
        exit(2);
    }
    glBindFramebuffer(target, framebuffer);
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, uint texture, int level) {
    auto glFramebufferTexture2D =
        (PFNGLFRAMEBUFFERTEXTURE2DPROC)glXGetProcAddress((unsigned char *)"glFramebufferTexture2D");
    if (!glFramebufferTexture2D) {
        printf("ERROR: Unable to cast glFramebufferTexture2D\n");
        exit(2);
    }
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void glGenRenderbuffers(int n, uint *renderbuffers) {
    auto glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)glXGetProcAddress((unsigned char *)"glGenRenderbuffers");
    if (!glGenRenderbuffers) {
        printf("ERROR: Unable to cast glGenRenderbuffer\n");
        exit(2);
    }
    glGenRenderbuffers(n, renderbuffers);
}

void glBindRenderBuffer(GLenum target, uint framebuffer) {
    auto glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)glXGetProcAddress((unsigned char *)"glBindRenderbuffer");
    if (!glBindRenderbuffer) {
        printf("ERROR: Unable to cast glBindRenderBuffer\n");
        exit(2);
    }
    glBindRenderbuffer(target, framebuffer);
}

void glRenderbufferStorage(GLenum target, GLenum internalformat, int width, int height) {
    auto glRenderbufferStorage =
        (PFNGLRENDERBUFFERSTORAGEPROC)glXGetProcAddress((unsigned char *)"glRenderbufferStorage");
    if (!glRenderbufferStorage) {
        printf("ERROR: Unable to cast glBindRenderbufferStorage\n");
        exit(2);
    }
    glRenderbufferStorage(target, internalformat, width, height);
}

void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, uint renderbuffer) {
    auto glFramebufferRenderbuffer =
        (PFNGLFRAMEBUFFERRENDERBUFFERPROC)glXGetProcAddress((unsigned char *)"glFramebufferRenderbuffer");
    if (!glFramebufferRenderbuffer) {
        printf("ERROR: Unable to cast glFramebufferRenderbuffer\n");
        exit(2);
    }
    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void glDrawBuffers(int n, const GLenum *bufs) {
    auto glDrawBuffers = (PFNGLDRAWBUFFERSARBPROC)glXGetProcAddress((unsigned char *)"glDrawBuffers");
    if (!glDrawBuffers) {
        printf("ERROR: Unable to cast glDrawBuffers\n");
        exit(2);
    }
    glDrawBuffers(n, bufs);
}
void glDeleteRenderbuffers(int n, uint *renderbuffers) {
    auto glDeleteRenderbuffers =
        (PFNGLDELETERENDERBUFFERSPROC)glXGetProcAddress((unsigned char *)"glDeleteRenderbuffers");
    if (!glDeleteRenderbuffers) {
        printf("ERROR: Unable to cast glDeleteRenderbuffers\n");
        exit(2);
    }
    glDeleteRenderbuffers(n, renderbuffers);
}
void glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {
    auto glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)glXGetProcAddress((unsigned char *)"glBlendFuncSeparate");
    if (!glBlendFuncSeparate) {
        printf("ERROR: Unable to cast glBlendFuncSeparate\n");
        exit(2);
    }
    glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

void InitializeOpenGL(OpenGL *openGL, Display *display, Window win, int screenWidth, int screenHeight, float screenNear,
                      float screenDepth, bool vsync) {
    openGL->screenWidth = screenWidth;
    openGL->screenHeight = screenWidth;
    openGL->display = display;
    openGL->hwnd = win;

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    GLXDrawable drawable = glXGetCurrentDrawable();
    if (vsync) {
        glXSwapIntervalEXT(openGL->display, drawable, 1);
    } else {
        glXSwapIntervalEXT(openGL->display, drawable, 0);
    }
    BuildIdentityMatrix(openGL->worldMatrix);

    float fov = PI / 4.0f;
    float screenAspect = (float)screenWidth / (float)screenHeight;

    BuildPerspectiveFovMatrix(openGL->projectionMatrix, fov, screenAspect, screenNear, screenDepth);
    BuildOrthoMatrix(openGL->orthoMatrix, (float)screenWidth, (float)screenHeight, screenNear, screenDepth);
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
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
}
void DisableAlphaBlending() {
    // Disable alpha blending.
    glDisable(GL_BLEND);
}

void SetBackBufferRenderTarget(OpenGL *openGL) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

bool MoveMatrix4fvToShader(const char *variableName, uint program, float *matrix, int count) {
    int location = glGetUniformLocation(program, variableName);
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, count, false, matrix);
    return true;
}
bool MoveMatrix4fvToShader(const char *variableName, uint program, float *matrix) {
    int location = glGetUniformLocation(program, variableName);
    if (location == -1) {
        return false;
    }
    glUniformMatrix4fv(location, 1, false, matrix);
    return true;
}
bool Move1fToShader(const char *variableName, uint program, float value) {
    int location = glGetUniformLocation(program, variableName);
    if (location == -1) {
        return false;
    }
    glUniform1f(location, value);
    return true;
}

bool Move1iToShader(const char *variableName, uint program, int value) {
    int location = glGetUniformLocation(program, variableName);
    if (location == -1) {
        return false;
    }
    glUniform1i(location, value);
    return true;
}
uint CreateAndCompileShader(const char *fileName, GLenum shaderType) {
    int status;
    const char *vertexShaderBuffer;
    vertexShaderBuffer = ReadFile(fileName);
    if (!vertexShaderBuffer) {
        return false;
    }
    uint shader = glCreateShader(shaderType);
    glShaderSource(shader, vertexShaderBuffer);
    delete[] vertexShaderBuffer;
    vertexShaderBuffer = 0;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != 1) {
        OutputShaderErrorMessage(shader, fileName);
        return -1;
    }
    return shader;
}
bool Move3fvToShader(const char *variableName, uint program, float *value, int count) {
    int location = glGetUniformLocation(program, variableName);
    if (location == -1) {
        return false;
    }
    glUniform3fv(location, count, value);
    return true;
}
bool Move4fvToShader(const char *variableName, uint program, float *value, int count) {
    int location = glGetUniformLocation(program, variableName);
    if (location == -1) {
        return false;
    }
    glUniform4fv(location, count, value);
    return true;
}
