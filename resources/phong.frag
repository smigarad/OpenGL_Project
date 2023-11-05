#version 460

in vec4 worldPos;
in vec3 worldNorm;

out vec4 fragColor;

uniform vec3 lightPos; // pozice světla ve světových souřadnicích
uniform vec3 lightColor;    // barva světla
uniform vec3 lightAmbient; // ambientní barva světla
uniform float r_a;
uniform float r_d;
uniform float r_s;

uniform vec3 objectColor;
uniform vec3 camPos;
uniform float shininess;
uniform float constant;
uniform float linear;
uniform float quadratic;

void main(void) {
    vec3 lightVec = lightPos - worldPos.xyz;
    vec3 lightDir = normalize(lightVec);
    vec3 viewDir = normalize(camPos - worldPos.xyz);
    float distance = length(lightVec);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
    attenuation = max(attenuation, 0.0);
    float diff = max(dot(lightDir, normalize(worldNorm)), 0.0);

    vec4 diffuse = diff * vec4(lightColor,1.0);

    vec3 reflectDir = reflect(-lightDir, normalize(worldNorm));
    float spec = 0.f;
    if (dot(lightDir, normalize(worldNorm)) > 0.f) {
        spec = pow(max(dot(viewDir, reflectDir), 0.0),shininess);
    }
    float specularStrength = 0.5;
    vec4 specular = specularStrength * spec * vec4(lightColor,1.0);

    diffuse *= attenuation;
    specular *= attenuation;
    vec4 ambient = vec4(lightAmbient,1.0);
    ambient *= attenuation;
    fragColor = (ambient + diffuse + specular) * vec4(objectColor, 1.0);
}

