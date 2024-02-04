#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "drawableObject.h"
#include "shaderProgram.h"
#include "transformation.h"
#include "transformationComposite.h"
#include "rotate.h"
#include "translation.h"
#include "scale.h"
#include "camera.h"
#include "subject.h"
#include "observer.h"
#include "shaderProgram.h"

//models_h
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "plain.h"
#include "sphere.h"
#include "bushes.h"
#include "tree.h"
#include "skycube.h"

#include "time.h"
#include "lights/light.h"
#include "lights/pointLight.h"
#include "lights/dirLight.h"
#include "lights/spotlight.h"

#include "material.h"
#include "skybox.h"

class Scene
{
private:
    GLFWwindow *window;
    float planet1RotationSpeed;
    float planet2RotationSpeed;
    float planet3RotationSpeed;
    float planet4RotationSpeed;
    float planet5RotationSpeed;
    float planet6RotationSpeed;
    float planet7RotationSpeed;
    float planet8RotationSpeed;
    bool qPressed;
    bool ePressed;
public:
    DrawableObject* skyboxObject;
    Skybox* skybox;
    Camera *camera;
    Light *light;
    std::vector<Light*>lights;
    std::vector<DrawableObject *> objects;
    Scene(GLFWwindow *window);
    ~Scene();
    void addObject(DrawableObject *object);
    void createTree(glm::vec3 position, float scale);
    void removeObjectById(int id);
    void handleInput();
    void draw();
    void update(glm::mat4 projection);
    void setupComponents(int n);
//    void updateLightsShaders();
    static Scene* makeSceneLightTest(GLFWwindow *window);
    static Scene* makeScenePhongTest(GLFWwindow *window);
    static Scene* makeSceneSolarSystem(GLFWwindow *window);
    static Scene* makeSceneForest(GLFWwindow * window);
    static Scene* makeSceneTextureAndSkybox(GLFWwindow * window);
    static Scene* makeSceneModifiedPhong(GLFWwindow * window);
    static Scene* makeSceneModifiedLights(GLFWwindow * window);
    static Scene* makeFinalScene(GLFWwindow* window);
    void rotatePlanets();



};

#endif // SCENE_H