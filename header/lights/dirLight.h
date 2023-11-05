//
// Created by radek on 3.11.23.
//

#ifndef DIRLIGHT_H
#define DIRLIGHT_H

#include "light.h"
class DirLight : public Light
{
private:
public:
    glm::vec3 direction;
    DirLight(glm::vec3 position, glm::vec3 color, glm::vec3 ambient, glm::vec3 direction);
    ~DirLight();
};
#endif //ZPG_DIRLIGHT_H
