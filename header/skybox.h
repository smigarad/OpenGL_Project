//
// Created by radek on 12/10/23.
//

#ifndef SKYBOX_H
#define SKYBOX_H
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
class Skybox{
private:
    std::vector<std::string>facesLocation;
public:
    Skybox(std::vector<std::string> facesLocation);
    Skybox();
    ~Skybox();
    u_int load();
    u_int textureId;
    void bind();

};

#endif //SKYBOX_H
