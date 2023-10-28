#include "shaderProgram.h"

ShaderProgram::ShaderProgram() {
    this->shaderProgramID = glCreateProgram();
    this->createDefaultShaders();
    this->compile();
}

ShaderProgram::ShaderProgram(VertexShader *vertexShader, FragmentShader *fragmentShader) {
    this->vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;
    this->shaderProgramID = glCreateProgram();
    this->compile();
}

ShaderProgram::ShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource) {
    this->vertexShader = VertexShader::loadFromFile(vertexShaderSource);
    this->fragmentShader = FragmentShader::loadFromFile(fragmentShaderSource);
    this->shaderProgramID = glCreateProgram();
    this->compile();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(this->shaderProgramID);
    delete this->vertexShader;
    delete this->fragmentShader;
}

void ShaderProgram::createDefaultShaders() {
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

void ShaderProgram::compile() {

    glAttachShader(this->shaderProgramID, this->vertexShader->GetShaderID());
    glAttachShader(this->shaderProgramID, this->fragmentShader->GetShaderID());
    glLinkProgram(this->shaderProgramID);
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(this->shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
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

void ShaderProgram::use(glm::mat4 model, Material *material, glm::vec3 color) {

    this->sendUniformValue(model,"modelMatrix");
    this->sendUniformValue(color,"objectColor");
    if (material != nullptr) {
        this->sendUniformValue(material->r_a,"r_a");
        this->sendUniformValue(material->r_s,"r_s");
        this->sendUniformValue(material->r_d,"r_a");

    }

}


void ShaderProgram::notify(Subject *subject) {
    if (typeid(*subject) == typeid(Camera)) {
        this->sendUniformValue(((Camera *) subject)->getCamera(), "viewMatrix");
        this->sendUniformValue(((Camera *) subject)->getProjection(), "projectionMatrix");
        this->sendUniformValue(((Camera *) subject)->getEye(), "camPos");
//        glm::mat4 matrix = ((Camera*)subject)->getCamera();
//        printf("Matrix values:\n");
//        printf("%f, %f, %f, %f\n", matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3]);
//        printf("%f, %f, %f, %f\n", matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3]);
//        printf("%f, %f, %f, %f\n", matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3]);
//        printf("%f, %f, %f, %f\n", matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);
    }

    if (typeid(*subject) == typeid(Light)) {
        this->sendUniformValue(((Light *) subject)->getPosition(), "lightPos");
        this->sendUniformValue(((Light *) subject)->getColor(), "lightColor");
        this->sendUniformValue(((Light *) subject)->getAmbient(), "lightAmbient");
    }
}

void ShaderProgram::unuse() {
    glUseProgram(0);
}

void ShaderProgram::sendUniformValue(glm::mat4 matrix, const std::string &name) const {
    GLint location = glGetUniformLocation(this->shaderProgramID, name.c_str());
    glUseProgram(this->shaderProgramID);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::sendUniformValue(glm::mat3 matrix, const std::string &name) const {
    GLint location = glGetUniformLocation(this->shaderProgramID, name.c_str());
    glUseProgram(this->shaderProgramID);
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::sendUniformValue(glm::vec3 vector, const std::string &name) const {
    GLint location = glGetUniformLocation(this->shaderProgramID, name.c_str());
    glUseProgram(this->shaderProgramID);
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::sendUniformValue(glm::vec4 vector, const std::string &name) const {
    GLint location = glGetUniformLocation(this->shaderProgramID, name.c_str());
    glUseProgram(this->shaderProgramID);
    glUniform4f(location, vector.x, vector.y, vector.z,vector.w);
}

void ShaderProgram::sendUniformValue(float fn, const std::string &name) const {
    GLint location = glGetUniformLocation(this->shaderProgramID, name.c_str());
    glUseProgram(this->shaderProgramID);
    glUniform1f(this->shaderProgramID,location);
}