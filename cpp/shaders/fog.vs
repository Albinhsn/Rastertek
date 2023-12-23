#version 400
in vec3 inputPosition;
in vec2 inputTexCoord;

out vec2 texCoord;
out float fogFactor;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec2 fogPosition;


void main(void)
{
    vec4 cameraPosition;
    float fogStart;
    float fogEnd;


    // Calculate the position of the vertex against the world, view, and projection matrices.
    gl_Position = vec4(inputPosition, 1.0f) * worldMatrix;
    gl_Position = gl_Position * viewMatrix;
    gl_Position = gl_Position * projectionMatrix;

    // Store the texture coordinates for the pixel shader.
    texCoord = inputTexCoord;

    // Calculate the camera position.
    cameraPosition = vec4(inputPosition, 1.0f) * worldMatrix;
    cameraPosition = cameraPosition * viewMatrix;

    // Calculate linear fog.
    fogStart = fogPosition.x;
    fogEnd = fogPosition.y;

    fogFactor = (fogEnd - cameraPosition.z) / (fogEnd - fogStart);
    fogFactor = clamp(fogFactor, 0.0f, 1.0f);
}
