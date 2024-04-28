//
// Created by Murilo on 28/04/2024.
//

#ifndef CG2_LIGHTCLASS_H
#define CG2_LIGHTCLASS_H

#include <string>
#include "cameraClass.h"
#include "elementBufferClass.h"
#include "vertexArrayClass.h"
#include "textureClass.h"

#include <vector>

using namespace std;

class LightClass{

public:
    vector <VertexClass> vertices;
    vector <GLuint> indices;
    unsigned int type; //0-> pointLight, 1 -> spotLight, 2 -> directional

    VertexArrayClass VAO;

    LightClass(vector <VertexClass>& vertices, vector <GLuint>& indices, unsigned int type);

    void Draw(ShaderClass& shader, CameraClass& camera);

};

#endif //CG2_LIGHTCLASS_H
