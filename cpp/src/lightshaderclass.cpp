#include "lightshaderclass.h"

LightShaderClass::LightShaderClass() { m_OpenGLPtr = 0; }

LightShaderClass::LightShaderClass(const LightShaderClass &other) {}

LightShaderClass::~LightShaderClass() {}

bool LightShaderClass::Initialize(OpenGLClass *OpenGL) {
  char vsFilename[128];
  char psFilename[128];
  bool result;

  m_OpenGLPtr = OpenGL;

  strcpy(vsFilename, "./shaders/light.vs");
  strcpy(psFilename, "./shaders/light.ps");

  result = InitializeShader(vsFilename, psFilename);
  if (!result) {
    printf("ERROR: Failed to initialize shaders\n");
    return false;
  }
  return true;
}
void LightShaderClass::Shutdown() {
  ShutdownShader();

  m_OpenGLPtr = 0;
}

bool LightShaderClass::InitializeShader(char *vsFilename, char *fsFilename) {
  const char *vertexShaderBuffer;
  const char *fragmentShaderBuffer;
  int status;

  vertexShaderBuffer = LoadShaderSourceFile(vsFilename);
  if (!vertexShaderBuffer) {
    printf("Failed to initialize vertex shader\n");
    return false;
  }

  fragmentShaderBuffer = LoadShaderSourceFile(fsFilename);
  if (!fragmentShaderBuffer) {
    printf("Failed to initialize fragment shader\n");
    return false;
  }

  m_vertexShader = m_OpenGLPtr->glCreateShader(GL_VERTEX_SHADER);
  m_fragmentShader = m_OpenGLPtr->glCreateShader(GL_FRAGMENT_SHADER);

  m_OpenGLPtr->glShaderSource(m_vertexShader, 1, &vertexShaderBuffer, NULL);
  m_OpenGLPtr->glShaderSource(m_fragmentShader, 1, &fragmentShaderBuffer, NULL);

  delete[] vertexShaderBuffer;
  vertexShaderBuffer = 0;

  delete[] fragmentShaderBuffer;
  fragmentShaderBuffer = 0;

  m_OpenGLPtr->glCompileShader(m_vertexShader);
  m_OpenGLPtr->glCompileShader(m_fragmentShader);

  m_OpenGLPtr->glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &status);
  if (status != 1) {
    OutputShaderErrorMessage(m_vertexShader, vsFilename);
    return false;
  }

  m_OpenGLPtr->glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &status);
  if (status != 1) {
    OutputShaderErrorMessage(m_fragmentShader, fsFilename);
    return false;
  }

  m_shaderProgram = m_OpenGLPtr->glCreateProgram();

  m_OpenGLPtr->glAttachShader(m_shaderProgram, m_vertexShader);
  m_OpenGLPtr->glAttachShader(m_shaderProgram, m_fragmentShader);

  m_OpenGLPtr->glBindAttribLocation(m_shaderProgram, 0, "inputPosition");
  m_OpenGLPtr->glBindAttribLocation(m_shaderProgram, 1, "inputTexCoord");
  m_OpenGLPtr->glBindAttribLocation(m_shaderProgram, 2, "inputNormal");

  m_OpenGLPtr->glLinkProgram(m_shaderProgram);

  m_OpenGLPtr->glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);
  if (status != 1) {
    OutputLinkerErrorMessage(m_shaderProgram);
    return false;
  }
  return true;
}

void LightShaderClass::ShutdownShader() {
  m_OpenGLPtr->glDetachShader(m_shaderProgram, m_vertexShader);
  m_OpenGLPtr->glDetachShader(m_shaderProgram, m_fragmentShader);

  m_OpenGLPtr->glDeleteShader(m_vertexShader);
  m_OpenGLPtr->glDeleteShader(m_fragmentShader);

  m_OpenGLPtr->glDeleteProgram(m_shaderProgram);
}

char *LightShaderClass::LoadShaderSourceFile(char *filename) {
  FILE *filePtr;
  char *buffer;
  long fileSize, count;
  int error;

  // Open the shader file for reading in text modee.
  filePtr = fopen(filename, "r");
  if (filePtr == NULL) {
    return 0;
  }

  // Go to the end of the file and get the size of the file.
  fseek(filePtr, 0, SEEK_END);
  fileSize = ftell(filePtr);

  // Initialize the buffer to read the shader source file into, adding 1 for an
  // extra null terminator.
  buffer = new char[fileSize + 1];

  // Return the file pointer back to the beginning of the file.
  fseek(filePtr, 0, SEEK_SET);

  // Read the shader text file into the buffer.
  count = fread(buffer, 1, fileSize, filePtr);
  if (count != fileSize) {
    return 0;
  }

  // Close the file.
  error = fclose(filePtr);
  if (error != 0) {
    return 0;
  }

  // Null terminate the buffer.
  buffer[fileSize] = '\0';

  return buffer;
}

void LightShaderClass::OutputShaderErrorMessage(unsigned int shaderId,
                                                char *shaderFilename) {
  long count;
  int logSize, error;

  char *infoLog;
  FILE *filePtr;

  // Get the size of the string containing the information log for the failed
  // shader compilation message.
  m_OpenGLPtr->glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

  // Increment the size by one to handle also the null terminator.
  logSize++;

  // Create a char buffer to hold the info log.
  infoLog = new char[logSize];

  // Now retrieve the info log.
  m_OpenGLPtr->glGetShaderInfoLog(shaderId, logSize, NULL, infoLog);

  // Open a text file to write the error message to.
  filePtr = fopen("shader-error.txt", "w");
  if (filePtr == NULL) {
    cout << "Error opening shader error message output file." << endl;
    return;
  }

  // Write out the error message.
  count = fwrite(infoLog, sizeof(char), logSize, filePtr);
  if (count != logSize) {
    cout << "Error writing shader error message output file." << endl;
    return;
  }

  // Close the file.
  error = fclose(filePtr);
  if (error != 0) {
    cout << "Error closing shader error message output file." << endl;
    return;
  }

  // Notify the user to check the text file for compile errors.
  cout << "Error compiling shader.  Check shader-error.txt for error message.  "
          "Shader filename: "
       << shaderFilename << endl;

  return;
}

void LightShaderClass::OutputLinkerErrorMessage(unsigned int programId) {
  long count;
  FILE *filePtr;
  int logSize, error;
  char *infoLog;

  // Get the size of the string containing the information log for the failed
  // shader compilation message.
  m_OpenGLPtr->glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);

  // Increment the size by one to handle also the null terminator.
  logSize++;

  // Create a char buffer to hold the info log.
  infoLog = new char[logSize];

  // Now retrieve the info log.
  m_OpenGLPtr->glGetProgramInfoLog(programId, logSize, NULL, infoLog);

  // Open a file to write the error message to.
  filePtr = fopen("linker-error.txt", "w");
  if (filePtr == NULL) {
    cout << "Error opening linker error message output file." << endl;
    return;
  }

  // Write out the error message.
  count = fwrite(infoLog, sizeof(char), logSize, filePtr);
  if (count != logSize) {
    cout << "Error writing linker error message output file." << endl;
    return;
  }

  // Close the file.
  error = fclose(filePtr);
  if (error != 0) {
    cout << "Error closing linker error message output file." << endl;
    return;
  }

  // Pop a message up on the screen to notify the user to check the text file
  // for linker errors.
  cout << "Error linking shader program.  Check linker-error.txt for message."
       << endl;

  return;
}

bool LightShaderClass::SetShaderParameters(
    float *worldMatrix, float *viewMatrix, float *projectionMatrix,
    float *lightDirection, float *diffuseLightColor, float *ambientLight) {
  float tpWorldMatrix[16], tpViewMatrix[16], tpProjectionMatrix[16];
  int location;

  m_OpenGLPtr->MatrixTranspose(tpWorldMatrix, worldMatrix);
  m_OpenGLPtr->MatrixTranspose(tpViewMatrix, viewMatrix);
  m_OpenGLPtr->MatrixTranspose(tpProjectionMatrix, projectionMatrix);

  m_OpenGLPtr->glUseProgram(m_shaderProgram);

  location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "worldMatrix");
  if (location == -1) {
    return false;
  }
  m_OpenGLPtr->glUniformMatrix4fv(location, 1, false, tpWorldMatrix);

  location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "viewMatrix");
  if (location == -1) {
    return false;
  }
  m_OpenGLPtr->glUniformMatrix4fv(location, 1, false, tpViewMatrix);

  location =
      m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "projectionMatrix");
  if (location == -1) {
    return false;
  }
  m_OpenGLPtr->glUniformMatrix4fv(location, 1, false, tpProjectionMatrix);

  location =
      m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "shaderTexture");
  if (location == -1) {
    return false;
  }

  m_OpenGLPtr->glUniform1i(location, 0);

  location =
      m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "lightDirection");
  if (location == -1) {
    return false;
  }
  m_OpenGLPtr->glUniform3fv(location, 1, lightDirection);

  location =
      m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "diffuseLightColor");
  if (location == -1) {
    return false;
  }
  m_OpenGLPtr->glUniform4fv(location, 1, diffuseLightColor);

  location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "ambientLight");
  if (location == -1) {
    return false;
  }
  m_OpenGLPtr->glUniform4fv(location, 1, ambientLight);
  return true;
}
