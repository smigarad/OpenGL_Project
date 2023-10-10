#include "scene.h"

Scene::Scene()
{
    this->objects = std::vector<DrawableObject*>();
    this->shaderProgram = new ShaderProgram();
}

Scene::Scene(const char* vertex_shader, const char* fragment_shader)
{
    this->objects = std::vector<DrawableObject*>();
    this->shaderProgram = new ShaderProgram(vertex_shader, fragment_shader);
}
Scene::~Scene()
{
    for (auto object : objects)
    {
        delete object;
    }
}

void Scene::addObject(DrawableObject* object)
{
    objects.push_back(object);
}

void Scene::draw()
{
    for (auto object : objects)
    {
        object->draw();
    }
}
