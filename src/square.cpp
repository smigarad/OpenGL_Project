#include "square.h"

Square::Square(float* points, int pointsCount) : Model(points, pointsCount)
{
}

Square::~Square()
{
}

void Square::draw()
{
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

