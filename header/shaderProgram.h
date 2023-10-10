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
class ShaderProgram
{
private:
    GLuint shaderProgramID;
    VertexShader* vertexShader;
    FragmentShader* fragmentShader;
public:
    ShaderProgram(VertexShader* vertexShader, FragmentShader* fragmentShader);
    ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
    ShaderProgram();
    ~ShaderProgram();
    void createDefaultShaders(float r, float g, float b, float a);
    void compile();
    void use(glm::mat4 model);
    void unuse();
};

#endif