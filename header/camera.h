#ifndef CAMERA_H
#define CAMERA_H
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
#include "shader.h"
#include "subject.h"
#include <algorithm>
class Shader;
class Camera : public Subject
{
private:
    /**/
    glm::mat4 projectionMatrix;
    // Camera matrix
    glm::mat4 viewMatrix;
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 modelMatrix;

    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;

    Shader *shader;
    float yaw;
    float pitch;
    float cameraSpeed;
    float deltaTime;
    float lastFrame;

    double xpos;
    double ypos;
    float lastX;
    float lastY;
    bool firstMouse;
    GLFWwindow *window;

public:
    Camera();
    // Camera(Shader *shader);
    ~Camera();
    glm::mat4 getProjection();
    glm::mat4 getView();
    glm::mat4 getModel();
    glm::mat4 getCamera();
    void processKeyboard(GLFWwindow *window);
    void processMouse(GLFWwindow *window);
    void attachShader(Shader *shader);
    void detachShader(Shader *shader);
    void notifyObservers() override;
    void update(GLFWwindow *window);
};

#endif // CAMERA_H