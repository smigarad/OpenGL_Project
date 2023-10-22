#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "shader.h"

class VertexShader : public Shader
{
private:
    /* data */
public:
    VertexShader(const char* source);
    ~VertexShader();
    static VertexShader* loadFromFile(const char* path);
    
};

#endif // VERTEXSHADER_H