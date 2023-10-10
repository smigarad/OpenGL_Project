#include "triangle.h"

Triangle::Triangle(float* points, int pointsCount) : Model(points, pointsCount)
{
}


Triangle::~Triangle()
{
    
}

void Triangle::draw()
{
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
