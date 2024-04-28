//
// Created by Murilo on 26/04/2024.
//

#ifndef CG2_VERTEXBUFFERCLASS_H
#define CG2_VERTEXBUFFERCLASS_H

#include <glad/glad.h>
#include <vector>

#include "vertexClass.h"

class VertexBufferClass{
public:
    GLuint id;

    VertexBufferClass(std::vector<VertexClass>& vertices);

    void Bind();
    void Unbind();
    void Delete();
};

#endif //CG2_VERTEXBUFFERCLASS_H
