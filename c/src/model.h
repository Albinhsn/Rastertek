#ifndef MODEL_H
#define MODEL_H

#include "opengl.h"
#include "texture.h"

struct Model{
  OpenGL * openGL;
  unsigned int vertexArrayId, vertexBufferId, indexBufferId;
  Texture * texture;
};

#endif
