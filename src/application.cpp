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
    glEnable(GL_DEPTH_TEST);

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

    glfwSetCursorPosCallback(window, Controller::cursor_callback);

    glfwSetMouseButtonCallback(window, Controller::button_callback);

    glfwSetWindowFocusCallback(window, Controller::window_focus_callback);

    glfwSetWindowIconifyCallback(window, Controller::window_iconify_callback);

    glfwSetWindowSizeCallback(window, Controller::window_size_callback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);

    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
}

void application::run()
{

    while (!glfwWindowShouldClose(window))
    {
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // draw triangles
        this->scene->draw();
        // update other events like input handling
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
    const char *vertex_shader =
        "#version 330\n"
        "layout(location=0) in vec3 vp;"
        "void main () {"
        "     gl_Position = vec4 (vp, 1.0);"
        "}";

    const char *fragment_shader = "#version 330\n"
                                  "out vec4 frag_colour;"
                                  "void main () {"
                                  "     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
                                  "}";

    
    Model *model = new Model(suziSmooth, sizeof(suziSmooth));
    DrawableObject *object = new DrawableObject(model);
    this->scene = new Scene();
    this->scene->addObject(object);

    object->transformationComposite->addTransformation(new Rotate(180.0f, 0.0f, 1.0f, 0.0f));
    object->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object->transformationComposite->addTransformation(new Translation(-0.6f, 0.0f, 0.0f));
    object->transformationComposite->apply();




    Model *model2 = new Model(suziSmooth, sizeof(suziSmooth));
    DrawableObject *object2 = new DrawableObject(model2);
    this->scene->addObject(object2);

    object2->transformationComposite->addTransformation(new Rotate(160.0f, 0.0f, 1.0f, 0.0f));
    object2->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object2->transformationComposite->addTransformation(new Translation(-0.0f, 0.0f, 0.0f));
    object2->transformationComposite->apply();

 
    Model *model3 = new Model(suziSmooth, sizeof(suziSmooth));
    DrawableObject *object3 = new DrawableObject(model3);
    this->scene->addObject(object3);

    object3->transformationComposite->addTransformation(new Rotate(200.0f, 0.0f, 1.0f, 0.0f));
    object3->transformationComposite->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    object3->transformationComposite->addTransformation(new Translation(0.2f, 0.5f, 0.0f));
    object3->transformationComposite->apply();


}

void application::createCamera()
{
    this->camera = new Camera();
}
application::~application()
{
    delete camera;
    delete scene;
}