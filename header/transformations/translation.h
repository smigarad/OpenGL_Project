#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "transformation.h"

class Translation : public Transformation
{
private:
    float x;
    float y;
    float z;
    glm::mat4 model;

public:
    Translation(float x, float y, float z);
    ~Translation() override;
    glm::mat4 getModelMatrix() override;
    void apply() override;
};

#endif // TRANSLATION_H