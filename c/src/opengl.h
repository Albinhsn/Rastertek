#ifndef OPENGLCLASS_H
#define OPENGLCLASS_H

#include "GL/gl.h"
#include "GL/glx.h"

// TYPE DEFINITIONS
typedef GLuint(APIENTRY *PFNGLCREATESHADERPROC)(GLenum type);
typedef void(APIENTRY *PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef void(APIENTRY *PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
typedef void(APIENTRY *PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, char *infoLog);
typedef GLuint(APIENTRY *PFNGLCREATEPROGRAMPROC)(void);
typedef void(APIENTRY *PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef void(APIENTRY *PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const char *name);
typedef void(APIENTRY *PFNGLLINKPROGRAMPROC)(GLuint program);
typedef void(APIENTRY *PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint *params);
typedef void(APIENTRY *PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei *length, char *infoLog);
typedef void(APIENTRY *PFNGLDETACHSHADERPROC)(GLuint program, GLuint shader);
typedef void(APIENTRY *PFNGLDELETESHADERPROC)(GLuint shader);
typedef void(APIENTRY *PFNGLDELETEPROGRAMPROC)(GLuint program);
typedef void(APIENTRY *PFNGLUSEPROGRAMPROC)(GLuint program);
typedef GLint(APIENTRY *PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const char *name);
typedef void(APIENTRY *PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose,
                                                  const GLfloat *value);
typedef void(APIENTRY *PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
typedef void(APIENTRY *PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void(APIENTRY *PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);
typedef void(APIENTRY *PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void(APIENTRY *PFNGLBUFFERDATAPROC)(GLenum target, ptrdiff_t size, const GLvoid *data, GLenum usage);
typedef void(APIENTRY *PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void(APIENTRY *PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized,
                                                     GLsizei stride, const GLvoid *pointer);
typedef void(APIENTRY *PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void(APIENTRY *PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint *buffers);
typedef void(APIENTRY *PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint *arrays);
typedef void(APIENTRY *PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
typedef void(APIENTRY *PFNGLACTIVETEXTUREPROC)(GLenum texture);
typedef void(APIENTRY *PFNGLGENERATEMIPMAPPROC)(GLenum target);
typedef void(APIENTRY *PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat *value);
typedef void(APIENTRY *PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat *value);
typedef void(APIENTRY *PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat *value);
typedef void *(APIENTRY *PFNGLMAPBUFFERPROC)(GLenum target, GLenum access);
typedef GLboolean(APIENTRY *PFNGLUNMAPBUFFERPROC)(GLenum target);
typedef void(APIENTRY *PFNGLXSWAPINTERVALEXTPROC)(Display *dpy, GLXDrawable drawable, int interval);
typedef void(APIENTRY *PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
typedef void(APIENTRY *PFNGLGENFRAMEBUFFERSPROC)(GLsizei n, GLuint *framebuffers);
typedef void(APIENTRY *PFNGLDELETEFRAMEBUFFERSPROC)(GLsizei n, const GLuint *framebuffers);
typedef void(APIENTRY *PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
typedef void(APIENTRY *PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum target, GLenum attachment, GLenum textarget,
                                                      GLuint texture, GLint level);
typedef void(APIENTRY *PFNGLGENRENDERBUFFERSPROC)(GLsizei n, GLuint *renderbuffers);
typedef void(APIENTRY *PFNGLBINDRENDERBUFFERPROC)(GLenum target, GLuint renderbuffer);
typedef void(APIENTRY *PFNGLRENDERBUFFERSTORAGEPROC)(GLenum target, GLenum internalformat, GLsizei width,
                                                     GLsizei height);
typedef void(APIENTRY *PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget,
                                                         GLuint renderbuffer);
typedef void(APIENTRY *PFNGLDRAWBUFFERSARBPROC)(GLsizei n, const GLenum *bufs);
typedef void(APIENTRY *PFNGLDELETERENDERBUFFERSPROC)(GLsizei n, const GLuint *renderbuffers);
typedef void(APIENTRYP PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha,
                                                   GLenum dfactorAlpha);
struct OpenGL {
    Display *display;
    Window hwnd;
    float worldMatrix[16];
    float projectionMatrix[16];
    float orthoMatrix[16];
    float screenWidth, screenHeight;
};

bool InitializeOpenGL(OpenGL *openGL, Display *display, Window win, int screenWidth, int screenHeight, float screenNear,
                      float screenDepth, bool vsync);
void ShutdownOpenGL();

void BeginScene(float, float, float, float);
void EndScene(Display *, Window hwnd);

void TurnZBufferOn();
void TurnZBufferOff();

void EnableAlphaBlending();
void DisableAlphaBlending();

void SetBackBufferRenderTarget();
void ResetViewport();

void EnableClipping();
void DisableClipping();
bool LoadExtensionList();
uint CreateShader(uint shaderType);
void glShaderSource(uint shader, const char *buffer);
void glCompileShader(uint shader);
void glGetShaderiv(uint shader, uint pname, int *status);
char *GetShaderInfoLog(uint shaderId);
uint CreateProgram();
void AttachShaders(uint shaderProgram, uint vShader, uint fShader);
void BindAttribLocation(uint shaderProgram, int location, const char *variableName);
void LinkProgram(uint shaderProgram);
void GetProgramiv(uint shaderProgram, uint pname, int *status);
char *GetProgramInfoLog(uint programId);
void DetachShader(uint program, uint shader);
void DeleteShader(uint shader);
void DeleteProgram(uint program);
void UseProgram(uint program);
int GetUniformLocation(uint program, char *variableName);
void glUniformMatrix4fv(int location, int count, bool transpose, const float *matrix);
void glGenVertexArrays(int n, uint *buffer);
void glBindVertexArray(uint buffer);
void glGenBuffers(int n, uint *buffer);
void glBindBuffer(GLenum target, GLuint buffer);
void glBufferData(GLenum target, size_t size, void *data, GLenum usage);
void glEnableVertexAttribArray(uint index);
void glVertexAttribPointer(uint index, int size, GLenum type, bool normalized, size_t stride, void *pointer);
void glDisableVertexAttribArray(uint index);
void glDeleteBuffers(int n, uint *buffers);
void glDeleteVertexArrays(int n, uint *arrays);
void glUniform1i(int location, int v0);
void glGenerateMipmap(GLenum target);
void glUniform2fv(int location, int count, float *value);
void glUniform3fv(int location, int count, float *value);
void glUniform4fv(int location, int count, float *value);
void *glMapBuffer(GLenum target, GLenum access);
void glUnmapBuffer(GLenum target);
void glXSwapIntervalEXT(Display *dpy, GLXDrawable drawable, int interval);
void glUniform1f(GLint location, GLfloat v0);
void glGenFramebuffers(int n, uint *framebuffers);
void glDeleteFrameBuffers(int n, uint *framebuffers);
void glBindFramebuffer(GLenum target, uint framebuffer);
void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, uint texture, int level);
void glGenRenderbuffers(int n, uint *renderbuffers);
void glBindRenderBuffer(GLenum target, uint framebuffer);
void glRenderbufferStorage(GLenum target, GLenum internalformat, int width, int height);
void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, uint renderbuffer);
void glDrawBuffers(int n, const GLenum *bufs);
void glDeleteRenderbuffers(int n, uint *renderbuffers);
void glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);

#endif
