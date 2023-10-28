#include "scene.h"

Scene::Scene(GLFWwindow *window) {
    this->objects = std::vector<DrawableObject *>();
    this->camera = nullptr;
    this->window = window;
    this->light = nullptr;
    this->camera = new Camera();

    this->planet1RotationSpeed = 10.f;
    this->planet2RotationSpeed = 10.f;
    this->planet3RotationSpeed = 10.f;
    this->planet4RotationSpeed = 10.f;
    this->planet5RotationSpeed = 10.f;
    this->planet6RotationSpeed = 10.f;
    this->planet7RotationSpeed = 10.f;
    this->planet8RotationSpeed = 10.f;
}

Scene::Scene(const char *vertex_shader, const char *fragment_shader) {
    this->objects = std::vector<DrawableObject *>();
}

Scene::~Scene() {
    for (auto object: objects) {
        delete object;
    }
    delete this->camera;
    delete this->light;
}

void Scene::addObject(DrawableObject *object) {
    objects.push_back(object);
}

void Scene::draw() {
    for (auto object: objects) {
        object->draw();
    }
}

Scene *Scene::makeScene1(GLFWwindow *window) {
    Scene *scene = new Scene(window);
    Light *light = new Light(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0), glm::vec3(0.1f));
    scene->light = light;
    ShaderProgram *shaderProgram1 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/lambert.frag");
    scene->camera->addObserver(shaderProgram1);
    scene->light->addObserver(shaderProgram1);

    Model *model = new Model(suziFlat, sizeof(suziFlat));
    DrawableObject *object = new DrawableObject(model, shaderProgram1);
    scene->addObject(object);

    Scale *scale = new Scale(0.2f, 0.2f, 0.2f);
    Translation *translation = new Translation(0.0f, 1.0f, 0.0f);
    object->transformationComposite->addTransformation(translation);
    object->transformationComposite->apply();

    object->transformationComposite->removeTransformation(scale);
    object->transformationComposite->removeTransformation(translation);
//    delete rotation;
    delete scale;
    delete translation;
    return scene;
}


Scene *Scene::makeScene2(GLFWwindow *window) {
    Scene *scene = new Scene(window);
    Light *light = new Light(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0), glm::vec3(0.1f));
    scene->light = light;
    ShaderProgram *shaderProgram1 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/blinn.frag");
    ShaderProgram *shaderProgram2 = new ShaderProgram("../resources/vertex_upgraded.vert","../resources/constant.frag");
    ShaderProgram *shaderProgram3 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    ShaderProgram *shaderProgram4 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/lambert.frag");

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
    object->setMaterial(new Material(1, 1, 1));
    scene->addObject(object);

    object->transformationComposite->addTransformation(new Translation(-0.5f, 0.0f, 0.0f));
    object->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object->transformationComposite->apply();

    Model *model2 = new Model(sphere, sizeof(sphere));
    DrawableObject *object2 = new DrawableObject(model2, shaderProgram2);
    object2->setMaterial(new Material(1, 1, 1));
    scene->addObject(object2);

    object2->transformationComposite->addTransformation(new Translation(0.5f, 0.0f, 0.0f));
    object2->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object2->transformationComposite->apply();

    Model *model3 = new Model(sphere, sizeof(sphere));
    DrawableObject *object3 = new DrawableObject(model3, shaderProgram3);
    object3->setMaterial(new Material(1, 1, 1));
    scene->addObject(object3);

    object3->transformationComposite->addTransformation(new Translation(0.f, 0.5f, 0.0f));
    object3->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object3->transformationComposite->apply();

    Model *model4 = new Model(sphere, sizeof(sphere));
    DrawableObject *object4 = new DrawableObject(model4, shaderProgram4);
//    object4->setMaterial(new Material(1,1,1));
    scene->addObject(object4);


    object4->transformationComposite->addTransformation(new Translation(0.f, -0.5f, 0.0f));
    object4->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object4->transformationComposite->apply();
    return scene;
}

void Scene::update(glm::mat4 perspective) {
    this->camera->update(this->window, perspective);
    if (light != nullptr)
        this->light->notifyObservers();
    this->draw();

}

void Scene::transformObjects(std::vector<Transformation *> transformations) {
    for (auto object: this->objects) {
        this->transformObject(object, transformations);
    }
}

void Scene::transformObject(DrawableObject *object, std::vector<Transformation *> transformations) {
    for (auto transformation: transformations) {
        object->transformationComposite->addTransformation(transformation);
    }
    object->transformationComposite->apply();
    for (auto transformation: transformations) {
        object->transformationComposite->removeTransformation(transformation);
    }
}

void Scene::transformObject(DrawableObject *object, Transformation *transformation) {
    object->transformationComposite->addTransformation(transformation);
    object->transformationComposite->apply();
    object->transformationComposite->removeTransformation(transformation);
}

Scene *Scene::makeSceneSolarSystem(GLFWwindow *window) {
    Scene *scene = new Scene(window);
    scene->light = new Light(glm::vec3(0.f), glm::vec3(1.f), glm::vec3(0.1f));

    ShaderProgram *sunShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/constant.frag");
    Model *sunModel = new Model(sphere, sizeof(sphere));
    DrawableObject *sun = new DrawableObject(sunModel, sunShader, glm::vec3(1.0f, 1.0f, 0.0f));
    scene->addObject(sun);
    scene->camera->addObserver(sunShader);

    sun->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    sun->transformationComposite->apply();

    ShaderProgram *mercuryShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    Model *mercuryModel = new Model(sphere, sizeof(sphere));
    DrawableObject *mercury = new DrawableObject(mercuryModel, mercuryShader, glm::vec3(0.7f, 0.7f, 0.7f));
    scene->addObject(mercury);
    scene->camera->addObserver(mercuryShader);
    scene->light->addObserver(mercuryShader);

    ShaderProgram *venusShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    Model *venusModel = new Model(sphere, sizeof(sphere));
    DrawableObject *venus = new DrawableObject(venusModel, venusShader, glm::vec3(0.9f, 0.8f, 0.6f));
    scene->addObject(venus);
    scene->camera->addObserver(venusShader);
    scene->light->addObserver(venusShader);

    ShaderProgram *marsShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    Model *marsModel = new Model(sphere, sizeof(sphere));
    DrawableObject *mars = new DrawableObject(marsModel, marsShader, glm::vec3(1.0f, 0.3f, 0.1f));
    scene->addObject(mars);
    scene->camera->addObserver(marsShader);
    scene->light->addObserver(marsShader);

    ShaderProgram *jupiterShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    Model *jupiterModel = new Model(sphere, sizeof(sphere));
    DrawableObject *jupiter = new DrawableObject(jupiterModel, jupiterShader,glm::vec3(0.9f, 0.6f, 0.4f));
    scene->addObject(jupiter);
    scene->camera->addObserver(jupiterShader);
    scene->light->addObserver(jupiterShader);

    ShaderProgram *earthShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    Model *earthModel = new Model(sphere, sizeof(sphere));
    DrawableObject *earth = new DrawableObject(earthModel, earthShader, glm::vec3(0.2f, 0.4f, 1.0f));
    scene->addObject(earth);
    scene->camera->addObserver(earthShader);
    scene->light->addObserver(earthShader);

    ShaderProgram *moonShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    Model *moonModel = new Model(sphere, sizeof(sphere));
    DrawableObject *moon = new DrawableObject(moonModel, moonShader, glm::vec3(1.0f, 1.0f, 1.0f));
    scene->addObject(moon);
    scene->camera->addObserver(moonShader);
    scene->light->addObserver(moonShader);




    return scene;
}

void Scene::rotatePlanets() {

    TransformationComposite* mercuryTransformation = new TransformationComposite();
    mercuryTransformation->addTransformation(new Rotate(this->planet1RotationSpeed, 0.0f, 1.0f, 0.0f));
    mercuryTransformation->addTransformation(new Translation(0.5f, 0.0f, 0.0f));
    mercuryTransformation->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    this->objects[1]->setTransformationComposite(mercuryTransformation);
    this->objects[1]->transformationComposite->apply();


//    this->objects[1]->transformationComposite->addTransformation(new Rotate(0.1, 0.0f, 0.0f, 0.0f));

    TransformationComposite* venusTransformation = new TransformationComposite();
    venusTransformation->addTransformation(new Rotate(this->planet2RotationSpeed, 1.0f, 0.0f, 0.0f));
    venusTransformation->addTransformation(new Translation(2.f, 0.4f, 0.0f));
    venusTransformation->addTransformation(new Scale(0.4f, 0.4f, 0.4f));
    this->objects[2]->setTransformationComposite(venusTransformation);
    this->objects[2]->transformationComposite->apply();



    TransformationComposite* marsTransformation = new TransformationComposite();
    marsTransformation->addTransformation(new Rotate(this->planet3RotationSpeed, 0.0f, 0.0f, 1.0f));
    marsTransformation->addTransformation(new Translation(1.52f, 0.0f, 0.0f));
    marsTransformation->addTransformation(new Scale(0.3f, 0.3f, 0.3f));
    this->objects[3]->setTransformationComposite(marsTransformation);
    this->objects[3]->transformationComposite->apply();

    TransformationComposite* jupiterTransformation = new TransformationComposite();
    jupiterTransformation->addTransformation(new Rotate(this->planet4RotationSpeed, 0.0f, 1.0f, 0.0f));
    jupiterTransformation->addTransformation(new Translation(5.2f, 0.0f, 0.0f));
    jupiterTransformation->addTransformation(new Scale(0.5f, 0.5f, 0.5f));
    this->objects[4]->setTransformationComposite(jupiterTransformation);
    this->objects[4]->transformationComposite->apply();

    TransformationComposite* earthTransformation = new TransformationComposite();
    earthTransformation->addTransformation(new Rotate(this->planet5RotationSpeed, 0.0f, 0.0f, 1.0f));
    earthTransformation->addTransformation(new Translation(1.0f, 0.0f, 0.0f));
    earthTransformation->addTransformation(new Scale(0.3f, 0.3f, 0.3f));
    this->objects[5]->setTransformationComposite(earthTransformation);
    this->objects[5]->transformationComposite->apply();

    //moon moves around earth
    TransformationComposite* moonTransformation = new TransformationComposite();
    moonTransformation->addTransformation(new Rotate(this->planet6RotationSpeed, 0.0f, 0.0f, 1.0f));
    moonTransformation->addTransformation(new Translation(0.0f, 0.5f, 0.0f));
    moonTransformation->addTransformation(new Scale(0.1f, 0.1f, 0.1f));
    this->objects[6]->setTransformationComposite(moonTransformation);
    this->objects[6]->transformationComposite->apply();

    this->planet1RotationSpeed += 0.2f;
    this->planet2RotationSpeed += 0.1f;
    this->planet3RotationSpeed += 0.2f;
    this->planet4RotationSpeed += 0.2f;
    this->planet5RotationSpeed += 0.1f;
    this->planet6RotationSpeed += 0.2f;
}



