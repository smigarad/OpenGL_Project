//
// Created by radek on 27.10.23.
//
#include "material.h"

Material::Material(float r_a, float r_d, float r_s) {
    this->r_a = r_a;
    this->r_d = r_d;
    this->r_s = r_s;
}

Material::Material(float r_a, float r_d, float r_s, const char *texturePath) {
    this->r_a = r_a;
    this->r_d = r_d;
    this->r_s = r_s;
    this->loadTexture(texturePath);
}

void Material::loadTexture(const char *texturePath) {
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    std::cout << "Loading texture: " << texturePath << std::endl;
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    if (data) {
        if (nrChannels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else if (nrChannels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture from file " << texturePath << std::endl;
    }
    stbi_image_free(data);
}

Material::~Material() {
//    glDeleteTextures(1, &this->textureId);
}

void Material::bind() {
//    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
//    std::cout << "Binding texture: " << this->textureId << std::endl;

}
