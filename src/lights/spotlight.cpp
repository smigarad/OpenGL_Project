#include "spotlight.h"

Spotlight::Spotlight(glm::vec3 position, glm::vec3 color, glm::vec3 ambient, glm::vec3 direction, float cutOff, float outerCutOff) :Light(position, color, ambient)
{
    this->direction = direction;
    this->cutOff = cutOff;
    this->outerCutOff = outerCutOff;
    this->type = LightType::SPOTLIGHT;
}


