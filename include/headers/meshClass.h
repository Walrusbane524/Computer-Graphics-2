//
// Created by Murilo on 28/04/2024.
//

#ifndef CG2_MESHCLASS_H
#define CG2_MESHCLASS_H

#include <string>
#include "cameraClass.h"
#include "elementBufferClass.h"
#include "vertexArrayClass.h"
#include "textureClass.h"

#include <vector>

using namespace std;

class MeshClass{

public:
    vector <VertexClass> vertices;
    vector <GLuint> indices;
    vector <TextureClass> textures;

    VertexArrayClass VAO;

    MeshClass(vector <VertexClass>& vertices, vector <GLuint>& indices, vector <TextureClass>& textures);

    void Draw
            (
                    ShaderClass& shader,
                    CameraClass& camera,
                    glm::mat4 matrix = glm::mat4(1.0f),
                    glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
            );

};

#endif //CG2_MESHCLASS_H
