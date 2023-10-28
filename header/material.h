//
// Created by radek on 27.10.23.
//

#ifndef MATERIAL_H
#define MATERIAL_H

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

class Material{
private:
public:
    //(r_a, r_d, r_s),
    float r_a;
    float r_d;
    float r_s;
    Material(float r_a,float r_d, float r_s);

};
#endif //MATERIAL_H
