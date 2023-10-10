#ifndef H_SQUARE
#define H_SQUARE

#include "model.h"

class Square : public Model
{
private:
    float *points1;
    float *points2;
public:

    Square(float* points, int pointsCount);

    ~Square();
    void draw() override;
};




#endif //H_SQUARE