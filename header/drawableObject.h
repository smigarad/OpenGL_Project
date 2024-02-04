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
#include "material.h"
class DrawableObject
{
private:

    Model* model;
    Material *material;
    glm::vec3 color;
    static unsigned int idCounter;
public:
    ShaderProgram *shaderProgram;

    TransformationComposite* transformationComposite;
    unsigned int id;
    DrawableObject(float* points, int pointsCount, const char* vertex_shader, const char* fragment_shader, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
    DrawableObject(Model* model, ShaderProgram* shaderProgram, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
    DrawableObject(Model* model, const char* vertex_shader, const char* fragment_shader, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
    DrawableObject(Model* model, ShaderProgram* shaderProgram, Material *material, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
    DrawableObject(Model* model);
    ~DrawableObject();
    void draw();
    void setMaterial(Material *material);
    void setTransformationComposite(TransformationComposite *transformationComposite);
};

#endif // DRAWABLE_OBJECT_H