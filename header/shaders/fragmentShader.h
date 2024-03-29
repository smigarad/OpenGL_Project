#ifndef __SHADER__
#define __SHADER__

#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H
#include "shader.h"

class FragmentShader : public Shader
{
private:
    /* data */
public:
    FragmentShader(const char* source);
    ~FragmentShader();
    static FragmentShader* loadFromFile(const char* path);
};

#endif // FRAGMENTSHADER_H
#endif //__SHADER__