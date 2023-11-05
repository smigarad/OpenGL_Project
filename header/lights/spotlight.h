//
// Created by radek on 5.11.23.
//

#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "light.h"
class Spotlight : public Light
{
    private:

    public:
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;
    Spotlight(glm::vec3 position, glm::vec3 color, glm::vec3 ambient, glm::vec3 direction, float cutOff, float outerCutOff);
    ~Spotlight();
};
#endif //ZPG_SPOTLIGHT_H
