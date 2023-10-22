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

#include "drawableObject.h"
#include "triangle.h"
#include "scene.h"
#include "camera.h"
#include "controller.h"
#include "square.h"


//shaders
#include "shader.h"
#include "vertexShader.h"
#include "fragmentShader.h"
//models



//transformation
#include "transformationComposite.h"
#include "transformation.h"
#include "translation.h"
#include "rotate.h"
#include "scale.h"

class application
{
private:
    Camera *camera;
    GLFWwindow *window;
    Scene *scene1;


public:
    void init();
    void run();
    void createShaders();
    void createModels();
    void createScene();
    void createCamera();
    application(/* args */);
    ~application();
};

#endif // APPLICATION_H