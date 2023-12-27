#include "particlesystemclass.h"

ParticleSystemClass::ParticleSystemClass() {
  m_OpenGLPtr = 0;
  m_Texture = 0;
  m_particleList = 0;
  m_vertices = 0;
}

ParticleSystemClass::ParticleSystemClass(const ParticleSystemClass &other) {}

ParticleSystemClass::~ParticleSystemClass() {}

bool ParticleSystemClass::Initialize(OpenGLClass *OpenGL,
                                     char *textureFilename) {
  bool result;

  // Store a pointer to the OpenGL object.
  m_OpenGLPtr = OpenGL;

  // Load the texture that is used for the particles.
  result = LoadTexture(textureFilename, false);
  if (!result) {
    return false;
  }

  // Initialize the particle system.
  InitializeParticleSystem();

  // Create the buffers that will be used to render the particles with.
  InitializeBuffers();

  return true;
}

void ParticleSystemClass::Shutdown() {
  // Release the buffers.
  ShutdownBuffers();

  // Release the particle system.
  ShutdownParticleSystem();

  // Release the texture used for the particles.
  ReleaseTexture();

  // Release the pointer to the OpenGL object.
  m_OpenGLPtr = 0;

  return;
}

void ParticleSystemClass::Frame(int frameTime) {
  KillParticles();

  EmitParticles(frameTime);
  UpdateParticles(frameTime);
  UpdateBuffers();
}

void ParticleSystemClass::Render() {
  m_Texture->SetTexture(m_OpenGLPtr);

  RenderBuffers();
}

bool ParticleSystemClass::LoadTexture(char *textureFilename, bool wrap) {
  bool result;

  m_Texture = new TextureClass;

  result = m_Texture->Initialize(m_OpenGLPtr, textureFilename, 0, wrap);
  if (!result) {
    return false;
  }

  return true;
}

void ParticleSystemClass::ReleaseTexture() {
  if (m_Texture) {
    m_Texture->Shutdown();
    delete m_Texture;
    m_Texture = 0;
  }
}

void ParticleSystemClass::InitializeParticleSystem() {
  int i;

  m_particleDeviationX = 0.5f;
  m_particleDeviationY = 0.1f;
  m_particleDeviationZ = 2.0f;

  m_particleVelocity = 1.0f;
  m_particleVelocityVariation = 0.2f;

  m_particleSize = 0.2f;

  m_particlesPerSecond = 100;

  m_maxParticles = 1000;

  m_particleList = new ParticleType[m_maxParticles];

  for (i = 0; i < m_maxParticles; i++) {
    m_particleList[i].active = false;
  }

  m_currentParticleCount = 0;
  m_accumulatedTime = 0;
}
void ParticleSystemClass::ShutdownParticleSystem() {
  if (m_particleList) {
    delete[] m_particleList;
    m_particleList = 0;
  }
}

void ParticleSystemClass::InitializeBuffers() {
  unsigned int *indices;
  int i;

  m_vertexCount = m_maxParticles * 6;

  m_indexCount = m_vertexCount;

  m_vertices = new VertexType[m_vertexCount];

  indices = new unsigned int[m_indexCount];

  memset(m_vertices, 0, (sizeof(VertexType) * m_vertexCount));

  for (i = 0; i < m_indexCount; i++) {
    indices[i] = i;
  }

  m_OpenGLPtr->glGenVertexArrays(1, &m_vertexArrayId);

  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  m_OpenGLPtr->glGenBuffers(1, &m_vertexBufferId);

  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
  m_OpenGLPtr->glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(VertexType),
                            m_vertices, GL_DYNAMIC_DRAW);

  m_OpenGLPtr->glEnableVertexAttribArray(0);
  m_OpenGLPtr->glEnableVertexAttribArray(1);
  m_OpenGLPtr->glEnableVertexAttribArray(2);

  m_OpenGLPtr->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType),
                                     0);
  m_OpenGLPtr->glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexType),
                                     (unsigned char *)NULL +
                                         (3 * sizeof(float)));

  // Specify the location and format of the color portion of the vertex buffer.
  m_OpenGLPtr->glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(VertexType),
                                     (unsigned char *)NULL +
                                         (5 * sizeof(float)));

  // Generate an ID for the index buffer.
  m_OpenGLPtr->glGenBuffers(1, &m_indexBufferId);

  // Bind the index buffer and load the index data into it.
  m_OpenGLPtr->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
  m_OpenGLPtr->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                            m_indexCount * sizeof(unsigned int), indices,
                            GL_STATIC_DRAW);

  // Now that the buffers have been loaded we can release the array data.
  delete[] indices;
  indices = 0;

  return;
}

void ParticleSystemClass::ShutdownBuffers() {
  // Disable the three vertex array attributes.
  m_OpenGLPtr->glDisableVertexAttribArray(0);
  m_OpenGLPtr->glDisableVertexAttribArray(1);
  m_OpenGLPtr->glDisableVertexAttribArray(2);

  // Release the vertex buffer.
  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_OpenGLPtr->glDeleteBuffers(1, &m_vertexBufferId);

  // Release the index buffer.
  m_OpenGLPtr->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_OpenGLPtr->glDeleteBuffers(1, &m_indexBufferId);

  // Release the vertex array object.
  m_OpenGLPtr->glBindVertexArray(0);
  m_OpenGLPtr->glDeleteVertexArrays(1, &m_vertexArrayId);

  // Release the vertices.
  if (m_vertices) {
    delete[] m_vertices;
    m_vertices = 0;
  }

  return;
}

void ParticleSystemClass::RenderBuffers() {
  // Bind the vertex array object that stored all the information about the
  // vertex and index buffers.
  m_OpenGLPtr->glBindVertexArray(m_vertexArrayId);

  // Render the vertex buffer using the index buffer.
  glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

  return;
}

void ParticleSystemClass::EmitParticles(int frameTime) {
  bool emitParticle, found;
  float positionX, positionY, positionZ, velocity, red, green, blue;
  int index, i, j;

  // Increment the frame time.
  m_accumulatedTime += frameTime;

  // Set emit particle to false for now.
  emitParticle = false;

  // Check if it is time to emit a new particle or not.
  if (m_accumulatedTime > (1000 / m_particlesPerSecond)) {
    m_accumulatedTime = 0;
    emitParticle = true;
  }

  // If there are particles to emit then emit one per frame.
  if ((emitParticle == true) &&
      (m_currentParticleCount < (m_maxParticles - 1))) {
    m_currentParticleCount++;

    // Now generate the randomized particle properties.
    positionX =
        (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviationX;
    positionY =
        (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviationY;
    positionZ =
        (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviationZ;

    velocity =
        m_particleVelocity + (((float)rand() - (float)rand()) / RAND_MAX) *
                                 m_particleVelocityVariation;

    red = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
    green = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
    blue = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;

    // Now since the particles need to be rendered from back to front for
    // blending we have to sort the particle array. We will sort using Z depth
    // so we need to find where in the list the particle should be inserted.
    index = 0;
    found = false;
    while (!found) {
      if ((m_particleList[index].active == false) ||
          (m_particleList[index].positionZ < positionZ)) {
        found = true;
      } else {
        index++;
      }
    }

    // Now that we know the location to insert into we need to copy the array
    // over by one position from the index to make room for the new particle.
    i = m_currentParticleCount;
    j = i - 1;

    while (i != index) {
      m_particleList[i].positionX = m_particleList[j].positionX;
      m_particleList[i].positionY = m_particleList[j].positionY;
      m_particleList[i].positionZ = m_particleList[j].positionZ;
      m_particleList[i].red = m_particleList[j].red;
      m_particleList[i].green = m_particleList[j].green;
      m_particleList[i].blue = m_particleList[j].blue;
      m_particleList[i].velocity = m_particleList[j].velocity;
      m_particleList[i].active = m_particleList[j].active;
      i--;
      j--;
    }

    // Now insert it into the particle array in the correct depth order.
    m_particleList[index].positionX = positionX;
    m_particleList[index].positionY = positionY;
    m_particleList[index].positionZ = positionZ;
    m_particleList[index].red = red;
    m_particleList[index].green = green;
    m_particleList[index].blue = blue;
    m_particleList[index].velocity = velocity;
    m_particleList[index].active = true;
  }

  return;
}

void ParticleSystemClass::UpdateParticles(int frameTime) {
  int i;

  // Each frame we update all the particles by making them move downwards using
  // their position, velocity, and the frame time.
  for (i = 0; i < m_currentParticleCount; i++) {
    m_particleList[i].positionY =
        m_particleList[i].positionY -
        (m_particleList[i].velocity * (float)frameTime * 0.001f);
  }

  return;
}

void ParticleSystemClass::KillParticles() {
  int i, j;

  // Kill all the particles that have gone below a certain height range.
  for (i = 0; i < m_maxParticles; i++) {
    if ((m_particleList[i].active == true) &&
        (m_particleList[i].positionY < -3.0f)) {
      m_particleList[i].active = false;
      m_currentParticleCount--;

      // Now shift all the live particles back up the array to erase the
      // destroyed particle and keep the array sorted correctly.
      for (j = i; j < m_maxParticles - 1; j++) {
        m_particleList[j].positionX = m_particleList[j + 1].positionX;
        m_particleList[j].positionY = m_particleList[j + 1].positionY;
        m_particleList[j].positionZ = m_particleList[j + 1].positionZ;
        m_particleList[j].red = m_particleList[j + 1].red;
        m_particleList[j].green = m_particleList[j + 1].green;
        m_particleList[j].blue = m_particleList[j + 1].blue;
        m_particleList[j].velocity = m_particleList[j + 1].velocity;
        m_particleList[j].active = m_particleList[j + 1].active;
      }
    }
  }

  return;
}

void ParticleSystemClass::UpdateBuffers() {
  void *dataPtr;
  int index, i;

  // Initialize vertex array to zeros at first.
  memset(m_vertices, 0, (sizeof(VertexType) * m_vertexCount));

  // Now build the vertex array from the particle list array.  Each particle is
  // a quad made out of two triangles.
  index = 0;

  for (i = 0; i < m_currentParticleCount; i++) {
    // Bottom left.
    m_vertices[index].x = m_particleList[i].positionX - m_particleSize;
    m_vertices[index].y = m_particleList[i].positionY - m_particleSize;
    m_vertices[index].z = m_particleList[i].positionZ;
    m_vertices[index].tu = 0.0f;
    m_vertices[index].tv = 0.0f;
    m_vertices[index].red = m_particleList[i].red;
    m_vertices[index].green = m_particleList[i].green;
    m_vertices[index].blue = m_particleList[i].blue;
    m_vertices[index].alpha = 1.0f;
    index++;

    // Top left.
    m_vertices[index].x = m_particleList[i].positionX - m_particleSize;
    m_vertices[index].y = m_particleList[i].positionY + m_particleSize;
    m_vertices[index].z = m_particleList[i].positionZ;
    m_vertices[index].tu = 0.0f;
    m_vertices[index].tv = 1.0f;
    m_vertices[index].red = m_particleList[i].red;
    m_vertices[index].green = m_particleList[i].green;
    m_vertices[index].blue = m_particleList[i].blue;
    m_vertices[index].alpha = 1.0f;
    index++;

    // Bottom right.
    m_vertices[index].x = m_particleList[i].positionX + m_particleSize;
    m_vertices[index].y = m_particleList[i].positionY - m_particleSize;
    m_vertices[index].z = m_particleList[i].positionZ;
    m_vertices[index].tu = 1.0f;
    m_vertices[index].tv = 0.0f;
    m_vertices[index].red = m_particleList[i].red;
    m_vertices[index].green = m_particleList[i].green;
    m_vertices[index].blue = m_particleList[i].blue;
    m_vertices[index].alpha = 1.0f;
    index++;

    // Bottom right.
    m_vertices[index].x = m_particleList[i].positionX + m_particleSize;
    m_vertices[index].y = m_particleList[i].positionY - m_particleSize;
    m_vertices[index].z = m_particleList[i].positionZ;
    m_vertices[index].tu = 1.0f;
    m_vertices[index].tv = 0.0f;
    m_vertices[index].red = m_particleList[i].red;
    m_vertices[index].green = m_particleList[i].green;
    m_vertices[index].blue = m_particleList[i].blue;
    m_vertices[index].alpha = 1.0f;
    index++;

    // Top left.
    m_vertices[index].x = m_particleList[i].positionX - m_particleSize;
    m_vertices[index].y = m_particleList[i].positionY + m_particleSize;
    m_vertices[index].z = m_particleList[i].positionZ;
    m_vertices[index].tu = 0.0f;
    m_vertices[index].tv = 1.0f;
    m_vertices[index].red = m_particleList[i].red;
    m_vertices[index].green = m_particleList[i].green;
    m_vertices[index].blue = m_particleList[i].blue;
    m_vertices[index].alpha = 1.0f;
    index++;

    // Top right.
    m_vertices[index].x = m_particleList[i].positionX + m_particleSize;
    m_vertices[index].y = m_particleList[i].positionY + m_particleSize;
    m_vertices[index].z = m_particleList[i].positionZ;
    m_vertices[index].tu = 1.0f;
    m_vertices[index].tv = 1.0f;
    m_vertices[index].red = m_particleList[i].red;
    m_vertices[index].green = m_particleList[i].green;
    m_vertices[index].blue = m_particleList[i].blue;
    m_vertices[index].alpha = 1.0f;
    index++;
  }

  // Bind the vertex buffer.
  m_OpenGLPtr->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);

  // Get a pointer to the buffer's actual location in memory.
  dataPtr = m_OpenGLPtr->glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

  // Copy the vertex data into memory.
  memcpy(dataPtr, m_vertices, (sizeof(VertexType) * m_vertexCount));

  // Unlock the vertex buffer.
  m_OpenGLPtr->glUnmapBuffer(GL_ARRAY_BUFFER);

  return;
}
