//
// Created by Murilo on 26/04/2024.
//
#include "../../include/headers/vertexArrayClass.h"

VertexArrayClass::VertexArrayClass(){
    glGenVertexArrays(1, &id);
}

void VertexArrayClass::LinkVBO(VertexBufferClass& VBO, GLuint l){
    VBO.Bind();
    glVertexAttribPointer(l, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(l);
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