#include "spriteclass.h"

SpriteClass::SpriteClass() {
  m_OpenGLPtr = 0;
  m_Textures = 0;
}

SpriteClass::SpriteClass(const SpriteClass &other) {}
SpriteClass::~SpriteClass() {}

bool SpriteClass::Initialize(OpenGLClass *OpenGL, int screenWidth,
                             int screenHeight, int renderX, int renderY,
                             char *spriteFilename) {
  bool result;

  m_OpenGLPtr = OpenGL;

  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;

  m_renderX = renderX;
  m_renderY = renderY;

  m_frameTime = 0;

  result = InitializeBuffers();
  if (!result) {
    return false;
  }

  result = LoadTextures(spriteFilename);
  if (!result) {
    return false;
  }

  return true;
}

void SpriteClass::Shutdown() {
  ReleaseTextures();
  ShutdownBuffers();

  m_OpenGLPtr = 0;
}

void SpriteClass::Render() {
  UpdateBuffers();

  SetTexture();

  RenderBuffers();
}

void SpriteClass::Update(int frameTime) {
  m_frameTime += frameTime;

  if (m_frameTime >= m_cycleTime) {
    m_frameTime -= m_cycleTime;

    m_currentTexture++;

    if (m_currentTexture == m_textureCount) {
      m_currentTexture = 0;
    }
  }
}

bool SpriteClass::InitializeBuffers() {
  VertexType *vertices;
  unsigned int *indices;
  int i;

  m_prevPosX = -1;
  m_prevPosY = -1;

  m_vertexCount = 6;

  vertices = new VertexType[m_vertexCount];

  indices = new unsigned int[m_indexCount];

  memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

  for (i = 0; i < m_indexCount; i++) {
    indices[i] = i;
  }

  // Allocate an OpenGL vertex array object.
  m_OpenGLPtr->glGenVertexArrays(1, &m_vertexArrayId);

  // Bind the vertex array object to store all the buffers and vertex attributes
  // we create here.
  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  // Generate an ID for the vertex buffer.
  m_OpenGLPtr->glGenBuffers(1, &m_vertexBufferId);

  // Bind the vertex buffer and load the vertex data into the vertex buffer. Set
  // gpu hint to dynamic since it will change once in a while.
  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
  m_OpenGLPtr->glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(VertexType),
                            vertices, GL_DYNAMIC_DRAW);

  // Enable the two vertex array attributes.
  m_OpenGLPtr->glEnableVertexAttribArray(0); // Vertex position.
  m_OpenGLPtr->glEnableVertexAttribArray(1); // Texture coordinates.

  // Specify the location and format of the position portion of the vertex
  // buffer.
  m_OpenGLPtr->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType),
                                     0);

  // Specify the location and format of the texture coordinate portion of the
  // vertex buffer.
  m_OpenGLPtr->glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType),
                                     (unsigned char *)NULL +
                                         (3 * sizeof(float)));

  // Generate an ID for the index buffer.
  m_OpenGLPtr->glGenBuffers(1, &m_indexBufferId);

  // Bind the index buffer and load the index data into it.  Leave it static
  // since the indices won't change, only the vertices.
  m_OpenGLPtr->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
  m_OpenGLPtr->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                            m_indexCount * sizeof(unsigned int), indices,
                            GL_STATIC_DRAW);

  // Now that the buffers have been loaded we can release the array data.
  delete[] vertices;
  vertices = 0;

  delete[] indices;
  indices = 0;

  return true;
}

void SpriteClass::ShutdownBuffers() {
  // Disable the two vertex array attributes.
  m_OpenGLPtr->glDisableVertexAttribArray(0);
  m_OpenGLPtr->glDisableVertexAttribArray(1);

  // Release the vertex buffer.
  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_OpenGLPtr->glDeleteBuffers(1, &m_vertexBufferId);

  // Release the index buffer.
  m_OpenGLPtr->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_OpenGLPtr->glDeleteBuffers(1, &m_indexBufferId);

  // Release the vertex array object.
  m_OpenGLPtr->glBindVertexArray(0);
  m_OpenGLPtr->glDeleteVertexArrays(1, &m_vertexArrayId);

  return;
}

bool SpriteClass::UpdateBuffers() {
  VertexType *vertices;
  void *dataPtr;
  float left, right, top, bottom;

  // If the position we are rendering this sprite to hasn't changed then don't
  // update the vertex buffer.
  if ((m_prevPosX == m_renderX) && (m_prevPosY == m_renderY)) {
    return true;
  }

  // If the rendering location has changed then store the new position and
  // update the vertex buffer.
  m_prevPosX = m_renderX;
  m_prevPosY = m_renderY;

  // Create the vertex array.
  vertices = new VertexType[m_vertexCount];

  // Calculate the screen coordinates of the left side of the sprite.
  left = (float)((m_screenWidth / 2) * -1) + (float)m_renderX;

  // Calculate the screen coordinates of the right side of the sprite.
  right = left + (float)m_bitmapWidth;

  // Calculate the screen coordinates of the top of the sprite.
  top = (float)(m_screenHeight / 2) - (float)m_renderY;

  // Calculate the screen coordinates of the bottom of the sprite.
  bottom = top - (float)m_bitmapHeight;

  // Load the vertex array with data.

  // First triangle.
  vertices[0].x = left; // Top left.
  vertices[0].y = top;
  vertices[0].z = 0.0f;
  vertices[0].tu = 0.0f;
  vertices[0].tv = 1.0f;

  vertices[1].x = right; // Bottom right.
  vertices[1].y = bottom;
  vertices[1].z = 0.0f;
  vertices[1].tu = 1.0f;
  vertices[1].tv = 0.0f;

  vertices[2].x = left; // Bottom left.
  vertices[2].y = bottom;
  vertices[2].z = 0.0f;
  vertices[2].tu = 0.0f;
  vertices[2].tv = 0.0f;

  // Second triangle.
  vertices[3].x = left; // Top left.
  vertices[3].y = top;
  vertices[3].z = 0.0f;
  vertices[3].tu = 0.0f;
  vertices[3].tv = 1.0f;

  vertices[4].x = right; // Top right.
  vertices[4].y = top;
  vertices[4].z = 0.0f;
  vertices[4].tu = 1.0f;
  vertices[4].tv = 1.0f;

  vertices[5].x = right; // Bottom right.
  vertices[5].y = bottom;
  vertices[5].z = 0.0f;
  vertices[5].tu = 1.0f;
  vertices[5].tv = 0.0f;

  // Bind the vertex buffer.
  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);

  // Get a pointer to the buffer's actual location in memory.
  dataPtr = m_OpenGLPtr->glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

  // Copy the vertex data into memory.
  memcpy(dataPtr, vertices, m_vertexCount * sizeof(VertexType));

  // Unlock the vertex buffer.
  m_OpenGLPtr->glUnmapBuffer(GL_ARRAY_BUFFER);

  // Now that the vertex buffer has been loaded we can release the array data.
  delete[] vertices;
  vertices = 0;

  return true;
}

void SpriteClass::RenderBuffers() {
  // Bind the vertex array object that stored all the information about the
  // vertex and index buffers.
  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  // Render the vertex buffer using the index buffer.
  glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

  return;
}


bool SpriteClass::LoadTextures(char* filename)
{
    char textureFilename[128];
    ifstream fin;
    int i, j;
    char input;
    bool result;


    // Open the sprite info data file.
    fin.open(filename);
    if(fin.fail())
    {
        return false;
    }

    // Read in the number of textures.
    fin >> m_textureCount;

    // Create and initialize the texture array with the texture count from the file.
    m_Textures = new TextureClass[m_textureCount];

    // Read to start of next line.
    fin.get(input);

    // Read in each texture file name.
    for(i=0; i<m_textureCount; i++)
    {
        j=0;
        fin.get(input);
        while(input != '\n')
        {
            textureFilename[j] = input;
            j++;
            fin.get(input);
        }
        textureFilename[j] = '\0';

        // Once you have the filename then load the texture in the texture array.
        result = m_Textures[i].Initialize(m_OpenGLPtr, textureFilename, 0, false);
        if(!result)
        {
            return false;
        }
    }

    // Read in the cycle time.
    fin >> m_cycleTime;

    // Close the file.
    fin.close();

    // Get the dimensions of the first texture and use that as the dimensions of the 2D sprite images.
    m_bitmapWidth = m_Textures[0].GetWidth();
    m_bitmapHeight = m_Textures[0].GetHeight();

    // Set the starting texture in the cycle to be the first one in the list.
    m_currentTexture = 0;

    return true;
}

void SpriteClass::ReleaseTextures()
{
    int i;


    // Release the texture objects.
    if(m_Textures)
    {
        for(i=0; i<m_textureCount; i++)
        {
            m_Textures[i].Shutdown();
        }

        delete [] m_Textures;
        m_Textures = 0;
    }

    return;
}

void SpriteClass::SetTexture()
{
    // Set the current texture in the sprite cycle.
    m_Textures[m_currentTexture].SetTexture(m_OpenGLPtr);

    return;
}

void SpriteClass::SetRenderLocation(int x, int y)
{
    m_renderX = x;
    m_renderY = y;
    return;
}


