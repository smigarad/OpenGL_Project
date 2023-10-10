#include "shader.h"

Shader::Shader(const char* source, GLenum shaderType)
{
    this->shaderID = glCreateShader(shaderType);
    glShaderSource(this->shaderID, 1, &source, NULL);
    glCompileShader(this->shaderID);
    GLint success;
    glGetShaderiv(this->shaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(this->shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << (shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

Shader::~Shader()
{
    glDeleteShader(this->shaderID);
}

GLuint Shader::GetShaderID()
{
    return this->shaderID;
}

void Shader::use(glm::mat4 model)
{
    GLint modelLoc = glGetUniformLocation(this->shaderID, "modelMatrix");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}