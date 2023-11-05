#version 460
#define MAX_LIGHTS 4
const uint DIR_LIGHT = 0u;
const uint POINT_LIGHT = 1u;
const uint SPOT_LIGHT = 2u;

struct Light {
    int type;
    vec3 position;
    vec3 direction;
    vec3 color;
    vec3 ambient;
    float diffuse;
    float specular;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};

uniform float shininess;
in vec4 worldPos;
in vec3 worldNorm;

out vec4 fragColor;

uniform int lightCount;
uniform Light lights[MAX_LIGHTS];
uniform float r_a;
uniform float r_d;
uniform float r_s;

uniform vec3 objectColor;
uniform vec3 camPos;
uniform vec3 camTarget; //baterka
uniform bool cameraSpotlight;
vec4 calculateDirLight(Light light, vec3 normal, vec3 viewDir);
vec4 calculatePointLight(Light light, vec3 normal, vec3 viewDir, vec3 fragPos);
vec4 calculateSpotLight(Light light, vec3 normal, vec3 viewDir, vec3 fragPos);
void main(void) {
    vec3 viewDir = normalize(camPos - worldPos.xyz);
    vec4 result = vec4(0.0);
    for (int i = 0; i < lightCount; i++) {
//        if (lights[i].type == DIR_LIGHT) {
//            result += calculateDirLight(lights[i], worldNorm, viewDir);
//        }
//        if (lights[i].type == POINT_LIGHT){
//            result += calculatePointLight(lights[i], worldNorm, viewDir, worldPos.xyz);
//        }
        if (lights[i].type == SPOT_LIGHT){
            result += calculateSpotLight(lights[i], worldNorm, viewDir, worldPos.xyz);
        }
    }

    fragColor = result * vec4(objectColor, 1.0);
}

vec4 calculateDirLight(Light light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(lightDir, normalize(normal)), 0.0);
    vec4 diffuse = diff * vec4(light.color,1.0);

    vec3 reflectDir = reflect(-lightDir, normalize(normal));
    float spec = 0.f;
    if (diff > 0.f) {
        spec = pow(max(dot(viewDir, reflectDir), 0.0),shininess);
    }
    float specularStrength = 0.5;
    vec4 specular = specularStrength * spec * vec4(light.color,1.0);

    vec4 ambient = vec4(light.ambient,1.0);
    return (ambient + diffuse + specular);
}

vec4 calculatePointLight(Light light, vec3 normal, vec3 viewDir, vec3 fragPos){
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(lightDir, normalize(normal)), 0.0);
    vec4 diffuse = diff * vec4(light.color,1.0);

    vec3 reflectDir = reflect(-lightDir, normalize(normal));
    float spec = 0.f;
    if (diff > 0.f) {
        spec = pow(max(dot(viewDir, reflectDir), 0.0),shininess);
    }
    float specularStrength = 0.5;
    vec4 specular = specularStrength * spec * vec4(light.color,1.0);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    attenuation = max(attenuation, 0.0);
    diffuse *= attenuation;
    specular *= attenuation;
    vec4 ambient = vec4(light.ambient,1.0);
    ambient *= attenuation;
    return (ambient + diffuse + specular);
}

vec4 calculateSpotLight(Light light, vec3 normal, vec3 viewDir, vec3 fragPos){
    vec3 lightDir = vec3(0.0);
    if (cameraSpotlight){
        lightDir = normalize(camPos - fragPos);
    } else {
        lightDir = normalize(light.position - fragPos);
    }

    float diff = max(dot(normalize(normal), lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normalize(normal));
    float spec = 0.f;
    if (diff > 0.f) {
        spec = pow(max(dot(viewDir, reflectDir), 0.0),shininess);
    }

    float distance = 0.f;
    if (cameraSpotlight){
        distance = length(camPos - fragPos);
    } else {
        distance = length(light.position - fragPos);
    }
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    float theta =0.f;
    if (cameraSpotlight){
        theta = dot(lightDir, normalize(-camTarget));
    } else {
        theta = dot(lightDir, normalize(-light.direction));
    }
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec4 ambient = vec4(light.ambient,1.0) ;
    vec4 diffuse = diff * vec4(light.color,1.0) ;
    float specularStrength = 0.5;
    vec4 specular = specularStrength * spec * vec4(light.color,1.0);
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}


