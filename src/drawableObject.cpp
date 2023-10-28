#include "drawableObject.h"

DrawableObject::DrawableObject(float* points, int pointsCount, const char* vertex_shader, const char* fragment_shader, glm::vec3 color){
    this->model = new Model(points, pointsCount);
    this->shaderProgram = new ShaderProgram(vertex_shader, fragment_shader);
    this->transformationComposite = new TransformationComposite();
    this->material = nullptr;
    this->color = color;
}

DrawableObject::~DrawableObject(){
    delete this->model;
    delete this->shaderProgram;
    delete this->material;
    delete this->transformationComposite;
}

void DrawableObject::draw(){
    this->shaderProgram->use(this->transformationComposite->getModelMatrix(),this->material, this->color);
    this->model->draw();
}

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram, glm::vec3 color){
    this->model = model;
    this->shaderProgram = shaderProgram;
    this->transformationComposite = new TransformationComposite();
    this->material = nullptr;
    this->color = color;
}

DrawableObject::DrawableObject(Model* model, const char* vertex_shader, const char* fragment_shader, glm::vec3 color){
    this->model = model;
    this->shaderProgram = new ShaderProgram(vertex_shader, fragment_shader);
    this->transformationComposite = new TransformationComposite();
    this->material = nullptr;
    this->color = color;

}

DrawableObject::DrawableObject(Model *model)
{
    this->model = model;
    this->shaderProgram = new ShaderProgram();
    this->transformationComposite = new TransformationComposite();
    this->material = nullptr;
}

void DrawableObject::setMaterial(Material *material) {
    this->material = material;
}

void DrawableObject::setTransformationComposite(TransformationComposite *transformationComposite) {
    delete this->transformationComposite;
    this->transformationComposite = transformationComposite;
}
