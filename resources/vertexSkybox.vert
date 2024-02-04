#version 460
layout (location = 0 ) in vec3 pos;

out vec3 texCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
    texCoords = pos;
    gl_Position = (projectionMatrix * mat4(mat3(viewMatrix))) * vec4(pos, 1.0);
}