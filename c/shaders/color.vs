#version 400

// Input variables
in vec3 inputPosition;
in vec3 inputColor;


// Output variables
out vec3 color;


// Uniform variables
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(){
  gl_Position = vec4(inputPosition, 1.0f) * worldMatrix;
  gl_Position = gl_Position * viewMatrix;
  gl_Position = gl_Position * projectionMatrix;

  color = inputColor;
}
