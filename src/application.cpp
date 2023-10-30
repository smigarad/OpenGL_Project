#include "application.h"

application::application() {
}

void application::init() {
    glfwSetErrorCallback(Controller::error_callback);

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    // inicializace konkretni verze
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //

    window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

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
    glfwSetKeyCallback(window, Controller::key_callback);

    // glfwSetCursorPosCallback(window, this->camera->ProcessMouse);

    glfwSetMouseButtonCallback(window, Controller::button_callback);

    glfwSetWindowFocusCallback(window, Controller::window_focus_callback);

    glfwSetWindowIconifyCallback(window, Controller::window_iconify_callback);

    glfwSetWindowSizeCallback(window, Controller::window_size_callback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glEnable(GL_DEPTH_TEST);
}

void application::run() {
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // musi byt zde kvuli okna
    glfwSetWindowUserPointer(window, &projection);
    this->key = 1;
    while (!glfwWindowShouldClose(window)) {
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->showCurrentScene();
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
//        case 4:
//            this->scene1 = this->scenes[3];
//            break;
        case 5:
            this->scene1 = this->scenes[3];
            break;
        default:
            break;
    }

}
void application::createScenes() {
    this->scenes.push_back(Scene::makeSceneLightTest(this->window));
    this->scenes.push_back(Scene::makeScenePhongTest(this->window));
    this->scenes.push_back(Scene::makeSceneSolarSystem(this->window));
    //this->scenes.push_back(Scene::makeSceneForest(this->window));
    this->scenes.push_back(Scene::makeSceneModifiedPhong(this->window));
}

application::~application() {
    for(auto scene : this->scenes)
        delete scene;
}