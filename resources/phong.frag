#version 400
in vec4 worldPos;
in vec3 worldNorm;

out vec4 fragColor;

uniform vec3 lightPos; // pozice světla ve světových souřadnicích
uniform vec3 lightColor;    // barva světla
uniform vec3 lightAmbient; // ambientní barva světla

uniform vec3 camPos;

void main(void) {
    vec3 lightVec = lightPos - worldPos.xyz;
    vec3 lightDir = normalize(lightVec);
    vec3 viewDir = normalize(camPos - worldPos.xyz);
    vec3 norm = normalize(worldNorm);
    float diff = max(dot(lightDir, norm), 0.0);
    vec4 diffuse = diff * vec4(lightColor,1.0);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    float specularStrength = 0.5;
    vec4 specular = specularStrength * spec * vec4(lightColor,1.0);
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    fragColor = (vec4(lightAmbient,1.0) + diffuse + specular) * objectColor;
}