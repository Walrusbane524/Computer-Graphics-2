//
// Created by Murilo on 28/04/2024.
//
#include "../../include/headers/meshClass.h"

MeshClass::MeshClass(vector<VertexClass>& vertices, vector<GLuint>& indices, vector<TextureClass>& textures) {
    MeshClass::vertices = vertices;
    MeshClass::indices = indices;
    MeshClass::textures = textures;

    VAO.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VertexBufferClass VBO(vertices);
    // Generates Element Buffer Object and links it to indices
    ElementBufferClass EBO(indices);
    // Links VBO attributes such as coordinates and colors to VAO
    VAO.LinkVBO(VBO, 0, 3, GL_FLOAT, sizeof(VertexClass), (void*)0);
    VAO.LinkVBO(VBO, 1, 3, GL_FLOAT, sizeof(VertexClass), (void*)(3 * sizeof(float)));
    VAO.LinkVBO(VBO, 2, 3, GL_FLOAT, sizeof(VertexClass), (void*)(6 * sizeof(float)));
    VAO.LinkVBO(VBO, 3, 2, GL_FLOAT, sizeof(VertexClass), (void*)(9 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void MeshClass::Draw(ShaderClass &shader, CameraClass &camera) {
    shader.Activate();
    VAO.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for(unsigned int i = 0; i < textures.size(); i++){
        std::string num;
        std::string type = textures[i].type;

        if (type == "diffuse") num = std::to_string(numDiffuse++);
        else if (type == "specular") num = std::to_string(numSpecular++);

        textures[i].texUnit(shader, (type + num).c_str(), i);
        textures[i].Bind();
        //names of the uniforms will be diffuse0, difusse1,...,specular0, specular1,...
    }
    glUniform3f(glGetUniformLocation(shader.id, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(shader, "camMatrix");

    // Draw the actual mesh
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

