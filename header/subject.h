#ifndef SUBJECT_H
#define SUBJECT_H
// include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/vec3.hpp>                 // glm::vec3
#include <glm/vec4.hpp>                 // glm::vec4
#include <glm/mat4x4.hpp>               // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>         // glm::value_ptr
#include <vector>
// Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include "observer.h"
class Subject
{
protected:
    std::vector<Observer*> observers;
public:
    Subject();
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    virtual void notifyObservers();
    std::vector<Observer*> getObservers();
    ~Subject();
};
#endif // SUBJECT_H