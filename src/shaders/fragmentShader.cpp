#include "fragmentShader.h"

FragmentShader::FragmentShader(const char* source) : Shader(source, GL_FRAGMENT_SHADER)
{
    
}

FragmentShader::~FragmentShader()
{
    
}

FragmentShader *FragmentShader::loadFromFile(const char *path)
{
    return (FragmentShader*)Shader::loadFile(path, GL_FRAGMENT_SHADER);
}
