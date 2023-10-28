#version 460
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vertex_normal;

out vec4 worldPos;
out vec3 worldNorm;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (vp, 1.0);
    worldPos = modelMatrix * vec4(vp, 1.0);
    worldNorm = normalize(transpose(inverse(mat3(modelMatrix))) * vertex_normal);


}