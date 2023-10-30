#ifndef APPLICATION_H
#define APPLICATION_H
// include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/vec3.hpp>                 // glm::vec3
#include <glm/vec4.hpp>                 // glm::vec4
#include <glm/mat4x4.hpp>               // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>         // glm::value_ptr
#include <vector>
// Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>

#include "scene.h"
#include "controller.h"


//shaders

class application
{
private:
    GLFWwindow *window;
    Scene *scene1;
    std::vector<Scene*>scenes;
    int key;

    void showCurrentScene();
public:
    void init();
    void run();
    void createScenes();
    application();
    ~application();
};

#endif // APPLICATION_H