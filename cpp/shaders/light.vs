#version 400

in vec3 inputPosition;
in vec2 inputTexCoord;
in vec3 inputNormal;


out vec2 texCoord;
out vec3 normal;
out vec3 viewDirection;


uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;

void main(void)
{
    vec4 worldPosition;

    gl_Position = vec4(inputPosition, 1.0f) * worldMatrix;
    gl_Position = gl_Position * viewMatrix;
    gl_Position = gl_Position * projectionMatrix;

    texCoord = inputTexCoord;

    normal = inputNormal * mat3(worldMatrix);

    normal = normalize(normal);

    worldPosition = vec4(inputPosition, 1.0f) * worldMatrix;

    viewDirection = cameraPosition.xyz - worldPosition.xyz;

    viewDirection = normalize(viewDirection);
}
