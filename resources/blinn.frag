#version 460
#define MAX_LIGHTS 4

struct Light {
    vec3 position;
    vec3 color;
    float ambient;
    float diffuse;
    float specular;
    float constant;
    float linear;
    float quadratic;
};

uniform Light lights[MAX_LIGHTS];
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

uniform float shininess;
uniform float constant;
uniform float linear;
uniform float quadratic;
void main(void) {
    vec3 lightDir = normalize(lightPos - worldPos.xyz);
    float distance = length(lightPos - worldPos.xyz);
    vec3 viewDir = normalize(camPos - worldPos.xyz);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
    attenuation = max(attenuation,0.0f);
    float diff = max(dot(lightDir, normalize(worldNorm)),0.0);
    vec4 diffuse = attenuation * diff * vec4(lightColor,1.0);

    vec3 reflectDir = reflect(-lightDir, normalize(worldNorm));
    float spec = 0.f;
    if (dot(lightDir, worldNorm) > 0.0)
    {
        spec = pow(max(dot(normalize(worldNorm),halfwayDir), 0.0), shininess);
    }
    float specularStrength = 0.5;
    vec4 specular = attenuation * specularStrength * spec * vec4(lightColor,1.0);
    fragColor = (attenuation * vec4(lightAmbient,1.0) + diffuse + specular) * vec4(objectColor,1.0f);
}