#version 400
out vec4 frag_colour;
uniform vec3 objectColor;
void main() {
    frag_colour = vec4(objectColor,1.0f); // Konstantní bílá barva (RGBA: 1, 1, 1, 1)
}