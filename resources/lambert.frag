#version 460
in vec4 worldPos;
in vec3 worldNorm;
out vec4 frag_colour;


uniform vec3 lightPos; // pozice světla ve světových souřadnicích
uniform vec3 lightColor;    // barva světla
uniform vec3 lightAmbient; // ambientní barva světla
uniform vec3 objectColor;
uniform float r_a;
uniform float r_d;
uniform float r_s;

void main() {


    vec3 light_vec = lightPos - worldPos.xyz;
    float dot_product = max(dot(normalize(light_vec), normalize(worldNorm)), 0.0);
    vec4 diffuse = dot_product * vec4(lightColor, 1.0);
    vec4 ambient = vec4(lightAmbient, 1.0);
    vec4 object_color = vec4 (objectColor ,1.0);
    frag_colour =(ambient + diffuse) * object_color;


}