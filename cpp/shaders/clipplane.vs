#version 400

in vec3 inputPosition;
in vec2 inputTexCoord;

out vec2 texCoord;

out float gl_ClipDistance[1];

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec4 clipPlane;

void main(void)
{
  gl_Position = vec4(inputPosition, 1.0f) * worldMatrix; 
  gl_Position = gl_Position * viewMatrix;
  gl_Position = gl_Position * projectionMatrix;

  texCoord = inputTexCoord;

  gl_ClipDistance[0] = dot(vec4(inputPosition, 1.0f) * worldMatrix, clipPlane);
}
