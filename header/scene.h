#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "drawableObject.h"  
#include "shaderProgram.h"
class Scene
{
private:
    std::vector<DrawableObject*> objects;
    ShaderProgram* shaderProgram;
public:
    Scene(/* args */);
    ~Scene();
    Scene(const char* vertex_shader, const char* fragment_shader);
    void addObject(DrawableObject* object);
    void draw();
    
};

#endif // SCENE_H