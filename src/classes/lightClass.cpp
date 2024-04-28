//
// Created by Murilo on 28/04/2024.
//
//
// Created by Murilo on 28/04/2024.
//
#include "../../include/headers/lightClass.h"

LightClass::LightClass(vector<VertexClass>& vertices, vector<GLuint>& indices, unsigned int type) {
    LightClass::vertices = vertices;
    LightClass::indices = indices;
    LightClass::type = type;

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

void LightClass::Draw(ShaderClass &shader, CameraClass &camera) {
    shader.Activate();
    VAO.Bind();
    glUniform3f(glGetUniformLocation(shader.id, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(shader, "camMatrix");

    // Draw the actual mesh
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

