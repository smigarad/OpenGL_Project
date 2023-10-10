#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/vec3.hpp>                 // glm::vec3
#include <glm/vec4.hpp>                 // glm::vec4
#include <glm/mat4x4.hpp>               // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>         // glm::value_ptr
#include <vector>
// Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>


class Model
{
private:

protected:
    void createVAO();
    void createVBO();
    GLuint VAO = 0;
    GLuint VBO = 0;
    const float *points;
    int pointsCount;
public:
    Model(const float *points, int pointsCount);
    ~Model();
    virtual void draw();
};

#endif // "MODEL_H"
