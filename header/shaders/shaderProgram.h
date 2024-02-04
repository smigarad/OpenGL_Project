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
#include "../lights/light.h"
#include "../observer.h"
#include "../material.h"
#include "../lights/pointLight.h"
#include "../lights/dirLight.h"
#include "../lights/spotlight.h"
class Light;
class PointLight;
class DirLight;
class Spotlight;
class Camera;
class ShaderProgram : public Observer
{
private:
    GLuint shaderProgramID;
    VertexShader *vertexShader;
    FragmentShader *fragmentShader;

public:
    ShaderProgram(VertexShader *vertexShader, FragmentShader *fragmentShader);
    ShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource, bool isFile = true, bool texture = false);
    ShaderProgram();
    ~ShaderProgram();
    void createDefaultShaders();
    void compile();
    void use(glm::mat4 model,Material* material, glm::vec3 color);
    void sendUniformValue(glm::mat4 matrix, const std::string& name) const;
    void sendUniformValue(glm::mat3 matrix, const std::string& name) const;
    void sendUniformValue(glm::vec3 vector, const std::string& name) const;
    void sendUniformValue(glm::vec4 vector, const std::string& name) const;
    void sendUniformValue(float fn, const std::string &name) const;
    void sendUniformValue(int fn, const std::string &name) const;
    void sendUniformValue(unsigned int fn, const std::string &name) const;
    // void use(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
    void use(GLint shaderProgramID);
    void notify(Subject *subject) override;
};

#endif