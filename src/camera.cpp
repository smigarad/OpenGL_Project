#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

glm::mat4 Camera::getModel()
{
    return this->Model;
}

glm::mat4 Camera::getView()
{
    return this->View;
}

glm::mat4 Camera::getProjection()
{
    return this->Projection;
}