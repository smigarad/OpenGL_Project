#ifndef SHADER_H
#define SHADER_H

// include GLEW
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
#include <iostream>
#include <string.h> 
#include <fstream>
#include <sstream>

using namespace std;
class Shader
{
private:
    GLuint shaderID;


public:
    Shader(const char* source, GLenum shaderType);
    ~Shader();  
    GLuint GetShaderID();
    static Shader* loadFile(const char *fname,GLenum shaderType);

};

#endif // SHADER_H