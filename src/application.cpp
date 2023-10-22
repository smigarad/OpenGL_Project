#include "application.h"

application::application()
{
}

void application::init()
{

    camera = new Camera();
    glfwSetErrorCallback(Controller::error_callback);

    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    // inicializace konkretni verze
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE); //

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
    glewInit();
    

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
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);

    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // cursor wont leave the window and will be hidden
    this->scene1 = Scene::makeScene2(this->window);
    glEnable(GL_DEPTH_TEST);
}

void application::run()
{
    while (!glfwWindowShouldClose(window))
    {
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // draw triangles
        // glm::mat4 projection = this->scene1->camera->getProjection();
        // glm::mat4 view = this->scene1->camera->getCamera();
        this->scene1->update();
        // this->scene1->draw(projection, view);
        // this->scene1->draw();
        //  update other events like input handling



        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(this->window);
    }

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

void application::createCamera()
{
    this->camera = new Camera();
}
application::~application()
{
    delete camera;
    delete scene1;
}