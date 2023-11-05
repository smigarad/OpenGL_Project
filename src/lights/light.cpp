#include "light.h"

Light::Light(glm::vec3 position, glm::vec3 color, glm::vec3 ambient) :Subject()
{
    this->position = position;
    this->color = color;
    this->ambient = ambient;
    this->constant = 1.0f;
    this->linear = 0.09f;
    this->quadratic = 0.032f;
    this->shininess = 32.0f;
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

float Light::getConstant() {
    return this->constant;
}

float Light::getLinear() {
    return this->linear;
}

float Light::getQuadratic() {
    return this->quadratic;
}

void Light::setConstant(float constant) {
    this->constant = constant;
}

void Light::setLinear(float linear) {
    this->linear = linear;
}

void Light::setQuadratic(float quadratic) {
    this->quadratic = quadratic;
}

float Light::getShininess() {
    return this->shininess;
}

void Light::setShininess(float shininess) {
    this->shininess = shininess;
}

