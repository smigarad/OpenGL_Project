#include "transformationComposite.h"

TransformationComposite::TransformationComposite()
{
    this->model = glm::mat4(1.0f);
    this->transformations = std::vector<Transformation*>();
}

TransformationComposite::~TransformationComposite()
{
}

glm::mat4 TransformationComposite::getModelMatrix()
{
    return this->model;
}

void TransformationComposite::apply()
{
    for (auto transformation : transformations)
    {
        transformation->apply();
        this->model = transformation->getModelMatrix() * this->model;
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

