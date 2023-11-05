#include "model.h"

Model::Model(const float *points, int pointsCount)
{
    this->pointsCount = pointsCount;
    this->points = points;
    this->createVBO();
    this->createVAO();
}

Model::~Model()
{
    glDeleteBuffers(1, &this->VBO);
    glDeleteVertexArrays(1, &this->VAO);
}
void Model::createVAO()
{
    this->VAO = 0;
    glGenVertexArrays(1, &this->VAO);   // generate the VAO
    glBindVertexArray(this->VAO);       // bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO); // bind the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL); // set the vertex attributes

    glEnableVertexAttribArray(1); //enable vertex attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)12); // set the vertex attributes
}

void Model::createVBO()
{
    this->VBO = 0;
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, pointsCount, this->points, GL_STATIC_DRAW);
}

void Model::draw()
{
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->pointsCount / 3 / sizeof(float));
}