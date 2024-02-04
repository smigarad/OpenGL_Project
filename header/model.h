#ifndef MODEL_H
#define MODEL_H

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
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
private:
    void createVAO(bool texture = false, bool skybox = false);
    void createVBO();
    GLuint VAO = 0;
    GLuint VBO = 0;
    std::vector<float> textureData;
public:
    const float *points;
    int pointsCount;
    float t;
    float alpha;
    glm::mat4 A;
    glm::mat4x3 B;
    glm::mat4 M = glm::mat4(1.0f);
    bool curve = false;
    void addTextureData(const char* path);
    Model(const float *points, int pointsCount, bool texture = false, bool skybox = false,bool curve = false);
    Model(const char* path, bool texture = false, bool skybox = false,bool curve = false);
    ~Model();
    virtual void draw();
    void bind();

};

#endif // "MODEL_H"
