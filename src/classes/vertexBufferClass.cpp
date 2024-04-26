//
// Created by Murilo on 26/04/2024.
//
#include "../../include/headers/vertexBufferClass.h"

VertexBufferClass::VertexBufferClass(GLfloat* vertices, GLsizeiptr size){
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexBufferClass::Bind(){
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBufferClass::Unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferClass::Delete() {
    glDeleteBuffers(1, &id);
}