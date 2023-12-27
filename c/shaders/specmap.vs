#version 400

in vec3 inputPosition;
in vec2 inputTexCoord;
in vec3 inputNormal;
in vec3 inputTangent;
in vec3 inputBinormal;

out vec2 texCoord;
out vec3 normal;
out vec3 tangent;
out vec3 binormal;
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

    tangent = inputTangent * mat3(worldMatrix);
    tangent = normalize(tangent);

    binormal = inputBinormal * mat3(worldMatrix);
    binormal = normalize(binormal);

    worldPosition = vec4(inputPosition, 1.0f) * worldMatrix;

    viewDirection = cameraPosition.xyz - worldPosition.xyz;

    viewDirection = normalize(viewDirection);
}

