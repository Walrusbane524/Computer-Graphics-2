//
// Created by Murilo on 26/04/2024.
//

#ifndef CG2_VERTEXARRAYCLASS_H
#define CG2_VERTEXARRAYCLASS_H

#include <glad/glad.h>
#include "./vertexBufferClass.h"

class VertexArrayClass{
public:
    GLuint id;

    VertexArrayClass();

    void LinkVBO(VertexBufferClass& VBO, GLuint l);

    void Bind();

    void Unbind();

    void Delete();
};

#endif //CG2_VERTEXARRAYCLASS_H
