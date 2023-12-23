#include "specmapshaderclass.h"

SpecMapShaderClass::SpecMapShaderClass() {}
SpecMapShaderClass::SpecMapShaderClass(const SpecMapShaderClass &other) {}
SpecMapShaderClass::~SpecMapShaderClass() {}

bool SpecMapShaderClass::Initialize(OpenGLClass *OpenGL) {
  char vsFilename[128];
  char psFilename[128];

  bool result;

  m_OpenGLPtr = OpenGL;

  strcpy(vsFilename, "./shaders/specmap.vs");
  strcpy(psFilename, "./shaders/specmap.ps");

  result = InitializeShader(vsFilename, psFilename);
  if (!result) {
    return false;
  }

  return true;
}

void SpecMapShaderClass::Shutdown() {
  ShutdownShader();

  m_OpenGLPtr = 0;
}

bool SpecMapShaderClass::InitializeShader(char *vsFilename, char *fsFilename) {
  const char *vertexShaderBuffer;
  const char *fragmentShaderBuffer;

  int status;

  vertexShaderBuffer = LoadShaderSourceFile(vsFilename);
  if (!vertexShaderBuffer) {
    printf("ERROR: failed to initialize vertexShader\n");
    return false;
  }

  fragmentShaderBuffer = LoadShaderSourceFile(fsFilename);
  if (!fragmentShaderBuffer) {
    printf("ERROR: failed to initialize fragmentShader\n");
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
    OutputShaderErrorMessage(m_fragmentShader, vsFilename);
    return false;
  }

  m_shaderProgram = m_OpenGLPtr->glCreateProgram();

  m_OpenGLPtr->glAttachShader(m_shaderProgram, m_vertexShader);
  m_OpenGLPtr->glAttachShader(m_shaderProgram, m_fragmentShader);

  m_OpenGLPtr->glBindAttribLocation(m_shaderProgram, 0, "inputPosition");
  m_OpenGLPtr->glBindAttribLocation(m_shaderProgram, 1, "inputTexCoord");
  m_OpenGLPtr->glBindAttribLocation(m_shaderProgram, 2, "inputNormal");
  m_OpenGLPtr->glBindAttribLocation(m_shaderProgram, 3, "inputTangent");
  m_OpenGLPtr->glBindAttribLocation(m_shaderProgram, 4, "inputBinormal");

  m_OpenGLPtr->glLinkProgram(m_shaderProgram);

  m_OpenGLPtr->glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);
  if (status != 1) {
    OutputLinkerErrorMessage(m_shaderProgram);
    return false;
  }

  return true;
}

void SpecMapShaderClass::ShutdownShader() {
  m_OpenGLPtr->glDetachShader(m_shaderProgram, m_vertexShader);
  m_OpenGLPtr->glDetachShader(m_shaderProgram, m_fragmentShader);

  m_OpenGLPtr->glDeleteShader(m_vertexShader);
  m_OpenGLPtr->glDeleteShader(m_fragmentShader);

  m_OpenGLPtr->glDeleteProgram(m_shaderProgram);

  return;
}

char *SpecMapShaderClass::LoadShaderSourceFile(char *filename) {
  FILE *filePtr;
  char *buffer;
  long fileSize, count;
  int error;

  // Open the shader file for reading in text modee.
  filePtr = fopen(filename, "r");
  if (filePtr == NULL) {
    printf("ERROR: tried to open unknown file '%s'\n", filename);
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

void SpecMapShaderClass::OutputShaderErrorMessage(unsigned int shaderId,
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

void SpecMapShaderClass::OutputLinkerErrorMessage(unsigned int programId) {
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

bool SpecMapShaderClass::SetShaderParameters(
    float *worldMatrix, float *viewMatrix, float *projectionMatrix,
    float *lightDirection, float *diffuseLightColor, float *cameraPosition,
    float *specularColor, float specularPower) {

    float tpWorldMatrix[16], tpViewMatrix[16], tpProjectionMatrix[16];
    int location;


    m_OpenGLPtr->MatrixTranspose(tpWorldMatrix, worldMatrix);
    m_OpenGLPtr->MatrixTranspose(tpViewMatrix, viewMatrix);
    m_OpenGLPtr->MatrixTranspose(tpProjectionMatrix, projectionMatrix);
    
    // Install the shader program as part of the current rendering state.
    m_OpenGLPtr->glUseProgram(m_shaderProgram);

    // Set the world matrix in the vertex shader.
    location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "worldMatrix");
    if(location == -1)
    {
        return false;
    }
    m_OpenGLPtr ->glUniformMatrix4fv(location, 1, false, tpWorldMatrix);

    // Set the view matrix in the vertex shader.
    location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "viewMatrix");
    if(location == -1)
    {
        return false;
    }
    m_OpenGLPtr->glUniformMatrix4fv(location, 1, false, tpViewMatrix);

    // Set the projection matrix in the vertex shader.
    location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "projectionMatrix");
    if(location == -1)
    {
        return false;
    }
    m_OpenGLPtr->glUniformMatrix4fv(location, 1, false, tpProjectionMatrix);

    // Set the camera position in the vertex shader.
    location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "cameraPosition");
    if(location == -1)
    {
        return false;
    }
    m_OpenGLPtr->glUniform3fv(location, 1, cameraPosition);

    // Set the first texture in the pixel shader to use the data from the first texture unit.
    location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "shaderTexture1");
    if(location == -1)
    {
        return false;
    }
    m_OpenGLPtr->glUniform1i(location, 0);

    // Set the second texture in the pixel shader to use the data from the second texture unit.
    location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "shaderTexture2");
    if(location == -1)
    {
        return false;
    }
    m_OpenGLPtr->glUniform1i(location, 1);
	
    // Set the third texture in the pixel shader to use the data from the third texture unit.
    location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "shaderTexture3");
    if(location == -1)
    {
        return false;
    }
    m_OpenGLPtr->glUniform1i(location, 2);

    // Set the light direction in the pixel shader.
    location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "lightDirection");
    if(location == -1)
    {
        return false;
    }
    m_OpenGLPtr->glUniform3fv(location, 1, lightDirection);

    // Set the light color in the pixel shader.
    location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "diffuseLightColor");
    if(location == -1)
    {
        return false;
    }
    m_OpenGLPtr->glUniform4fv(location, 1, diffuseLightColor);

    // Set the specular light power in the pixel shader.
    location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "specularPower");
    if(location == -1)
    {
        return false;
    }
    m_OpenGLPtr->glUniform1f(location, specularPower);

    // Set the specular light color in the pixel shader.
    location = m_OpenGLPtr->glGetUniformLocation(m_shaderProgram, "specularColor");
    if(location == -1)
    {
        return false;
    }
    m_OpenGLPtr->glUniform4fv(location, 1, specularColor);

    return true;
}
