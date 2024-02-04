#include "scene.h"

Scene::Scene(GLFWwindow *window) {
    this->objects = std::vector<DrawableObject *>();
    this->camera = nullptr;
    this->window = window;
    this->light = nullptr;
    this->lights = std::vector<Light *>();
    this->skybox = nullptr;
    this->skyboxObject = nullptr;
    this->camera = new Camera();
    this->lights = std::vector<Light *>();
    this->ePressed = false;
    this->qPressed = false;
    this->planet1RotationSpeed = 10.f;
    this->planet2RotationSpeed = 10.f;
    this->planet3RotationSpeed = 10.f;
    this->planet4RotationSpeed = 10.f;
    this->planet5RotationSpeed = 10.f;
    this->planet6RotationSpeed = 10.f;
    this->planet7RotationSpeed = 10.f;
    this->planet8RotationSpeed = 10.f;
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

void Scene::update(glm::mat4 perspective) {
    this->camera->update(this->window, perspective);
    if (this->skyboxObject != nullptr) {
        this->skybox->bind();
        this->skyboxObject->draw();
        glClear(GL_DEPTH_BUFFER_BIT);
    }
//    this->handleInput();
    if (light != nullptr) {
        this->light->notifyObservers();
    }
    for (auto light: lights) {
        light->notifyObservers();
    }
    this->draw();

}


Scene *Scene::makeSceneLightTest(GLFWwindow *window) {
    Scene *scene = new Scene(window);
    Light *light = new Light(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0), glm::vec3(0.1f));
    scene->light = light;
    ShaderProgram *shaderProgram1 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    ShaderProgram *shaderProgram2 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/blinn.frag");
    ShaderProgram *shaderProgram3 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/lambert.frag");
    ShaderProgram *shaderProgram4 = new ShaderProgram("../resources/vertex_upgraded.vert",
                                                      "../resources/constant.frag");

    scene->camera->addObserver(shaderProgram1);
    scene->camera->addObserver(shaderProgram2);
    scene->camera->addObserver(shaderProgram3);
    scene->camera->addObserver(shaderProgram4);
    scene->light->addObserver(shaderProgram1);
    scene->light->addObserver(shaderProgram2);
    scene->light->addObserver(shaderProgram3);
    scene->light->addObserver(shaderProgram4);
    Model *model = new Model(sphere, sizeof(sphere));
    DrawableObject *object = new DrawableObject(model, shaderProgram1, glm::vec3(0.385, 0.647, 0.812));
    object->setMaterial(new Material(1, 1, 1));
    scene->addObject(object);

    object->transformationComposite->addTransformation(new Translation(-0.5f, 0.0f, 0.0f));
    object->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object->transformationComposite->apply();

    Model *model2 = new Model(sphere, sizeof(sphere));
    DrawableObject *object2 = new DrawableObject(model2, shaderProgram2, glm::vec3(0.385, 0.647, 0.812));
    object2->setMaterial(new Material(1, 1, 1));
    scene->addObject(object2);

    object2->transformationComposite->addTransformation(new Translation(0.5f, 0.0f, 0.0f));
    object2->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object2->transformationComposite->apply();

    Model *model3 = new Model(sphere, sizeof(sphere));
    DrawableObject *object3 = new DrawableObject(model3, shaderProgram3, glm::vec3(0.385, 0.647, 0.812));
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

Scene *Scene::makeScenePhongTest(GLFWwindow *window) {
    Scene *scene = new Scene(window);
    Light *light = new Light(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0), glm::vec3(0.1f));
    scene->light = light;
    ShaderProgram *shaderProgram1 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    ShaderProgram *shaderProgram2 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    ShaderProgram *shaderProgram3 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    ShaderProgram *shaderProgram4 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");

    scene->camera->addObserver(shaderProgram1);
    scene->camera->addObserver(shaderProgram2);
    scene->camera->addObserver(shaderProgram3);
    scene->camera->addObserver(shaderProgram4);
    scene->light->addObserver(shaderProgram1);
    scene->light->addObserver(shaderProgram2);
    scene->light->addObserver(shaderProgram3);
    scene->light->addObserver(shaderProgram4);
    Model *model = new Model(sphere, sizeof(sphere));
    DrawableObject *object = new DrawableObject(model, shaderProgram1, glm::vec3(0.385, 0.647, 0.812));
    object->setMaterial(new Material(1, 1, 1));
    scene->addObject(object);

    object->transformationComposite->addTransformation(new Translation(-0.5f, 0.0f, 0.0f));
    object->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object->transformationComposite->apply();

    Model *model2 = new Model(sphere, sizeof(sphere));
    DrawableObject *object2 = new DrawableObject(model2, shaderProgram2, glm::vec3(0.385, 0.647, 0.812));
    object2->setMaterial(new Material(1, 1, 1));
    scene->addObject(object2);

    object2->transformationComposite->addTransformation(new Translation(0.5f, 0.0f, 0.0f));
    object2->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object2->transformationComposite->apply();

    Model *model3 = new Model(sphere, sizeof(sphere));
    DrawableObject *object3 = new DrawableObject(model3, shaderProgram3, glm::vec3(0.385, 0.647, 0.812));
    object3->setMaterial(new Material(1, 1, 1));
    scene->addObject(object3);

    object3->transformationComposite->addTransformation(new Translation(0.f, 0.5f, 0.0f));
    object3->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object3->transformationComposite->apply();

    Model *model4 = new Model(sphere, sizeof(sphere));
    DrawableObject *object4 = new DrawableObject(model4, shaderProgram4, glm::vec3(0.385, 0.647, 0.812));
//    object4->setMaterial(new Material(1,1,1));
    scene->addObject(object4);


    object4->transformationComposite->addTransformation(new Translation(0.f, -0.5f, 0.0f));
    object4->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object4->transformationComposite->apply();
    return scene;
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
    DrawableObject *jupiter = new DrawableObject(jupiterModel, jupiterShader, glm::vec3(0.9f, 0.6f, 0.4f));
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

    TransformationComposite *mercuryTransformation = new TransformationComposite();
    mercuryTransformation->addTransformation(new Rotate(this->planet1RotationSpeed, 0.0f, 1.0f, 0.0f));
    mercuryTransformation->addTransformation(new Translation(0.5f, 0.0f, 0.0f));
    mercuryTransformation->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    this->objects[1]->setTransformationComposite(mercuryTransformation);
    this->objects[1]->transformationComposite->apply();

    TransformationComposite *venusTransformation = new TransformationComposite();
    venusTransformation->addTransformation(new Rotate(this->planet2RotationSpeed, 1.0f, 0.0f, 0.0f));
    venusTransformation->addTransformation(new Translation(2.f, 1.4f, 0.0f));
    venusTransformation->addTransformation(new Scale(0.4f, 0.4f, 0.4f));
    this->objects[2]->setTransformationComposite(venusTransformation);
    this->objects[2]->transformationComposite->apply();


    TransformationComposite *marsTransformation = new TransformationComposite();
    marsTransformation->addTransformation(new Rotate(this->planet3RotationSpeed, 0.0f, 0.0f, 1.0f));
    marsTransformation->addTransformation(new Translation(1.f, 0.5f, 0.0f));
    marsTransformation->addTransformation(new Scale(0.3f, 0.3f, 0.3f));
    this->objects[3]->setTransformationComposite(marsTransformation);
    this->objects[3]->transformationComposite->apply();

    TransformationComposite *jupiterTransformation = new TransformationComposite();
    jupiterTransformation->addTransformation(new Rotate(this->planet4RotationSpeed, 0.0f, 1.0f, 0.0f));
    jupiterTransformation->addTransformation(new Translation(3.f, 2.0f, 0.0f));
    jupiterTransformation->addTransformation(new Scale(0.5f, 0.5f, 0.5f));
    this->objects[4]->setTransformationComposite(jupiterTransformation);
    this->objects[4]->transformationComposite->apply();

    TransformationComposite *earthTransformation = new TransformationComposite();
    earthTransformation->addTransformation(new Rotate(this->planet5RotationSpeed, 0.0f, 0.0f, 1.0f));
    earthTransformation->addTransformation(new Translation(1.0f, 2.0f, 0.0f));
    earthTransformation->addTransformation(new Scale(0.3f, 0.3f, 0.3f));
    this->objects[5]->setTransformationComposite(earthTransformation);
    this->objects[5]->transformationComposite->apply();

    TransformationComposite *moonTransformation = new TransformationComposite();
    moonTransformation->addTransformation(new Rotate(this->planet5RotationSpeed, 0.0f, 0.0f, 1.0f));
    moonTransformation->addTransformation(new Translation(1.0f, 2.f, 0.0f));
    moonTransformation->addTransformation(new Rotate(this->planet6RotationSpeed, 0.0f, 0.0f, 1.0f));
    moonTransformation->addTransformation(new Translation(0.7f, 0.f, 0.0f));
    moonTransformation->addTransformation(new Scale(0.1f, 0.1f, 0.1f));
    this->objects[6]->setTransformationComposite(moonTransformation);
    this->objects[6]->transformationComposite->apply();

    this->planet1RotationSpeed += 0.2f;
    this->planet2RotationSpeed += 0.1f;
    this->planet3RotationSpeed += 0.2f;
    this->planet4RotationSpeed += 0.2f;
    this->planet5RotationSpeed += 0.5f;
    this->planet6RotationSpeed += 4.f;
}

Scene *Scene::makeSceneForest(GLFWwindow *window) {
    Scene *scene = new Scene(window);
    scene->light = new Light(glm::vec3(0.f, 5.f, 0.f), glm::vec3(1.f), glm::vec3(0.1f));
    ShaderProgram *floorShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/constant.frag");
    Model *floorModel = new Model(plain, sizeof(plain));
    DrawableObject *floor = new DrawableObject(floorModel, floorShader, glm::vec3(0.0f, 0.5f, 0.0f));
    floor->transformationComposite->addTransformation(new Scale(200.f, 2.f, 200.f));
    floor->transformationComposite->addTransformation(new Translation(0.f, 0.f, 0.5f));
    floor->transformationComposite->apply();
    scene->addObject(floor);
    scene->camera->addObserver(floorShader);
    scene->light->addObserver(floorShader);

    srand(time(NULL));

    int bushesNumber = rand() % 100 + 1;
    printf("%d\n", bushesNumber);
    int treesNumber = rand() % 100 + 1;
    int suziFlatNumber = rand() % 30 + 1;
    int suziSmoothNumber = rand() % 30 + 1;
    int spheresNumber = rand() % 30 + 1;

    for (int i = 0; i < bushesNumber; i++) {
        Model *bushesModel = new Model(bushes, sizeof(bushes));
        ShaderProgram *bushesShader = new ShaderProgram("../resources/vertex_upgraded.vert",
                                                        "../resources/constant.frag");
        DrawableObject *bush = new DrawableObject(bushesModel, bushesShader, glm::vec3(0.0f, 0.3f, 0.0f));
        scene->addObject(bush);
        float x = (float) ((rand() % 30 + 1) / 10.f);
        float z = (float) ((rand() % 30 + 1) / 10.f);
        float scale_x = (float) ((rand() % 5 + 1) / 10.f);
        float angle = (float) ((rand() % 360 + 1) / 1.f);

        Translation *translation = new Translation(x, 0.f, z);
        Scale *scale = new Scale(scale_x, scale_x, scale_x);
        Rotate *rotate = new Rotate(angle, 0.f, 1.f, 0.f);
        bush->transformationComposite->addTransformation(rotate);
        bush->transformationComposite->addTransformation(translation);
        bush->transformationComposite->addTransformation(scale);
        bush->transformationComposite->apply();
        scene->camera->addObserver(bushesShader);
        scene->light->addObserver(bushesShader);
    }

    for (int i = 0; i < treesNumber; i++) {
        Model *treeModel = new Model(tree, sizeof(tree));
        ShaderProgram *treeShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
        DrawableObject *tree = new DrawableObject(treeModel, treeShader, glm::vec3(0.4f, 0.3f, 0.0f));
        scene->addObject(tree);
        float x = (float) ((rand() % 50 + 1) / 10.f);
        float z = (float) ((rand() % 50 + 1) / 10.f);
        float scale_x = (float) ((rand() % 3 + 1) / 10.f);
        float angle = (float) ((rand() % 360 + 1) / 1.f);
        printf("%f %f", x, z);
        Translation *translation = new Translation(x, 0.f, z);
        Scale *scale = new Scale(scale_x, scale_x, scale_x);
        Rotate *rotate = new Rotate(angle, 0.f, 1.f, 0.f);

        tree->transformationComposite->addTransformation(translation);
        tree->transformationComposite->addTransformation(rotate);
        tree->transformationComposite->addTransformation(scale);
        tree->transformationComposite->apply();
        scene->camera->addObserver(treeShader);
        scene->light->addObserver(treeShader);
    }

    for (int i = 0; i < suziFlatNumber; i++) {
        Model *suziFlatModel = new Model(suziFlat, sizeof(suziFlat));
        ShaderProgram *suziFlatShader = new ShaderProgram("../resources/vertex_upgraded.vert",
                                                          "../resources/phong.frag");
        DrawableObject *suziFlat = new DrawableObject(suziFlatModel, suziFlatShader, glm::vec3(0.4f, 0.3f, 0.2f));
        scene->addObject(suziFlat);
        float x = (float) ((rand() % 30 + 1) / 10.f);
        float z = (float) ((rand() % 30 + 1) / 10.f);
        float scale_x = (float) ((rand() % 3 + 1) / 10.f);
        float angle = (float) ((rand() % 360 + 1) / 1.f);

        Translation *translation = new Translation(x, 0.2f, z);
        Scale *scale = new Scale(scale_x, scale_x, scale_x);
        Rotate *rotate = new Rotate(angle, 0.f, 1.f, 0.f);

        suziFlat->transformationComposite->addTransformation(rotate);
        suziFlat->transformationComposite->addTransformation(translation);
        suziFlat->transformationComposite->addTransformation(scale);
        suziFlat->transformationComposite->apply();
        scene->camera->addObserver(suziFlatShader);
        scene->light->addObserver(suziFlatShader);
    }

    for (int i = 0; i < suziSmoothNumber; i++) {
        Model *suziSmoothModel = new Model(suziSmooth, sizeof(suziSmooth));
        ShaderProgram *suziSmoothShader = new ShaderProgram("../resources/vertex_upgraded.vert",
                                                            "../resources/phong.frag");
        DrawableObject *suziSmooth = new DrawableObject(suziSmoothModel, suziSmoothShader, glm::vec3(0.1f, 0.f, 0.8f));
        scene->addObject(suziSmooth);
        float x = (float) ((rand() % 30 + 1) / 10.f);
        float z = (float) ((rand() % 30 + 1) / 10.f);
        float scale_x = (float) ((rand() % 3 + 1) / 10.f);
        float angle = (float) ((rand() % 360 + 1) / 1.f);

        Translation *translation = new Translation(x, 0.2f, z);
        Scale *scale = new Scale(scale_x, scale_x, scale_x);
        Rotate *rotate = new Rotate(angle, 0.f, 1.f, 0.f);

        suziSmooth->transformationComposite->addTransformation(rotate);
        suziSmooth->transformationComposite->addTransformation(translation);
        suziSmooth->transformationComposite->addTransformation(scale);
        suziSmooth->transformationComposite->apply();
        scene->camera->addObserver(suziSmoothShader);
        scene->light->addObserver(suziSmoothShader);
    }

    for (int i = 0; i < spheresNumber; i++) {
        Model *sphereModel = new Model(sphere, sizeof(sphere));
        ShaderProgram *sphereShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
        DrawableObject *sphere = new DrawableObject(sphereModel, sphereShader, glm::vec3(0.7f, 0.2f, 0.5f));
        scene->addObject(sphere);
        float x = (float) ((rand() % 30 + 1) / 10.f);
        float z = (float) ((rand() % 30 + 1) / 10.f);
        float scale_x = (float) ((rand() % 3 + 1) / 10.f);
        float angle = (float) ((rand() % 360 + 1) / 1.f);

        Translation *translation = new Translation(x, 0.2f, z);
        Scale *scale = new Scale(scale_x, scale_x, scale_x);
        Rotate *rotate = new Rotate(angle, 0.f, 1.f, 0.f);

        sphere->transformationComposite->addTransformation(rotate);
        sphere->transformationComposite->addTransformation(translation);
        sphere->transformationComposite->addTransformation(scale);
        sphere->transformationComposite->apply();
        scene->camera->addObserver(sphereShader);
        scene->light->addObserver(sphereShader);
    }
//    int treesNumber = std::rand()

    return scene;
}

Scene *Scene::makeSceneModifiedPhong(GLFWwindow *window) {
    Scene *scene = new Scene(window);
    scene->light = new Light(glm::vec3(0.f), glm::vec3(1.f), glm::vec3(0.1f));
    ShaderProgram *shaderProgram1 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    ShaderProgram *shaderProgram2 = new ShaderProgram("../resources/vertex_upgraded.vert",
                                                      "../resources/phong_variant.frag");

    scene->camera->addObserver(shaderProgram1);
    scene->camera->addObserver(shaderProgram2);
    scene->light->addObserver(shaderProgram1);
    scene->light->addObserver(shaderProgram2);

    Model *model = new Model(sphere, sizeof(sphere));
    DrawableObject *object = new DrawableObject(model, shaderProgram1);
    object->setMaterial(new Material(1, 1, 1));
    scene->addObject(object);

    Model *model2 = new Model(sphere, sizeof(sphere));
    DrawableObject *object2 = new DrawableObject(model2, shaderProgram2);
    object->setMaterial(new Material(1, 1, 1));
    scene->addObject(object2);

    object->transformationComposite->addTransformation(new Translation(-0.5f, 0.0f, 0.0f));
    object->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));

    object2->transformationComposite->addTransformation(new Translation(0.5f, 0.0f, 0.0f));
    object2->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));

    object->transformationComposite->apply();
    object2->transformationComposite->apply();

    return scene;
}

Scene *Scene::makeSceneModifiedLights(GLFWwindow *window) {
    Scene *scene = new Scene(window);
    DirLight *dirLight = new DirLight(glm::vec3(0.f, 5.f, 0.f), glm::vec3(1.f), glm::vec3(0.1f),
                                      glm::vec3(-0.2f, -1.0f, -0.3f));
    scene->lights.push_back(dirLight);
    PointLight *pointLight = new PointLight(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f), glm::vec3(0.1f), 1.f, 0.09f,
                                            0.032f);
    scene->lights.push_back(pointLight);
    Spotlight *spotlight = new Spotlight(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f), glm::vec3(0.05f), glm::vec3(0.f),
                                         glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.f)));
    scene->lights.push_back(spotlight);
    ShaderProgram *shaderProgram1 = new ShaderProgram("../resources/vertex_upgraded.vert",
                                                      "../resources/phongLights.frag");
    Model *model = new Model(sphere, sizeof(sphere));
    DrawableObject *object = new DrawableObject(model, shaderProgram1, glm::vec3(0.385, 0.647, 0.812));

    object->transformationComposite->addTransformation(new Translation(0.5f, 0.f, 0.f));
    object->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object->transformationComposite->apply();


    ShaderProgram *shaderProgram2 = new ShaderProgram("../resources/vertex_upgraded.vert",
                                                      "../resources/phongLights.frag");
    Model *model2 = new Model(sphere, sizeof(sphere));
    DrawableObject *object2 = new DrawableObject(model2, shaderProgram2, glm::vec3(0.385, 0.647, 0.812));

    object2->transformationComposite->addTransformation(new Translation(-0.5f, 0.0f, 0.f));
    object2->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object2->transformationComposite->apply();

    ShaderProgram *shaderProgram3 = new ShaderProgram("../resources/vertex_upgraded.vert",
                                                      "../resources/phongLights.frag");
    Model *model3 = new Model(sphere, sizeof(sphere));
    DrawableObject *object3 = new DrawableObject(model3, shaderProgram3, glm::vec3(0.385, 0.647, 0.812));

    object3->transformationComposite->addTransformation(new Translation(0.f, 0.5f, 0.f));
    object3->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object3->transformationComposite->apply();

    Model *model4 = new Model(sphere, sizeof(sphere));
    ShaderProgram *shaderProgram4 = new ShaderProgram("../resources/vertex_upgraded.vert",
                                                      "../resources/phongLights.frag");
    DrawableObject *object4 = new DrawableObject(model4, shaderProgram4, glm::vec3(0.385, 0.647, 0.812));

    object4->transformationComposite->addTransformation(new Translation(0.f, -0.5f, 0.f));
    object4->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object4->transformationComposite->apply();


    scene->camera->addObserver(shaderProgram4);
    scene->camera->addObserver(shaderProgram3);
    scene->camera->addObserver(shaderProgram2);
    scene->camera->addObserver(shaderProgram1);
    scene->addObject(object);
    scene->addObject(object2);
    scene->addObject(object3);
    scene->addObject(object4);
    for (auto light: scene->lights) {
        light->addObserver(shaderProgram1);
        light->addObserver(shaderProgram2);
        light->addObserver(shaderProgram3);
        light->addObserver(shaderProgram4);
    }
    std::vector<ShaderProgram *> shaders = {shaderProgram1, shaderProgram2, shaderProgram3, shaderProgram4};
    for (auto shader: shaders) {
        shader->sendUniformValue(3, "lightCount");
        //dir
        shader->sendUniformValue(scene->lights[0]->type, "lights[0].type");
        shader->sendUniformValue(scene->lights[0]->getColor(), "lights[0].color");
        shader->sendUniformValue(scene->lights[0]->getAmbient(), "lights[0].ambient");
        shader->sendUniformValue(dynamic_cast<DirLight *>(scene->lights[0])->direction, "lights[0].direction");

        //point
        shader->sendUniformValue(scene->lights[1]->type, "lights[1].type");
        shader->sendUniformValue(scene->lights[1]->getPosition(), "lights[1].position");
        shader->sendUniformValue(scene->lights[1]->getColor(), "lights[1].color");
        shader->sendUniformValue(scene->lights[1]->getAmbient(), "lights[1].ambient");
        shader->sendUniformValue(dynamic_cast<PointLight *>(scene->lights[1])->constant, "lights[1].constant");
        shader->sendUniformValue(dynamic_cast<PointLight *>(scene->lights[1])->linear, "lights[1].linear");
        shader->sendUniformValue(dynamic_cast<PointLight *>(scene->lights[1])->quadratic, "lights[1].quadratic");

        //spot
        shader->sendUniformValue(scene->lights[2]->type, "lights[2].type");
        shader->sendUniformValue(true, "cameraSpotlight");
        shader->sendUniformValue(scene->lights[2]->getPosition(), "lights[2].position");
        shader->sendUniformValue(scene->lights[2]->getColor(), "lights[2].color");
        shader->sendUniformValue(scene->lights[2]->getAmbient(), "lights[2].ambient");
        shader->sendUniformValue(dynamic_cast<Spotlight *>(scene->lights[2])->getConstant(), "lights[2].constant");
        shader->sendUniformValue(dynamic_cast<Spotlight *>(scene->lights[2])->getLinear(), "lights[2].linear");
        shader->sendUniformValue(dynamic_cast<Spotlight *>(scene->lights[2])->getQuadratic(), "lights[2].quadratic");
        shader->sendUniformValue(dynamic_cast<Spotlight *>(scene->lights[2])->cutOff, "lights[2].cutOff");
        shader->sendUniformValue(dynamic_cast<Spotlight *>(scene->lights[2])->outerCutOff, "lights[2].outerCutOff");
    }
    return scene;
}

Scene *Scene::makeSceneTextureAndSkybox(GLFWwindow *window) {
    Scene *scene = new Scene(window);
    DirLight *dirLight = new DirLight(glm::vec3(0.f, 5.f, 0.f), glm::vec3(1.f), glm::vec3(0.6f),
                                      glm::vec3(0.0f, -1.0f, 0.0f));
    scene->lights.push_back(dirLight);

    scene->skybox = new Skybox();
    Model *modelSkybox = new Model(skycube, sizeof(skycube), false,true);
    ShaderProgram *shaderProgramSkybox = new ShaderProgram("../resources/vertexSkybox.vert",
                                                           "../resources/fragmentSkybox.frag",true,true);
    DrawableObject *objectSkybox = new DrawableObject(modelSkybox, shaderProgramSkybox);
    printf("skybox: %d\n", objectSkybox->id);
    scene->skyboxObject = objectSkybox;


    ShaderProgram *shaderProgramFloor = new ShaderProgram("../resources/vertexTextures.vert",
                                                          "../resources/fragmentPhongLightsTextures.frag",true,true);
    Model *modelFloor = new Model(plain, sizeof(plain), true,false);
    Material *materialFloor = new Material(1.f, 1.f, 1.f, "../textures/grass.png");
    DrawableObject *objectFloor = new DrawableObject(modelFloor, shaderProgramFloor, materialFloor);
    printf("floor: %d\n", objectFloor->id);
    scene->addObject(objectFloor);
    objectFloor->transformationComposite->addTransformation(new Translation(0.f, -1.f, 0.5f));
    objectFloor->transformationComposite->addTransformation(new Scale(20.f, 1.f, 20.f));
    objectFloor->transformationComposite->apply();




    Model* building = new Model("../resources/models/building/model.obj",true,false);
    ShaderProgram* shaderProgramBuilding = new ShaderProgram("../resources/vertexTextures.vert",
                                                             "../resources/fragmentPhongLightsTextures.frag",true,true);
    DrawableObject* objectBuilding = new DrawableObject(building, shaderProgramBuilding, new Material(1.f, 1.f, 1.f, "../resources/models/building/test.png"));
    scene->addObject(objectBuilding);
    printf("building %d\n", objectBuilding->id);
    objectBuilding->transformationComposite->addTransformation(new Translation(0.f, 0.5f, 0.f));
    objectBuilding->transformationComposite->addTransformation(new Scale(1.f, 0.5f, 1.f));
    objectBuilding->transformationComposite->apply();

    Model *model = new Model(sphere, sizeof(sphere),false,false,true);
    ShaderProgram *shaderProgram = new ShaderProgram("../resources/vertex_upgraded.vert",
                                                     "../resources/phongLights.frag",true);
    DrawableObject *object = new DrawableObject(model, shaderProgram);
    object->transformationComposite->addTransformation(new Translation(1.5f, 1.f, 0.f));
    object->transformationComposite->addTransformation(new Scale(0.0f, 0.0f, 0.0f));
    object->transformationComposite->apply();
    scene->addObject(object);

    scene->setupComponents(1);
    return scene;
}

void Scene::createTree(glm::vec3 position, float scale) {

    Material *material = new Material(1.f, 1.f, 1.f, "../resources/models/tree/tree.png");
    Model *treeModel = new Model("../resources/models/tree/tree.obj", true, false);
    ShaderProgram *treeShader = new ShaderProgram("../resources/vertexTextures.vert",
                                                  "../resources/fragmentPhongLightsTextures.frag", true, true);
    DrawableObject *tree = new DrawableObject(treeModel, treeShader, material);

    tree->transformationComposite->addTransformation(new Translation(position.x, position.y, position.z));
    tree->transformationComposite->addTransformation(new Scale(scale, scale, scale));
    tree->transformationComposite->apply();
    objects.push_back(tree);
    treeShader->sendUniformValue((int)this->lights.size(), "lightCount");
    camera->addObserver(treeShader);
    for (auto light: lights) {
        light->addObserver(treeShader);
    }
}

void Scene::removeObjectById(int id) {

    for (int i = 0; i < objects.size(); i++) {
        printf("%d\n", objects[i]->id);
        if (objects[i]->id == id) {
            objects.erase(objects.begin() + i);
            printf("removed\n");
            return;
        }
    }

}

void Scene::handleInput() {
    GLuint id = 0;
    double x,y;
    glfwGetCursorPos(window, &x, &y);
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    GLbyte color[4];
    GLfloat depth;
    int new_y = height - y;

    if(!this->camera->moving){
        glReadPixels(x, new_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(x, new_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(x, new_y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &id);
//        printf("aaaaaaaaa%d\n",id);
    }
    else{
        glReadPixels(x, new_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(x, new_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(x, new_y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &id);

    }

    if(glfwGetKey(window,GLFW_KEY_Q) == GLFW_PRESS && !this->qPressed){
        qPressed = true;
        printf("pressed q");
        printf("id: %d\n",id);
        if(id != 0){
            removeObjectById(id);
        }
    }
    else if(glfwGetKey(window,GLFW_KEY_Q) == GLFW_RELEASE){
        qPressed = false;
    }

    if(glfwGetKey(window,GLFW_KEY_E) == GLFW_PRESS && !this->ePressed){
        ePressed = true;
        printf("pressed e");
//        if(id != 0){
            printf("%f %f %f\n",x,new_y,depth);
            glm::vec3 screenPos = glm::vec3(x, new_y, depth);
            glm::vec4 viewport = glm::vec4(0, 0, width, height);
            printf("%f %f %f %f\n",viewport.x,viewport.y,viewport.z,viewport.w);
            glm::vec3 worldPos = glm::unProject(screenPos, this->camera->getViewMatrix(), this->camera->getProjectionMatrix(), viewport);
            printf("%f %f %f\n",worldPos.x,worldPos.y,worldPos.z);
            this->createTree(worldPos,0.1f);
//        }
    }
    if(glfwGetKey(window,GLFW_KEY_E) == GLFW_RELEASE){
        ePressed = false;
//        printf("realesed\n");
    }
}

void Scene::setupComponents(int n) {
    if( this->skyboxObject != nullptr){
        this->camera->addObserver(this->skyboxObject->shaderProgram);
        this->skyboxObject->shaderProgram->sendUniformValue(0, "cube");
    }
    for (auto object: this->objects){
        object->shaderProgram->sendUniformValue(n, "lightCount");
        camera->addObserver(object->shaderProgram);
        for (int i = 0; i < lights.size(); i++) {
            lights[i]->addObserver(object->shaderProgram);
            lights[i]->id = i;
        }
    }
}

Scene *Scene::makeFinalScene(GLFWwindow *window) {
    Scene* scene = new Scene(window);
    scene->skybox = new Skybox();
    Model *modelSkybox = new Model(skycube, sizeof(skycube), false,true);
    Model* terain = new Model("../resources/models/teren/teren.obj",true,false);
    Model* building = new Model("../resources/models/building/model.obj",true,false);
    Model *zombie = new Model("../resources/models/zombie/zombie.obj", true, false);
    Model *treeModel = new Model("../resources/models/tree/tree.obj", true, false);
    Model* wallModel = new Model("../resources/models/wall/zed.obj", true, false);
    Model * lampModel = new Model("../resources/models/lamp/lamp2.fbx", true, false);
    Model * bushModel = new Model("../resources/models/bush/bush_r.obj", true, false);
    ShaderProgram* terainShader = new ShaderProgram("../resources/vertexTextures.vert","../resources/fragmentPhongLightsTextures.frag",true,true);
    ShaderProgram *shaderProgramSkybox = new ShaderProgram("../resources/vertexSkybox.vert","../resources/fragmentSkybox.frag",true,true);
    ShaderProgram* shaderProgramBuilding = new ShaderProgram("../resources/vertexTextures.vert","../resources/fragmentPhongLightsTextures.frag",true,true);
    ShaderProgram *zombieShader = new ShaderProgram("../resources/vertexTextures.vert","../resources/fragmentPhongLightsTextures.frag", true, true);
    ShaderProgram *treeShader = new ShaderProgram("../resources/vertexTextures.vert","../resources/fragmentPhongLightsTextures.frag", true, true);
    ShaderProgram *wallShader = new ShaderProgram("../resources/vertexTextures.vert","../resources/fragmentPhongLightsTextures.frag", true, true);
    ShaderProgram *lampShader = new ShaderProgram("../resources/vertexTextures.vert","../resources/fragmentPhongLightsTextures.frag", true, true);
    ShaderProgram *bushShader = new ShaderProgram("../resources/vertexTextures.vert","../resources/fragmentPhongLightsTextures.frag", true, true);
    Material *terainMaterial = new Material(1.f, 1.f, 1.f, "../resources/models/teren/grass.png");
    Material *buildingMaterial = new Material(1.f, 1.f, 1.f, "../resources/models/building/test.png");
    Material *zombieMaterial = new Material(1.f, 1.f, 1.f, "../resources/models/zombie/zombie.png");
    Material *treeMaterial = new Material(1.f, 1.f, 1.f, "../resources/models/tree/tree.png");
    Material *wallMaterial = new Material(1.f, 1.f, 1.f, "../resources/models/wall/bake.png");
    Material *lampMaterial = new Material(1.f, 1.f, 1.f, "../resources/models/lamp/lampText.png");
    Material *bushMaterial = new Material(1.f,1.f,1.f, "../resources/models/bush/bush.png");
    DrawableObject *objectSkybox = new DrawableObject(modelSkybox, shaderProgramSkybox);
    printf("skybox: %d\n", objectSkybox->id);
    scene->skyboxObject = objectSkybox;

    DrawableObject* terainObject = new DrawableObject(terain, terainShader, terainMaterial);
    scene->addObject(terainObject);

    DrawableObject* objectBuilding = new DrawableObject(building, shaderProgramBuilding, buildingMaterial);
    objectBuilding->transformationComposite->addTransformation(new Scale(0.65f, 0.65f, 0.65f));
    objectBuilding->transformationComposite->apply();
    scene->addObject(objectBuilding);

    DrawableObject *objectZombie = new DrawableObject(zombie, zombieShader, zombieMaterial);
    objectZombie->transformationComposite->addTransformation(new Translation(-1.5f, 0.f, 10.f));
    objectZombie->transformationComposite->addTransformation(new Rotate(150.f, 0.f, 1.f, 0.f));
    objectZombie->transformationComposite->apply();
    scene->addObject(objectZombie);

    DrawableObject* objectZombie2 = new DrawableObject(zombie, zombieShader, zombieMaterial);
    objectZombie2->transformationComposite->addTransformation(new Translation(1.5f, 0.f, 10.f));
    objectZombie2->transformationComposite->addTransformation(new Rotate(230.f, 0.f, 1.f, 0.f));
    objectZombie2->transformationComposite->apply();
    scene->addObject(objectZombie2);

    //left side
    DrawableObject* objectWall5 = new DrawableObject(wallModel, wallShader, wallMaterial);
    objectWall5->transformationComposite->addTransformation(new Translation(-3.3f, 0.f, -9.1f));
    objectWall5->transformationComposite->addTransformation(new Rotate(30.f, 0.f, 1.f, 0.f));
    objectWall5->transformationComposite->addTransformation(new Scale(0.8f, 1.0f, 1.05f));
    objectWall5->transformationComposite->apply();
    scene->addObject(objectWall5);

    DrawableObject* objectWall6 = new DrawableObject(wallModel, wallShader, wallMaterial);
    objectWall6->transformationComposite->addTransformation(new Translation(3.2f, 0.f, -9.1f));
    objectWall6->transformationComposite->addTransformation(new Rotate(-30.f, 0.f, 1.f, 0.f));
    objectWall6->transformationComposite->addTransformation(new Scale(0.8f, 1.0f, 1.05f));
    objectWall6->transformationComposite->apply();
    scene->addObject(objectWall6);

    DrawableObject* objectWall = new DrawableObject(wallModel, wallShader, wallMaterial);
    objectWall->transformationComposite->addTransformation(new Translation(-6.f, 0.f, -4.f));
    objectWall->transformationComposite->addTransformation(new Rotate(90.f, 0.f, 1.f, 0.f));
    objectWall->transformationComposite->apply();
    scene->addObject(objectWall);

    DrawableObject* objectWall2 = new DrawableObject(wallModel, wallShader, wallMaterial);
    objectWall2->transformationComposite->addTransformation(new Translation(-6.f, 0.f, 4.f));
    objectWall2->transformationComposite->addTransformation(new Rotate(90.f, 0.f, 1.f, 0.f));
    objectWall2->transformationComposite->apply();
    scene->addObject(objectWall2);

    //right side
    DrawableObject* objectWall3 = new DrawableObject(wallModel, wallShader, wallMaterial);
    objectWall3->transformationComposite->addTransformation(new Translation(6.f, 0.f, -4.f));
    objectWall3->transformationComposite->addTransformation(new Rotate(90.f, 0.f, 1.f, 0.f));
    objectWall3->transformationComposite->apply();
    scene->addObject(objectWall3);

    DrawableObject* objectWall4 = new DrawableObject(wallModel, wallShader, wallMaterial);
    objectWall4->transformationComposite->addTransformation(new Translation(6.f, 0.f, 4.f));
    objectWall4->transformationComposite->addTransformation(new Rotate(90.f, 0.f, 1.f, 0.f));
//    objectWall2->transformationComposite->addTransformation(new Scale(0.65f, 0.65f, 2.6f));
    objectWall4->transformationComposite->apply();
    scene->addObject(objectWall4);

    DrawableObject* objectLamp = new DrawableObject(lampModel, lampShader, lampMaterial);
    objectLamp->transformationComposite->addTransformation(new Translation(3.5f, 0.f, 8.f));
    objectLamp->transformationComposite->addTransformation(new Rotate(270.f, 1.f, 0.f, 0.f));
    objectLamp->transformationComposite->addTransformation(new Rotate(180.f, 0.f, 0.f, 1.f));
    objectLamp->transformationComposite->apply();

    scene->addObject(objectLamp);
    PointLight* pointLight = new PointLight(glm::vec3(3.5f, 2.f, 8.f), glm::vec3(1.f), glm::vec3(0.9f), 1.f, 0.09f,0.032f);
    scene->lights.push_back(pointLight);

    DrawableObject* objectLamp2 = new DrawableObject(lampModel, lampShader, lampMaterial);
    objectLamp2->transformationComposite->addTransformation(new Translation(-3.5f, 0.f, 17.f));
    objectLamp2->transformationComposite->addTransformation(new Rotate(270.f, 1.f, 0.f, 0.f));
    objectLamp2->transformationComposite->addTransformation(new Rotate(40.f, 0.f, 0.f, 1.f));
    objectLamp2->transformationComposite->apply();
    scene->addObject(objectLamp2);
    PointLight* pointLight2 = new PointLight(glm::vec3(-3.5f, 0.f, 17.f), glm::vec3(1.f), glm::vec3(0.9f), 1.f, 0.09f,0.032f);
    scene->lights.push_back(pointLight2);

    float offsetX = -2.f;
    for(int i = 0; i < 5; i++){
        DrawableObject* objectTree = new DrawableObject(treeModel, treeShader, treeMaterial);
        objectTree->transformationComposite->addTransformation(new Translation(-3.5f + offsetX, 0.f, 14.f));
        objectTree->transformationComposite->addTransformation(new Scale(0.12f, 0.12f, 0.12f));
        objectTree->transformationComposite->apply();
        scene->addObject(objectTree);

//        DrawableObject* objectTree2 = new DrawableObject(treeModel, treeShader, treeMaterial);
//        objectTree2->transformationComposite->addTransformation(new Translation(- 3.5f + offsetX, 0.f, 17.f));
//        objectTree2->transformationComposite->addTransformation(new Scale(0.12f, 0.12f, 0.12f));
//        objectTree2->transformationComposite->apply();
//        scene->addObject(objectTree);

        DrawableObject* zombieObject = new DrawableObject(zombie, zombieShader, zombieMaterial);
        zombieObject->transformationComposite->addTransformation(new Translation(- 3.5f + offsetX, 0.f, 17.f));
        zombieObject->transformationComposite->addTransformation(new Rotate(180.f, 0.f, 1.f, 0.f));
        zombieObject->transformationComposite->apply();
        scene->addObject(zombieObject);

        DrawableObject* objectTree3 = new DrawableObject(treeModel, treeShader, treeMaterial);
        objectTree3->transformationComposite->addTransformation(new Translation(- 3.5f + offsetX, 0.f, 20.f));
        objectTree3->transformationComposite->addTransformation(new Scale(0.12f, 0.12f, 0.12f));
        objectTree3->transformationComposite->apply();
        scene->addObject(objectTree3);

        DrawableObject* objectTree4 = new DrawableObject(treeModel, treeShader, treeMaterial);
        objectTree4->transformationComposite->addTransformation(new Translation(- 3.5f + offsetX, 0.f, 23.f));
        objectTree4->transformationComposite->addTransformation(new Scale(0.12f, 0.12f, 0.12f));
        objectTree4->transformationComposite->apply();
        scene->addObject(objectTree4);

        offsetX += 3.f;
    }
//    DrawableObject * bushObject = new DrawableObject(bushModel, bushShader, bushMaterial);
//    bushObject->transformationComposite->addTransformation(new Translation(0.f,5.f,12.f));
//    bushObject->transformationComposite->apply();
//    scene->addObject(bushObject);

    Spotlight *spotlight = new Spotlight(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f), glm::vec3(0.05f), glm::vec3(0.f),
                                         glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.f)));
    scene->lights.push_back(spotlight);

    Light* dirLight = new DirLight(glm::vec3(0.f, 5.f, 0.f), glm::vec3(0.1f), glm::vec3(0.1f),
                                   glm::vec3(0.0f, -1.0f, 0.0f));
    scene->lights.push_back(dirLight);


    scene->setupComponents(4);
    return scene;

}




