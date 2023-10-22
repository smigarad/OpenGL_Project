#include "scene.h"

Scene::Scene(GLFWwindow *window)
{
    this->objects = std::vector<DrawableObject*>();
    this->camera = new Camera();
    this->shaderPrograms = std::vector<ShaderProgram*>();
    this->window = window;
}

Scene::Scene(const char* vertex_shader, const char* fragment_shader)
{
    this->objects = std::vector<DrawableObject*>();
}
Scene::~Scene()
{
    for (auto object : objects)
    {
        delete object;
    }
    delete this->camera;
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

// void Scene::draw(glm::mat4 perspective, glm::mat4 view)
// {
//     for (auto object : objects)
//     {
//         object->draw(perspective, view);
//     }
// }

Scene* Scene::makeScene1(GLFWwindow *window){
    Scene* scene = new Scene(window);
    Light *light = new Light(glm::vec3(2.f, 0.f, 0.f), glm::vec3(1.0), glm::vec3(0.1f));
    scene->light = light;
    ShaderProgram* shaderProgram1 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/blinn.frag");
    shaderProgram1->camera = scene->camera;
    // scene->shaderPrograms.push_back(shaderProgram1);
    // scene->shaderPrograms.push_back(shaderProgram2);
    // scene->shaderPrograms.push_back(shaderProgram3);

    scene->camera->addObserver(shaderProgram1);

    scene->light->addObserver(shaderProgram1);

    Model *model = new Model(sphere, sizeof(sphere));
    DrawableObject *object = new DrawableObject(model, shaderProgram1);
    scene->addObject(object);


    object->transformationComposite->addTransformation(new Rotate(180.0f, 0.0f, 1.0f, 0.0f));
    object->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object->transformationComposite->addTransformation(new Translation(-2.0f, 0.0f, 0.0f));
    object->transformationComposite->apply();

    return scene;
}


Scene* Scene::makeScene2(GLFWwindow *window){
    Scene* scene = new Scene(window);
    Light *light = new Light(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0), glm::vec3(0.1f));
    scene->light = light;
    ShaderProgram* shaderProgram1 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/lambert.frag");
    ShaderProgram* shaderProgram2 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/constant.frag");
    ShaderProgram* shaderProgram3 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    ShaderProgram* shaderProgram4 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/blinn.frag");
    shaderProgram1->camera = scene->camera;
    shaderProgram2->camera = scene->camera;
    shaderProgram3->camera = scene->camera;
    shaderProgram4->camera = scene->camera;
    // scene->shaderPrograms.push_back(shaderProgram1);
    // scene->shaderPrograms.push_back(shaderProgram2);
    // scene->shaderPrograms.push_back(shaderProgram3);

    scene->camera->addObserver(shaderProgram1);
    scene->camera->addObserver(shaderProgram2);
    scene->camera->addObserver(shaderProgram3);
    scene->camera->addObserver(shaderProgram4);
    scene->light->addObserver(shaderProgram1);
    scene->light->addObserver(shaderProgram2);
    scene->light->addObserver(shaderProgram3);
    scene->light->addObserver(shaderProgram4);
    Model *model = new Model(sphere, sizeof(sphere));
    DrawableObject *object = new DrawableObject(model, shaderProgram1);
    scene->addObject(object);


    object->transformationComposite->addTransformation(new Rotate(180.0f, 0.0f, 1.0f, 0.0f));
    object->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object->transformationComposite->addTransformation(new Translation(-1.f, 0.0f, 0.0f));
    object->transformationComposite->apply();

    Model *model2 = new Model(sphere, sizeof(sphere));
    DrawableObject *object2 = new DrawableObject(model2, shaderProgram2);
    scene->addObject(object2);

    object2->transformationComposite->addTransformation(new Rotate(160.0f, 0.0f, 1.0f, 0.0f));
    object2->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object2->transformationComposite->addTransformation(new Translation(1.f, 0.0f, 0.0f));
    object2->transformationComposite->apply();

    Model *model3 = new Model(sphere, sizeof(sphere));
    DrawableObject *object3 = new DrawableObject(model3, shaderProgram3);
    scene->addObject(object3);

    object3->transformationComposite->addTransformation(new Rotate(200.0f, 0.0f, 1.0f, 0.0f));
    object3->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object3->transformationComposite->addTransformation(new Translation(0.f, 1.0f, 0.0f));
    object3->transformationComposite->apply();

    Model *model4 = new Model(sphere, sizeof(sphere));
    DrawableObject *object4 = new DrawableObject(model4, shaderProgram4);
    scene->addObject(object4);

    object4->transformationComposite->addTransformation(new Rotate(200.0f, 0.0f, 1.0f, 0.0f));
    object4->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object4->transformationComposite->addTransformation(new Translation(0.f, -1.0f, 0.0f));
    object4->transformationComposite->apply();
    return scene;
}

void Scene::update()
{
    this->camera->update(this->window);
    this->light->notifyObservers();
    this->draw();
    
}