#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H
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

#include "shaderProgram.h"
#include "model.h"
#include "transformationComposite.h"
class DrawableObject
{
private:

    Model* model;
    ShaderProgram *shaderProgram;
public:

    TransformationComposite* transformationComposite;
    
    DrawableObject(float* points, int pointsCount, const char* vertex_shader, const char* fragment_shader);
    DrawableObject(Model* model, ShaderProgram* shaderProgram);
    DrawableObject(Model* model, const char* vertex_shader, const char* fragment_shader);
    DrawableObject(Model* model);
    ~DrawableObject();
    void draw();
    // void draw(glm::mat4 perspective, glm::mat4 view);
    ShaderProgram* GetShaderProgramId();
    //poznamky
    //bude mit 1 mdel, jeden shader a jednu transforaci
};

#endif // DRAWABLE_OBJECT_H