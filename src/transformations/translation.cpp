#include "translation.h"

Translation::Translation(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->model = glm::mat4(1.0f);
}

Translation::~Translation()
{
}

glm::mat4 Translation::getModelMatrix()
{
    return this->model;
}

void Translation::apply()
{
    this->model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}