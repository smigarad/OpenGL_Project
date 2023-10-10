#include "model.h"

Model::Model(const float *points, int pointsCount)
{
    this->pointsCount = pointsCount;
    printf("pointsCount: %d\n", this->pointsCount);
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
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, pointsCount, this->points, GL_STATIC_DRAW);
}

void Model::draw()
{
    glBindVertexArray(this->VAO);
    printf("pointsCount: %d\n", this->pointsCount / 6 / sizeof(float));
    glDrawArrays(GL_TRIANGLES, 0, this->pointsCount / 6 / sizeof(float));
}