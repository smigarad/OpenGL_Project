#include "scale.h"

Scale::Scale(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->model = glm::mat4(1.0f);
}

Scale::~Scale()
{
}

glm::mat4 Scale::getModelMatrix()
{
    return this->model;
}

void Scale::apply()
{
    this->model = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
}

