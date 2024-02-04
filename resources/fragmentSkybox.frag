#version 460
in vec3 texCoords;
out vec4 fragColor;
uniform samplerCube cube;

void main(){
        fragColor = texture(cube, texCoords);
}