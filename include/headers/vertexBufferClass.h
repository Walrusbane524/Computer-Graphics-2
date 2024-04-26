//
// Created by Murilo on 26/04/2024.
//

#ifndef CG2_VERTEXBUFFERCLASS_H
#define CG2_VERTEXBUFFERCLASS_H

#include <glad/glad.h>

class VertexBufferClass{
public:
    GLuint id;

    VertexBufferClass(GLfloat* vertices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};

#endif //CG2_VERTEXBUFFERCLASS_H
