#version 400

in vec3 inputPosition;
in vec2 inputTexCoord;

out vec2 texCoord;

out vec4 reflectionPosition;
out vec4 refractionPosition;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 reflectionMatrix;

void main(void)
{
  mat4 reflectProjectWorld;
  mat4 viewProjectWorld;

  gl_Position = vec4(inputPosition, 1.0f) * worldMatrix;
  gl_Position = gl_Position * viewMatrix;
  gl_Position = gl_Position * projectionMatrix;

  texCoord = inputTexCoord;

  reflectProjectWorld = reflectionMatrix * projectionMatrix;
  reflectProjectWorld = worldMatrix * reflectProjectWorld;

  reflectionPosition = vec4(inputPosition, 1.0f) * reflectProjectWorld;

  viewProjectWorld = viewMatrix * projectionMatrix;
  viewProjectWorld = worldMatrix * viewProjectWorld;

  refractionPosition = vec4(inputPosition, 1.0f) * viewProjectWorld;
}
