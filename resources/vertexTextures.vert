#version 460
layout(location=0) in vec3 vertex_position;
layout(location=1) in vec3 vertex_normal;
layout(location=2) in vec2 vertex_texture;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec4 worldPos;
out vec3 worldNorm;
out vec2 texCoord;
out mat3 normalMatrix;

void main(){
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vertex_position, 1.0);
    worldPos = modelMatrix * vec4(vertex_position, 1.0);
    worldNorm = normalize(transpose(inverse(mat3(modelMatrix))) * vertex_normal);
    texCoord = vertex_texture;
    normalMatrix = transpose(inverse(mat3(modelMatrix)));
}