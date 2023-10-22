#ifndef SCALE_H
#define SCALE_H

#include "transformation.h"

class Scale : public Transformation
{
private:
    float x;
    float y;
    float z;
    glm::mat4 model;
public:
    Scale(float x, float y, float z);
    ~Scale() override;
    glm::mat4 getModelMatrix() override;
    void apply() override;
};

#endif // SCALE_H