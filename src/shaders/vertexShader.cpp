#include "vertexShader.h"

VertexShader::VertexShader(const char* source) : Shader(source, GL_VERTEX_SHADER)
{
    
}

VertexShader::~VertexShader()
{
    
}

VertexShader *VertexShader::loadFromFile(const char *path)
{
    return (VertexShader*)Shader::loadFile(path, GL_VERTEX_SHADER);
}
