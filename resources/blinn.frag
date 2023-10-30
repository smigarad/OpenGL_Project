#version 460
in vec4 worldPos;
in vec3 worldNorm;

out vec4 fragColor;

uniform vec3 lightPos; // pozice světla ve světových souřadnicích
uniform vec3 lightColor;    // barva světla
uniform vec3 lightAmbient; // ambientní barva světla

uniform vec3 objectColor; // barva objektu

uniform float r_a;
uniform float r_d;
uniform float r_s;

uniform vec3 camPos;

void main(void) {
    vec3 lightDir = normalize(lightPos - worldPos.xyz);

    vec3 viewDir = normalize(camPos - worldPos.xyz);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float diff = max(dot(lightDir, normalize(worldNorm)));
    vec4 diffuse = diff * vec4(lightColor,1.0);

    vec3 reflectDir = reflect(-lightDir, normalize(worldNorm));
    float spec = 0.f;
    if (dot(lightDir, worldNorm) > 0.0)
        spec = pow(max(dot(halfwayDir, reflectDir), 0.0), 64.0);

    float specularStrength = 0.5;
    vec4 specular = specularStrength * spec * vec4(lightColor,1.0);
    fragColor = (vec4(lightAmbient,1.0) + diffuse + specular) * vec4(objectColor,1.0f);
}