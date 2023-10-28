#include "application.h"

application::application()
{
}

void application::init()
{
    glfwSetErrorCallback(Controller::error_callback);

    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    // inicializace konkretni verze
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE); //

    window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!window)
    {
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
    this->scene1 = Scene::makeSceneSolarSystem(this->window);


}

void application::run()
{
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // musi byt zde kvuli okna
    glfwSetWindowUserPointer(window, &projection);
    std::vector<DrawableObject*> objects = this->scene1->objects;

    Rotate *rotation = new Rotate(glm::radians(45.0f), 0.0f, 0.0f, 1.0f);
    Translation *translation_position = new Translation(0.0f, 1.0f, 0.0f);
    Translation *translation_start = new Translation(0.0f, -1.0f, 0.0f);
    // 0.0,0.0,0.0
    //rotate
    // 0.0,1.0,0.0


    std::vector<Transformation*> transformations = std::vector<Transformation*>{translation_start,rotation,translation_position};
    while (!glfwWindowShouldClose(window))
    {
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // draw triangles

        this->scene1->update(projection);
//        for(auto object : scene1->objects){
//            object->transformationComposite->apply();
//        }
         this->scene1->rotatePlanets();
        //this->scene1->transformObject(this->scene1->objects[0],transformations);

        //  update other events like input handling
        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(this->window);
    }
    delete rotation;
    glfwDestroyWindow(this->window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void application::createShaders()
{
}

void application::createModels()
{
}

void application::createScene()
{
}

application::~application()
{
    delete scene1;
}