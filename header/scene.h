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
public:
    Camera *camera;
    Light *light;
    std::vector<DrawableObject *> objects;
    std::vector<ShaderProgram *> shaderPrograms;
    Scene(GLFWwindow *window);
    ~Scene();
    Scene(const char *vertex_shader, const char *fragment_shader);
    void addObject(DrawableObject *object);
    void draw();
    void update();
    // void draw(glm::mat4 perspective, glm::mat4 view);
    static Scene* makeScene1(GLFWwindow *window);
    static Scene* makeScene2(GLFWwindow *window);
    static Scene* makeScene3(GLFWwindow *window);

};

#endif // SCENE_H