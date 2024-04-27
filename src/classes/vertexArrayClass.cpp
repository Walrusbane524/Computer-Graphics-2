//
// Created by Murilo on 26/04/2024.
//
#include "../../include/headers/vertexArrayClass.h"

VertexArrayClass::VertexArrayClass(){
    glGenVertexArrays(1, &id);
}

void VertexArrayClass::LinkVBO(VertexBufferClass& VBO, GLuint layout, GLuint n_comp, GLenum type,  GLsizeiptr stride, void* offset){
    VBO.Bind();
    //VertexAttrbPointer interpreta os vertices de acordo com o shaders e com os dados enviados na função
    glVertexAttribPointer(layout, n_comp, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VertexArrayClass::Bind(){
    glBindVertexArray(id);
}

void VertexArrayClass::Unbind(){
    glBindVertexArray(0);
}

void VertexArrayClass::Delete() {
    glDeleteVertexArrays(1, &id);
}