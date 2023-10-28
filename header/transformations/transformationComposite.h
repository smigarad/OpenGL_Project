#ifndef TRANSFORMATIONCOMPOSITE_H
#define TRANSFORMATIONCOMPOSITE_H

#include "transformation.h"
#include <typeinfo>
class TransformationComposite : public Transformation
{
private:
    std::vector<Transformation*> transformations;
    glm::mat4 model;
public:
    TransformationComposite();
    void addTransformation(Transformation* transformation);
    ~TransformationComposite() override;
    glm::mat4 getModelMatrix() override;
    void apply() override;
    void removeTransformation(Transformation* transformation);
    void reset();
};

#endif // TRANSFORMATIONCOMPOSITE_H
