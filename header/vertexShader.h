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
};

#endif // VERTEXSHADER_H