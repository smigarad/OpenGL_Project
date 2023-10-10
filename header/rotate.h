#ifndef ROTATE_H
#define ROTATE_H

#include "transformation.h"

class Rotate : public Transformation
{
private:
    float angle;
    float x;
    float y;
    float z;
    glm::mat4 model;

public:
    Rotate(float angle, float x, float y, float z);
    ~Rotate() override;
    glm::mat4 getModelMatrix() override;
    void apply() override;
};

#endif // ROTATE_H