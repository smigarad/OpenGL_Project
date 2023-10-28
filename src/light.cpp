#include "light.h"

Light::Light(glm::vec3 position, glm::vec3 color, glm::vec3 ambient) :Subject()
{
    this->position = position;
    this->color = color;
    this->ambient = ambient;
}

Light::~Light()
{
}

glm::vec3 Light::getPosition()
{
    return this->position;
}

glm::vec3 Light::getColor()
{
    return this->color;
}

glm::vec3 Light::getAmbient()
{
    return this->ambient;
}

void Light::setPosition(glm::vec3 position)
{
    this->position = position;
}

void Light::setColor(glm::vec3 color)
{
    this->color = color;
}

void Light::setAmbient(glm::vec3 ambient)
{
    this->ambient = ambient;
}

