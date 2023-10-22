#include "drawableObject.h"

DrawableObject::DrawableObject(float* points, int pointsCount, const char* vertex_shader, const char* fragment_shader){
    this->model = new Model(points, pointsCount);
    this->shaderProgram = new ShaderProgram(vertex_shader, fragment_shader);
    this->transformationComposite = new TransformationComposite();
}

DrawableObject::~DrawableObject(){
    delete this->model;
    delete this->shaderProgram;
}

void DrawableObject::draw(){
    this->shaderProgram->use(this->transformationComposite->getModelMatrix());
    this->model->draw();
}

// void DrawableObject::draw(glm::mat4 perspective, glm::mat4 view)
// {
    
//     this->shaderProgram->use(this->transformationComposite->getModelMatrix(),view, perspective);
//     this->model->draw();
// }

ShaderProgram* DrawableObject::GetShaderProgramId()
{
return this->shaderProgram;
}

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram){
    this->model = model;
    this->shaderProgram = shaderProgram;
    this->transformationComposite = new TransformationComposite();
}

DrawableObject::DrawableObject(Model* model, const char* vertex_shader, const char* fragment_shader){
    this->model = model;
    this->shaderProgram = new ShaderProgram(vertex_shader, fragment_shader);
    this->transformationComposite = new TransformationComposite();
}

DrawableObject::DrawableObject(Model *model)
{
    this->model = model;
    this->shaderProgram = new ShaderProgram();
    this->transformationComposite = new TransformationComposite();
}
