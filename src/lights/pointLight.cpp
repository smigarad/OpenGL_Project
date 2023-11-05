#include "pointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 color, glm::vec3 ambient, float constant, float linear, float quadratic) :Light(position, color, ambient)
{
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
    this->type = LightType::POINT;
}

PointLight::~PointLight()
{
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color, glm::vec3 ambient) : Light(position, color, ambient) {
this->constant = 1.0f;
    this->linear = 0.09f;
    this->quadratic = 0.032f;
    this->type = LightType::POINT;
}

