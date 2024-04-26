//
// Created by Murilo on 26/04/2024.
//

#include "../../include/headers/elementBufferClass.h"

ElementBufferClass::ElementBufferClass(GLuint* indices, GLsizeiptr size){
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void ElementBufferClass::Bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBufferClass::Unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBufferClass::Delete() {
    glDeleteBuffers(1, &id);
}