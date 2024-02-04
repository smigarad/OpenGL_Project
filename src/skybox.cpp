//
// Created by radek on 12/10/23.
//

#include "skybox.h"

Skybox::Skybox(std::vector<std::string> facesLocation) {
    this->facesLocation = facesLocation;
    this->textureId = load();
}

Skybox::~Skybox() {
}

u_int Skybox::load() {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false);
    for (unsigned int i = 0; i < facesLocation.size(); i++)
    {
        unsigned char *data = stbi_load(facesLocation[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            if (nrChannels == 3)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            else if (nrChannels == 4)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << facesLocation[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return textureId;
}

void Skybox::bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
}

Skybox::Skybox() {
    this->facesLocation = std::vector<std::string>{"../resources/darkMap/posx.jpg",
                                                   "../resources/darkMap/negx.jpg",
                                                   "../resources/darkMap/posy.jpg",
                                                   "../resources/darkMap/negy.jpg",
                                                   "../resources/darkMap/posz.jpg",
                                                   "../resources/darkMap/negz.jpg"};
    this->textureId = load();
}

