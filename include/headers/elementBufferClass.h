//
// Created by Murilo on 26/04/2024.
//

#ifndef CG2_ELEMENTBUFFERCLASS_H
#define CG2_ELEMENTBUFFERCLASS_H

#include <glad/glad.h>
#include <vector>

class ElementBufferClass{
public:
    GLuint id;

    ElementBufferClass(std::vector<GLuint>& indices);

    void Bind();
    void Unbind();
    void Delete();
};


#endif //CG2_ELEMENTBUFFERCLASS_H
