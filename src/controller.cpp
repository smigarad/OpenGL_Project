#include"controller.h"


void Controller::error_callback(int error, const char* description)
{ fputs(description, stderr); }

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
//    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Controller::window_focus_callback(GLFWwindow *window,int focused) { printf("window_focus_callback \n"); }

void Controller::window_iconify_callback(GLFWwindow *window,int iconified) { printf("window_iconify_callback \n"); }

void Controller::window_size_callback(GLFWwindow *window,int width, int height)
{
    this->width = width;
    this->height = height;
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);

    glm::mat4 *projection = (glm::mat4*)glfwGetWindowUserPointer(window);
    *projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 1000.0f);
}

void Controller::cursor_callback(GLFWwindow *window, double x, double y) {
    this->x = x;
    this->y = y;

    printf("cursor_callback %f, %f \n", x, y);
    glfwGetCursorPos(window, &x, &y);
    printf("cursor_callback %f, %f \n", x, y);
}

void Controller::button_callback(GLFWwindow *window,int button, int action, int mode)
{
    if (action == GLFW_PRESS) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
//        double x, y;
//        glfwGetCursorPos(window, &x, &y);
        printf("%d, %d\n", x, y);
        GLbyte color[4];
        GLfloat depth;
        GLuint index; // identifikace tìlesa
        int newy = height - y - 10;
        glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
        printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
    }
}

void Controller::error_callback_static(int error, const char *description) {
    if (instance) {
        instance->error_callback(error, description);
    }
}

void Controller::key_callback_static(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (instance) {
        instance->key_callback(window, key, scancode, action, mods);
    }
}

void Controller::window_focus_callback_static(GLFWwindow *window, int focused) {
    if (instance) {
        instance->window_focus_callback(window, focused);
    }
}

void Controller::window_iconify_callback_static(GLFWwindow *window, int iconified) {
    if (instance) {
        instance->window_iconify_callback(window, iconified);
    }
}

void Controller::window_size_callback_static(GLFWwindow *window, int width, int height) {
    if (instance) {
        instance->window_size_callback(window, width, height);
    }
}

void Controller::cursor_callback_static(GLFWwindow *window, double x, double y) {
    if (instance) {
        instance->cursor_callback(window, x, y);
    }
}

void Controller::button_callback_static(GLFWwindow *window, int button, int action, int mode) {
    if (instance) {
        instance->button_callback(window, button, action, mode);
    }
}
Controller::Controller() {
    this->instance = this;
    this->x = 0;
    this->y = 0;
    this->height = 0;
    this->width = 0;
}

Controller *Controller::instance = NULL;
