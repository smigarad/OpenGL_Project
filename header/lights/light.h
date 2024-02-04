#ifndef H_LIGHT
#define H_LIGHT

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
#include <vector>
// Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>
#include "../subject.h"
#include <algorithm>

enum LightType
{
    DIRECTIONAL,
    POINT,
    SPOTLIGHT
};

class Light : public Subject
{
    private:
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 ambient;

    float constant;
    float linear;
    float quadratic;
    float shininess;

    public:
    Light(glm::vec3 position, glm::vec3 color, glm::vec3 ambient);
    LightType type;
    int id;
    ~Light();

    glm::vec3 getPosition();
    glm::vec3 getColor();
    glm::vec3 getAmbient();
    float getConstant();
    float getLinear();
    float getQuadratic();
    float getShininess();
    void setPosition(glm::vec3 position);
    void setColor(glm::vec3 color);
    void setAmbient(glm::vec3 ambient);
    void setConstant(float constant);
    void setLinear(float linear);
    void setQuadratic(float quadratic);
    void setShininess(float shininess);
};
#endif // H_LIGHT