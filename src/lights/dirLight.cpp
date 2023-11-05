#include "dirLight.h"

DirLight::DirLight(glm::vec3 position, glm::vec3 color, glm::vec3 ambient, glm::vec3 direction) :Light(position, color, ambient)
{
    this->direction = direction;
    this->type = LightType::DIRECTIONAL;
}
