#include "shaderProgram.h"

ShaderProgram::ShaderProgram()
{
    this->shaderProgramID = glCreateProgram();
    this->createDefaultShaders();
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
    this->vertexShader = VertexShader::loadFromFile(vertexShaderSource);
    this->fragmentShader = FragmentShader::loadFromFile(fragmentShaderSource);
    this->shaderProgramID = glCreateProgram();
    this->compile();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(this->shaderProgramID);
    delete this->vertexShader;
    delete this->fragmentShader;
}

void ShaderProgram::createDefaultShaders()
{
    const std::string vertex_shader =
        "#version 400\n"
        "layout(location=0) in vec3 vp;"
        "layout(location=1) in vec3 vertex_normal;"
        "uniform mat4 modelMatrix;"
        "uniform mat4 viewMatrix;"
        "uniform mat4 projectionMatrix;"
        "out vec3 vs_normal;"
        "void main () {"
        "    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);"
        "    vs_normal = vertex_normal;"
        "}";

    const std::string fragment_shader = "#version 400\n"
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
        exit(-1);
    }

    glUseProgram(this->shaderProgramID);
}
void ShaderProgram::use(glm::mat4 model)
{   
    GLint modelLoc = glGetUniformLocation(this->shaderProgramID, "modelMatrix");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUseProgram(this->shaderProgramID);
}

// void ShaderProgram::use(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
// {

//     GLint modelLoc = glGetUniformLocation(this->shaderProgramID, "modelMatrix");
//     glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

//     // GLint ViewTransform = glGetUniformLocation(this->shaderProgramID, "viewMatrix");
//     // glUniformMatrix4fv(ViewTransform, 1, GL_FALSE, glm::value_ptr(view));

//     // GLint projectionMat = glGetUniformLocation(this->shaderProgramID, "projectionMatrix");
//     // glUniformMatrix4fv(projectionMat, 1, GL_FALSE, glm::value_ptr(projection));
// }

void ShaderProgram::notify(Subject *subject)
{
    if (typeid(*subject) == typeid(Camera))
    {
        GLint ViewTransform = glGetUniformLocation(this->shaderProgramID, "viewMatrix");
        glUniformMatrix4fv(ViewTransform, 1, GL_FALSE, glm::value_ptr(((Camera *)subject)->getCamera()));
        glUseProgram(this->shaderProgramID);
        GLint projectionMat = glGetUniformLocation(this->shaderProgramID, "projectionMatrix");
        glUniformMatrix4fv(projectionMat, 1, GL_FALSE, glm::value_ptr(((Camera *)subject)->getProjection()));
        glUseProgram(this->shaderProgramID);
    }

    if (typeid(*subject) == typeid(Light))
    {
        GLint lightPosLoc = glGetUniformLocation(this->shaderProgramID, "lightPos");
        glUniform3f(lightPosLoc, ((Light *)subject)->getPosition().x, ((Light *)subject)->getPosition().y, ((Light *)subject)->getPosition().z);
        glUseProgram(this->shaderProgramID);
        GLint lightColorLoc = glGetUniformLocation(this->shaderProgramID, "lightColor");
        glUniform3f(lightColorLoc, ((Light *)subject)->getColor().x, ((Light *)subject)->getColor().y, ((Light *)subject)->getColor().z);
        glUseProgram(this->shaderProgramID);
        GLint lightAmbientLoc = glGetUniformLocation(this->shaderProgramID, "lightAmbient");
        glUniform3f(lightAmbientLoc, ((Light *)subject)->getAmbient().x, ((Light *)subject)->getAmbient().y, ((Light *)subject)->getAmbient().z);
        glUseProgram(this->shaderProgramID);

        GLint camPosLoc = glGetUniformLocation(this->shaderProgramID, "camPos");
        glUniformMatrix4fv(camPosLoc,1,GL_FALSE,glm::value_ptr(this->camera->getCamera()));
        glUseProgram(this->shaderProgramID);

    }
}
void ShaderProgram::unuse()
{
    glUseProgram(0);
}

GLuint ShaderProgram::GetVertexShaderID()
{
    return this->vertexShader->GetShaderID();
}
