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

Scene *Scene::makeSceneLightTest(GLFWwindow *window) {
    Scene *scene = new Scene(window);
    Light *light = new Light(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0), glm::vec3(0.1f));
    scene->light = light;
    ShaderProgram *shaderProgram1 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    ShaderProgram *shaderProgram2 = new ShaderProgram("../resources/vertex_upgraded.vert","../resources/blinn.frag");
    ShaderProgram *shaderProgram3 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/lambert.frag");
    ShaderProgram *shaderProgram4 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/constant.frag");

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


Scene *Scene::makeScenePhongTest(GLFWwindow *window) {
    Scene *scene = new Scene(window);
    Light *light = new Light(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0), glm::vec3(0.1f));
    scene->light = light;
    ShaderProgram *shaderProgram1 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    ShaderProgram *shaderProgram2 = new ShaderProgram("../resources/vertex_upgraded.vert","../resources/phong.frag");
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

    TransformationComposite* venusTransformation = new TransformationComposite();
    venusTransformation->addTransformation(new Rotate(this->planet2RotationSpeed, 1.0f, 0.0f, 0.0f));
    venusTransformation->addTransformation(new Translation(2.f, 1.4f, 0.0f));
    venusTransformation->addTransformation(new Scale(0.4f, 0.4f, 0.4f));
    this->objects[2]->setTransformationComposite(venusTransformation);
    this->objects[2]->transformationComposite->apply();


    TransformationComposite* marsTransformation = new TransformationComposite();
    marsTransformation->addTransformation(new Rotate(this->planet3RotationSpeed, 0.0f, 0.0f, 1.0f));
    marsTransformation->addTransformation(new Translation(1.f, 0.5f, 0.0f));
    marsTransformation->addTransformation(new Scale(0.3f, 0.3f, 0.3f));
    this->objects[3]->setTransformationComposite(marsTransformation);
    this->objects[3]->transformationComposite->apply();

    TransformationComposite* jupiterTransformation = new TransformationComposite();
    jupiterTransformation->addTransformation(new Rotate(this->planet4RotationSpeed, 0.0f, 1.0f, 0.0f));
    jupiterTransformation->addTransformation(new Translation(3.f, 2.0f, 0.0f));
    jupiterTransformation->addTransformation(new Scale(0.5f, 0.5f, 0.5f));
    this->objects[4]->setTransformationComposite(jupiterTransformation);
    this->objects[4]->transformationComposite->apply();

    TransformationComposite* earthTransformation = new TransformationComposite();
    earthTransformation->addTransformation(new Rotate(this->planet5RotationSpeed, 0.0f, 0.0f, 1.0f));
    earthTransformation->addTransformation(new Translation(1.0f, 2.0f, 0.0f));
    earthTransformation->addTransformation(new Scale(0.3f, 0.3f, 0.3f));
    this->objects[5]->setTransformationComposite(earthTransformation);
    this->objects[5]->transformationComposite->apply();

    TransformationComposite* moonTransformation = new TransformationComposite();
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
    this->planet5RotationSpeed += 0.1f;
    this->planet6RotationSpeed += 0.2f;
}

Scene *Scene::makeSceneForest(GLFWwindow *window) {
    Scene *scene = new Scene(window);
    scene->light = new Light(glm::vec3(0.f,5.f,0.f), glm::vec3(1.f), glm::vec3(0.1f));
    ShaderProgram *floorShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/constant.frag");
    Model *floorModel = new Model(plain, sizeof(plain));
    DrawableObject *floor = new DrawableObject(floorModel, floorShader, glm::vec3(0.0f, 0.5f, 0.0f));
    floor->transformationComposite->addTransformation(new Scale(4.f, 2.f, 4.f));
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
        ShaderProgram *bushesShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/constant.frag");
        DrawableObject *bush = new DrawableObject(bushesModel, bushesShader, glm::vec3(0.0f, 0.3f, 0.0f));
        scene->addObject(bush);
        float x = (float) ((rand() % 30+ 1 ) / 10.f);
        float z = (float) ((rand() % 30 + 1 ) / 10.f);
        float scale_x = (float) ((rand() % 5 + 1 ) / 10.f);
        float scale_y = (float) ((rand() % 5 + 1 ) / 10.f);
        float scale_z = (float) ((rand() % 5 + 1 ) / 10.f);
        float angle = (float) ((rand() % 360 + 1 ) / 1.f);

        Translation* translation = new Translation(x, 0.f, z);
        Scale* scale = new Scale(scale_x, scale_y, scale_z);
        Rotate* rotate = new Rotate(angle, 0.f, 1.f, 0.f);
        bush->transformationComposite->addTransformation(rotate);
        bush->transformationComposite->addTransformation(translation);
        bush->transformationComposite->addTransformation(scale);
        bush->transformationComposite->apply();
        scene->camera->addObserver(bushesShader);
        scene->light->addObserver(bushesShader);
    }

    for (int i = 0; i < treesNumber; i++) {
        Model *treeModel = new Model(tree, sizeof(tree));
        ShaderProgram *treeShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/blinn.frag");
        DrawableObject *tree = new DrawableObject(treeModel, treeShader, glm::vec3(0.4f, 0.3f, 0.0f));
        scene->addObject(tree);
        float x = (float) ((rand() % 50 + 1 ) / 10.f);
        float z = (float) ((rand() % 50 + 1 ) / 10.f);
        float scale_x = (float) ((rand() % 3 + 1 ) / 10.f);
        float scale_y = (float) ((rand() % 3 + 1 ) / 10.f);
        float scale_z = (float) ((rand() % 3 + 1 ) / 10.f);
        float angle = (float) ((rand() % 360 + 1 ) / 1.f);
        printf("%f %f", x, z);
        Translation* translation = new Translation(x, 0.f, z);
        Scale* scale = new Scale(scale_x, scale_y, scale_z);
        Rotate* rotate = new Rotate(angle, 0.f, 1.f, 0.f);

        tree->transformationComposite->addTransformation(translation);
        tree->transformationComposite->addTransformation(rotate);
        tree->transformationComposite->addTransformation(scale);
        tree->transformationComposite->apply();
        scene->camera->addObserver(treeShader);
        scene->light->addObserver(treeShader);
    }

    for(int i = 0; i < suziFlatNumber; i++){
        Model *suziFlatModel = new Model(suziFlat, sizeof(suziFlat));
        ShaderProgram *suziFlatShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/blinn.frag");
        DrawableObject *suziFlat = new DrawableObject(suziFlatModel, suziFlatShader, glm::vec3(0.4f, 0.3f, 0.2f));
        scene->addObject(suziFlat);
        float x = (float) ((rand() % 30 + 1 ) / 10.f);
        float z = (float) ((rand() % 30 + 1 ) / 10.f);
        float scale_x = (float) ((rand() % 3 + 1 ) / 10.f);
        float scale_y = (float) ((rand() % 3 + 1 ) / 10.f);
        float scale_z = (float) ((rand() % 3 + 1 ) / 10.f);
        float angle = (float) ((rand() % 360 + 1 ) / 1.f);

        Translation* translation = new Translation(x, 0.2f, z);
        Scale* scale = new Scale(scale_x, scale_y, scale_z);
        Rotate* rotate = new Rotate(angle, 0.f, 1.f, 0.f);

        suziFlat->transformationComposite->addTransformation(rotate);
        suziFlat->transformationComposite->addTransformation(translation);
        suziFlat->transformationComposite->addTransformation(scale);
        suziFlat->transformationComposite->apply();
        scene->camera->addObserver(suziFlatShader);
        scene->light->addObserver(suziFlatShader);
    }

    for(int i = 0; i < suziSmoothNumber; i++){
        Model *suziSmoothModel = new Model(suziSmooth, sizeof(suziSmooth));
        ShaderProgram *suziSmoothShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/blinn.frag");
        DrawableObject *suziSmooth = new DrawableObject(suziSmoothModel, suziSmoothShader, glm::vec3(0.1f, 0.f, 0.8f));
        scene->addObject(suziSmooth);
        float x = (float) ((rand() % 30 + 1 ) / 10.f);
        float z = (float) ((rand() % 30 + 1 ) / 10.f);
        float scale_x = (float) ((rand() % 3 + 1 ) / 10.f);
        float scale_y = (float) ((rand() % 3 + 1 ) / 10.f);
        float scale_z = (float) ((rand() % 3 + 1 ) / 10.f);
        float angle = (float) ((rand() % 360 + 1 ) / 1.f);

        Translation* translation = new Translation(x, 0.2f, z);
        Scale* scale = new Scale(scale_x, scale_y, scale_z);
        Rotate* rotate = new Rotate(angle, 0.f, 1.f, 0.f);

        suziSmooth->transformationComposite->addTransformation(rotate);
        suziSmooth->transformationComposite->addTransformation(translation);
        suziSmooth->transformationComposite->addTransformation(scale);
        suziSmooth->transformationComposite->apply();
        scene->camera->addObserver(suziSmoothShader);
        scene->light->addObserver(suziSmoothShader);
    }

    for(int i = 0; i < spheresNumber; i++){
        Model *sphereModel = new Model(sphere, sizeof(sphere));
        ShaderProgram *sphereShader = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/blinn.frag");
        DrawableObject *sphere = new DrawableObject(sphereModel, sphereShader, glm::vec3(0.7f, 0.2f, 0.5f));
        scene->addObject(sphere);
        float x = (float) ((rand() % 30 + 1 ) / 10.f);
        float z = (float) ((rand() % 30 + 1 ) / 10.f);
        float scale_x = (float) ((rand() % 3 + 1 ) / 10.f);
        float scale_y = (float) ((rand() % 3 + 1 ) / 10.f);
        float scale_z = (float) ((rand() % 3 + 1 ) / 10.f);
        float angle = (float) ((rand() % 360 + 1 ) / 1.f);

        Translation* translation = new Translation(x, 0.2f, z);
        Scale* scale = new Scale(scale_x, scale_y, scale_z);
        Rotate* rotate = new Rotate(angle, 0.f, 1.f, 0.f);

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
    Scene* scene = new Scene(window);
    scene->light = new Light(glm::vec3(0.f), glm::vec3(1.f), glm::vec3(0.1f));
    ShaderProgram *shaderProgram1 = new ShaderProgram("../resources/vertex_upgraded.vert", "../resources/phong.frag");
    ShaderProgram *shaderProgram2 = new ShaderProgram("../resources/vertex_upgraded.vert","../resources/phong_variant.frag");

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



