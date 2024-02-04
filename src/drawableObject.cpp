#include "drawableObject.h"

unsigned int DrawableObject::idCounter = 0;
DrawableObject::DrawableObject(float* points, int pointsCount, const char* vertex_shader, const char* fragment_shader, glm::vec3 color){
    this->model = new Model(points, pointsCount);
    this->shaderProgram = new ShaderProgram(vertex_shader, fragment_shader);
    this->transformationComposite = new TransformationComposite();
    this->material = nullptr;
    this->color = color;
    this->id = ++idCounter;
}

DrawableObject::~DrawableObject(){
    delete this->model;
    delete this->shaderProgram;
    delete this->material;
    delete this->transformationComposite;
}

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram, glm::vec3 color){
    this->model = model;
    this->shaderProgram = shaderProgram;
    this->transformationComposite = new TransformationComposite();
    this->material = nullptr;
    this->color = color;
    this->id = ++idCounter;
}

DrawableObject::DrawableObject(Model* model, const char* vertex_shader, const char* fragment_shader, glm::vec3 color){
    this->model = model;
    this->shaderProgram = new ShaderProgram(vertex_shader, fragment_shader);
    this->transformationComposite = new TransformationComposite();
    this->material = nullptr;
    this->color = color;
    this->id = ++idCounter;

}

DrawableObject::DrawableObject(Model *model)
{
    this->model = model;
    this->shaderProgram = new ShaderProgram();
    this->transformationComposite = new TransformationComposite();
    this->material = nullptr;
    this->color = glm::vec3(1.0f, 1.0f, 1.0f);
    this->id = ++idCounter;
}

DrawableObject::DrawableObject(Model *model, ShaderProgram *shaderProgram, Material *material, glm::vec3 color) {
    this->model = model;
    this->shaderProgram = shaderProgram;
    this->transformationComposite = new TransformationComposite();
    this->material = material;
    this->color = color;
    this->id = ++idCounter;
}

void DrawableObject::setMaterial(Material *material) {
    this->material = material;
}

void DrawableObject::setTransformationComposite(TransformationComposite *transformationComposite) {
    delete this->transformationComposite;
    this->transformationComposite = transformationComposite;
}

void DrawableObject::draw(){
    if(this->model->curve){
        glm::vec4 par = glm::vec4(this->model->t,this->model->t,this->model->t,1.0f);
        glm::vec3 p = par * this->model->A * glm::transpose(this->model->B);
        this->model->M = glm::translate(glm::mat4(1.0f), p);
        this->shaderProgram->use(this->model->M ,this->material, this->color);
        if (this->model->t >= 1.0f || this->model->t <= 0.0f){
            this->model->alpha *= -1;
        }
        this->model->t += this->model->alpha;
//        this->model->B.
    }
    else
        this->shaderProgram->use(this->transformationComposite->getModelMatrix(),this->material, this->color);

    this->model->bind();
    if(this->material != nullptr){
        this->material->bind();
    }
//    printf("id: %d\n", this->id);
    glStencilFunc(GL_ALWAYS, this->id, 0xFF);
    this->model->draw();
}
