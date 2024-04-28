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

    void Draw(ShaderClass& shader, CameraClass& camera);

};

#endif //CG2_MESHCLASS_H
