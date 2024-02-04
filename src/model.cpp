#include "model.h"

Model::Model(const float *points, int pointsCount, bool texture, bool skybox, bool curve) {
    if (texture) {
        this->pointsCount = pointsCount / 8 / sizeof(float);
    } else if (skybox) {
        this->pointsCount = pointsCount / 3 / sizeof(float);
    } else {
        this->pointsCount = pointsCount / 6 / sizeof(float);
    }
    this->pointsCount = pointsCount;
    this->points = points;
    this->createVBO();
    this->createVAO(texture, skybox);
    this->curve = curve;
    if (this->curve) {
        this->t = 1.f;
        this->alpha = 0.02f;
        this->A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
                            glm::vec4(3.0, -6.0, 3.0, 0),
                            glm::vec4(-3.0, 3.0, 0, 0),
                            glm::vec4(1, 0, 0, 0));
//        this->B = glm::mat4x3( glm::vec3(0, 0, 0),
//                               glm::vec3(2, 2, 0),
//                               glm::vec3(4, 4, 0),
//                               glm::vec3(6, 0, 0));
        B = glm::mat4x3(glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.19f, 1.63f, 0.0f),
                        glm::vec3(0.49f, -0.71f, 0.0f),
                        glm::vec3(1.0f, 0.0f, 0.0f));
        this->M = glm::mat4(1.0f);
    }
}

Model::~Model() {
    glDeleteBuffers(1, &this->VBO);
    glDeleteVertexArrays(1, &this->VAO);
}

Model::Model(const char *path, bool texture, bool skybox, bool curve) {
    this->addTextureData(path);
    this->pointsCount = this->textureData.size() * sizeof(float);
    printf("pointsCount: %d\n", this->pointsCount);
    this->points = this->textureData.data();
    this->createVBO();
    this->createVAO(texture, skybox);
    this->curve = curve;

}

void Model::createVAO(bool texture, bool skybox) {
    this->VAO = 0;
    glGenVertexArrays(1, &this->VAO);   // generate the VAO
    glBindVertexArray(this->VAO);       // bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO); // bind the VBO

    if (texture) {
        printf("texture\n");
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), NULL);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 12);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    } else if (skybox) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    } else {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 12);
    }
}

void Model::createVBO() {
    this->VBO = 0;
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, pointsCount, this->points, GL_STATIC_DRAW);
}

void Model::draw() {
//    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->pointsCount / 3);
}

void Model::bind() {
    glBindVertexArray(this->VAO);
}

void Model::addTextureData(const char *filepath) {
    Assimp::Importer importer;
    unsigned int flags = aiProcess_OptimizeMeshes
                         | aiProcess_JoinIdenticalVertices
                         | aiProcess_Triangulate
                         | aiProcess_CalcTangentSpace;

    const aiScene *scene = importer.ReadFile(filepath, flags);
    std::vector<float> vertices = {};
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        printf("Assimp Error: %s\n", importer.GetErrorString());
        return;
    }
    if (scene->HasMeshes()) {
        aiMesh *mesh = scene->mMeshes[0];
        printf("model: %s\n", mesh->mName.C_Str());
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                aiVector3D position = mesh->mVertices[face.mIndices[j]];
                aiVector3D normal = mesh->mNormals[face.mIndices[j]];

                vertices.push_back(position.x);
                vertices.push_back(position.y);
                vertices.push_back(position.z);

                vertices.push_back(normal.x);
                vertices.push_back(normal.y);
                vertices.push_back(normal.z);

                if (mesh->HasTextureCoords(0)) {

//                    printf("has texture coords\n");
                    aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
                    vertices.push_back(uv.x);
                    vertices.push_back(uv.y);
                }
            }
        }
    }
    this->textureData = vertices;
}

