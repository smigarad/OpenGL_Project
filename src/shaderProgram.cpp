#include "shaderProgram.h"

ShaderProgram::ShaderProgram()
{
    this->shaderProgramID = glCreateProgram();
    this->createDefaultShaders(1.0f, 1.0f, 1.0f, 1.0f);
    this->compile();
}
ShaderProgram::ShaderProgram(VertexShader *vertexShader, FragmentShader *fragmentShader)
{
    this->vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;
    this->shaderProgramID = glCreateProgram();
    this->compile();
}

ShaderProgram::ShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource)
{
    this->vertexShader = new VertexShader(vertexShaderSource);
    this->fragmentShader = new FragmentShader(fragmentShaderSource);
    this->shaderProgramID = glCreateProgram();
    this->compile();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(this->shaderProgramID);
    delete this->vertexShader;
    delete this->fragmentShader;
}

void ShaderProgram::createDefaultShaders(float r, float g, float b, float a)
{
    const std::string vertex_shader = 
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vertex_normal;"
		"uniform mat4 modelMatrix; "
		"out vec3 vs_normal;"
		"void main () {"
		"    gl_Position = modelMatrix * vec4 (vp, 1.0);"
		"    vs_normal = vertex_normal;"
		"}";

    const std::string fragment_shader = "#version 330\n"
		"out vec4 frag_colour;"
		"in vec3 vs_normal;"
		"void main () {"
		"     frag_colour = vec4 (vs_normal, 1.0);"
		"}";
        
    this->vertexShader = new VertexShader(vertex_shader.c_str());
    this->fragmentShader = new FragmentShader(fragment_shader.c_str());
    
}
void ShaderProgram::compile()
{
    
    glAttachShader(this->shaderProgramID, this->vertexShader->GetShaderID());
    glAttachShader(this->shaderProgramID, this->fragmentShader->GetShaderID());
    glLinkProgram(this->shaderProgramID);
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(this->shaderProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLint infoLogLength;
        glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgramID, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

    glUseProgram(this->shaderProgramID);
}
void ShaderProgram::use(glm::mat4 model)
{
    GLint modelLoc = glGetUniformLocation(this->shaderProgramID, "modelMatrix");
    glUseProgram(this->shaderProgramID);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void ShaderProgram::unuse()
{
    glUseProgram(0);
}
