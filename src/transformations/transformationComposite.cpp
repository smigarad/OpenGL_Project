#include "transformationComposite.h"

TransformationComposite::TransformationComposite()
{
    this->model = glm::mat4(1.0f);
    this->transformations = std::vector<Transformation*>();
}

TransformationComposite::~TransformationComposite()
{
    for (auto transformation : this->transformations)
    {
        delete transformation;
    }
}

glm::mat4 TransformationComposite::getModelMatrix()
{
    this->model = glm::mat4(1.f);
    for (auto transformation : this->transformations)
    {
        this->model = this->model * transformation->getModelMatrix();
    }
    return this->model;
}

void TransformationComposite::apply()
{
    for (auto transformation : transformations)
    {
        transformation->apply();
    }


}

void TransformationComposite::addTransformation(Transformation* transformation)
{
    transformations.push_back(transformation);
}

void TransformationComposite::removeTransformation(Transformation* transformation)
{
    transformations.erase(std::remove(transformations.begin(), transformations.end(), transformation), transformations.end());
}

void TransformationComposite::reset() {
    this->model = glm::mat4(1.0f);

}




