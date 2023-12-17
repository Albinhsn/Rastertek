#include "textureclass.h"

TextureClass::TextureClass() { m_loaded = false; }

TextureClass::TextureClass(const TextureClass &other) {}
TextureClass::~TextureClass() {}

bool TextureClass::Initialize(OpenGLClass *OpenGL, char *filename,
                              unsigned int textureUnit, bool wrap) {
  bool result;

  m_textureUnit = textureUnit;
  result = LoadTarga32Bit(OpenGL, filename, wrap);
  if (!result) {
    printf("ERROR: failed to load targa32bit\n");
    return false;
  }

  m_loaded = true;
  return true;
}

void TextureClass::Shutdown() {
  if (m_loaded) {
    glDeleteTextures(1, &m_textureId);
    m_loaded = false;
  }

  return;
}

bool TextureClass::LoadTarga32Bit(OpenGLClass *OpenGL, char *filename,
                                  bool wrap) {

  TargaHeader targaFileHeader;
  FILE *filePtr;
  int bpp, error, index, i, j;
  unsigned long count, imageSize;
  unsigned char *targaData;
  unsigned char *targaImage;

  // Open the targa file for reading in binary.
  filePtr = fopen(filename, "rb");
  if (filePtr == NULL) {
    printf("ERROR: file doesn't exist %s\n", filename);
    return false;
  }

  // Read in the file header.
  count = fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);
  if (count != 1) {
    printf("ERROR: Failed to read into header\n");
    return false;
  }

  // Get the important information from the header.
  m_width = (int)targaFileHeader.width;
  m_height = (int)targaFileHeader.height;
  bpp = (int)targaFileHeader.bpp;

  // Check that it is 32 bit and not 24 bit.
  if (bpp != 32) {
    printf("ERROR: bpp isn't 32 but %d\n", bpp);
    return false;
  }

  // Calculate the size of the 32 bit image data.
  imageSize = m_width * m_height * 4;

  // Allocate memory for the targa image data.
  targaImage = new unsigned char[imageSize];

  // Read in the targa image data.
  count = fread(targaImage, 1, imageSize, filePtr);
  if (count != imageSize) {
    printf("ERROR: count read doesn't equal imageSize\n");
    return false;
  }

  error = fclose(filePtr);
  if (error != 0) {
    return false;
  }

  targaData = new unsigned char[imageSize];
  index = 0;
  for (j = 0; j < m_height; j++) {
    for (i = 0; i < m_width; i++) {
      targaData[index] = targaImage[index + 2];     // Red
      targaData[index + 1] = targaImage[index + 1]; // Green
      targaData[index + 2] = targaImage[index];     // Blue
      targaData[index + 3] = targaImage[index + 3]; // Blue

      index += 4;
    }
  }

  delete[] targaImage;
  targaImage = 0;

  OpenGL->glActiveTexture(GL_TEXTURE + m_textureUnit);

  glGenTextures(1, &m_textureId);
  glBindTexture(GL_TEXTURE_2D, m_textureId);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, targaData);

  if (wrap) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  } else {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);

  OpenGL->glGenerateMipmap(GL_TEXTURE_2D);

  delete[] targaData;
  targaData = 0;

  return true;
}

void TextureClass::SetTexture(OpenGLClass *OpenGL) {
  if (m_loaded) {
    OpenGL->glActiveTexture(GL_TEXTURE0 + m_textureUnit);

    glBindTexture(GL_TEXTURE_2D, m_textureId);
  }

  return;
}

int TextureClass::GetWidth() { return m_width; }

int TextureClass::GetHeight() { return m_height; }
