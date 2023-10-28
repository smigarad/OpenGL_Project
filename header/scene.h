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
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "plain.h"
#include "sphere.h"
#include "light.h"

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

public:
    Camera *camera;
    Light *light;
    std::vector<DrawableObject *> objects;
    Scene(GLFWwindow *window);
    ~Scene();
    Scene(const char *vertex_shader, const char *fragment_shader);
    void addObject(DrawableObject *object);
    void draw();
    void update(glm::mat4 projection);
    static Scene* makeScene1(GLFWwindow *window);
    static Scene* makeScene2(GLFWwindow *window);
    static Scene* makeSceneSolarSystem(GLFWwindow *window);

    void transformObjects(std::vector<Transformation*> transformations);
    void transformObject(DrawableObject* object,std::vector<Transformation*> transformations);
    void transformObject(DrawableObject *object, Transformation *transformation);

    void rotatePlanets();



};

#endif // SCENE_H