//
// Created by Murilo on 28/04/2024.
//

#ifndef CG2_VERTEXCLASS_H
#define CG2_VERTEXCLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>

struct VertexClass{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
};

#endif //CG2_VERTEXCLASS_H
