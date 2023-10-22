#ifndef TRIANGLE_H
#define TRIANGLE_H
#ifndef __MODEL__
#define __MODEL__
#include "model.h"

class Triangle : public Model
{
private:


public:
    Triangle(float *points, int pointsCount);
    ~Triangle();
    void draw() override;
};

#endif // TRIANGLE_H
#endif // TRIANGLE_H