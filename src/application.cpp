#include "application.h"

application::application() {
    this->width = 1600;
    this->height = 900;
    this->controller = new Controller();
}

void application::init() {
    glfwSetErrorCallback(controller->error_callback_static);

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    // inicializace konkretni verze
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //

    window = glfwCreateWindow(width, height, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetWindowSizeCallback(window, controller->window_size_callback_static);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }


    // get version info
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    // Sets the key callback
    glfwSetKeyCallback(window, Controller::key_callback_static);

    // glfwSetCursorPosCallback(window, this->camera->ProcessMouse);

//    glfwSetMouseButtonCallback(window, Controller::button_callback_static);

    glfwSetWindowFocusCallback(window, Controller::window_focus_callback_static);

    glfwSetWindowIconifyCallback(window, Controller::window_iconify_callback_static);



    glfwGetFramebufferSize(window, &this->width, &this->height);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void application::run() {
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f); // musi byt zde kvuli okna
    glfwSetWindowUserPointer(window, &projection);
    this->key = 1;
    while (!glfwWindowShouldClose(window)) {
        // clear color and depth buffer
//        glClearStencil(0);
        this->showCurrentScene();
        this->scene1->handleInput();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        this->scene1.skybox->draw(projection);
        this->scene1->update(projection);
        //  update other events like input handling
        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(this->window);
    }
    glfwDestroyWindow(this->window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void application::showCurrentScene(){
    //light test
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        key = 1;
    //phong
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        key = 2;
    //planets
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        key = 3;
    //forest
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        key = 4;
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        key = 5;
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        key = 6;


    switch (key) {
        case 1:
            this->scene1 = this->scenes[0];
            break;
        case 2:
            this->scene1 = this->scenes[1];
            break;
        case 3:
            this->scene1 = this->scenes[2];
            this->scene1->rotatePlanets();
            break;
        case 4:
            this->scene1 = this->scenes[3];
            break;
        case 5:
            this->scene1 = this->scenes[4];
            break;
        case 6:
            this->scene1 = this->scenes[5];
            break;
        default:
            break;
    }

}
void application::createScenes() {
    this->scenes.push_back(Scene::makeSceneLightTest(this->window));
    this->scenes.push_back(Scene::makeScenePhongTest(this->window));
    this->scenes.push_back(Scene::makeSceneSolarSystem(this->window));
    this->scenes.push_back(Scene::makeSceneModifiedLights(this->window));
    this->scenes.push_back(Scene::makeSceneModifiedPhong(this->window));
    this->scenes.push_back(Scene::makeFinalScene(this->window));
}

application::~application() {
    for(auto scene : this->scenes)
        delete scene;
    delete this->controller;
}

application::application(int width, int height) {
    this->width = width;
    this->height = height;
    this->controller = new Controller();
}
