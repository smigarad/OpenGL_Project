#include "rotate.h"

Rotate::Rotate(float angle, float x, float y, float z)
{
    this->angle = angle;
    this->x = x;
    this->y = y;
    this->z = z;
    this->model = glm::mat4(1.0f);
}

Rotate::~Rotate()
{
}

glm::mat4 Rotate::getModelMatrix()
{
    return this->model;
}

void Rotate::apply()
{
    this->model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(x, y, z));
}