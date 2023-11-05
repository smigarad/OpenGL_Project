//
// Created by radek on 3.11.23.
//

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"
class PointLight : public Light
{
private:
public:
    float constant;
    float linear;
    float quadratic;
    PointLight(glm::vec3 position, glm::vec3 color, glm::vec3 ambient,float constant, float linear, float quadratic);
    PointLight(glm::vec3 position, glm::vec3 color, glm::vec3 ambient);
    ~PointLight();


};
#endif //ZPG_POINTLIGHT_H
