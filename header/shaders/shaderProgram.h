#ifndef H_SHADERPROGRAM
#define H_SHADERPROGRAM

#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/vec3.hpp>                 // glm::vec3
#include <glm/vec4.hpp>                 // glm::vec4
#include <glm/mat4x4.hpp>               // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>         // glm::value_ptr

// Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>

#include "vertexShader.h"
#include "fragmentShader.h"
#include "../camera.h"
#include "../light.h"
#include "../observer.h"

class Light;
class Camera;
class ShaderProgram : public Observer
{
private:
    GLuint shaderProgramID;
    VertexShader *vertexShader;
    FragmentShader *fragmentShader;

public:
    Camera *camera;
    ShaderProgram(VertexShader *vertexShader, FragmentShader *fragmentShader);
    ShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource);
    ShaderProgram();
    ~ShaderProgram();
    void createDefaultShaders();
    void compile();
    void use(glm::mat4 model);
    // void use(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
    void unuse();
    GLuint GetVertexShaderID();
    void notify(Subject *subject) override;
};

#endif