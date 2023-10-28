#include "camera.h"
#include "shader.h"
Camera::Camera() : Subject()
{
    this->projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    this->viewMatrix = glm::lookAt(
        glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
        glm::vec3(0, 0, 0),    // and looks at the origin
        glm::vec3(0, 1, 0)     // Head is up (set to 0,-1,0 to look upside-down)
    );
    this->modelMatrix = glm::mat4(1.0f);

    this->eye = glm::vec3(0.0f, 0.0f, 3.0f);
    this->target = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);

    this->yaw = -90.f;
    this->pitch = 0.0f;
    this->cameraSpeed = 2.0f;
    this->deltaTime = 0.0f;
    this->lastFrame = 0.0f;

    this->lastX = 400;
    this->lastY = 300;
    this->firstMouse = true;
    this->moving = false;
    this->pressed = false;
    this->mouse_pressed = false;
    this->camera_last_x = 0;
    this->camera_last_y = 0;
    this->firstUpdate = true;
}
Camera::~Camera()
{
    delete this->shader;
}

glm::mat4 Camera::getModel()
{
    return this->modelMatrix;
}

glm::mat4 Camera::getCamera()
{
    this->viewMatrix = glm::lookAt(eye, eye + target, up);
    return this->viewMatrix;
}

void Camera::processKeyboard(GLFWwindow *window)
{
    this->deltaTime = glfwGetTime() - this->lastFrame;
    this->lastFrame = glfwGetTime();
    this->cameraSpeed = 2.0f * this->deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        this->eye += this->cameraSpeed * this->target;
        this->pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        this->eye -= this->cameraSpeed * this->target;
        this->pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        this->eye -= glm::normalize(glm::cross(this->target, this->up)) * this->cameraSpeed;
        this->pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        this->eye += glm::normalize(glm::cross(this->target, this->up)) * this->cameraSpeed;
        this->pressed = true;
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS){

        if(moving && !mouse_pressed){
            this->moving = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else if(!moving && !mouse_pressed){
            this->moving = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        pressed = true;
        mouse_pressed = true;
    }
    else{
        mouse_pressed = false;
    }
    if(this->pressed){
        this->notifyObservers();
        this->pressed = false;
    }

}

void Camera::processMouse(GLFWwindow *window)
{
    glfwGetCursorPos(window, &xpos, &ypos);
    if(this->moving){
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        this->yaw += xoffset;
        this->pitch += yoffset;
        if (this->pitch > 89.0f)
        {
            this->pitch = 89.0f;
        }
        if (this->pitch < -89.0f)
        {
            this->pitch = -89.0f;
        }

        target.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        target.y = sin(glm::radians(this->pitch));
        target.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

        if(lastX != this->camera_last_x || lastY != this->camera_last_y)
        {
            this->notifyObservers();
            printf("xpos: %f, ypos: %f\n", xpos, ypos);
            this->camera_last_x = lastX;
            this->camera_last_y = lastY;

        }

    }

}

void Camera::notifyObservers()
{
    for(auto observer : this->observers)
    {
        observer->notify(this);
    }
}

void Camera::update(GLFWwindow *window,glm::mat4 perspective)
{
    this->projectionMatrix = perspective;
    this->processKeyboard(window);
    this->processMouse(window);

    if(this->firstUpdate){
        this->firstUpdate = false;
        this->notifyObservers();
    }
}

glm::mat4 Camera::getView()
{
    return this->viewMatrix;
}

glm::mat4 Camera::getProjection()
{
    return this->projectionMatrix;
}

glm::vec3 Camera::getEye() {
    return this->eye;
}

