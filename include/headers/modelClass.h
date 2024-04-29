//
// Created by Murilo on 29/04/2024.
//

#ifndef CG2_MODELCLASS_H
#define CG2_MODELCLASS_H

#include <json/njson.h>
#include "meshClass.h"

using json = nlohmann::json;

class ModelClass{
public:
    ModelClass(const char* file);

    void Draw(ShaderClass& shader, CameraClass& camera);

private:
    const char* file;
    std::vector<unsigned char> data;
    json JSON;

    std::vector<MeshClass> meshes;
    std::vector<glm::vec3> translationsMeshes;
    std::vector<glm::quat> rotationsMeshes;
    std::vector<glm::vec3> scalesMeshes;
    std::vector<glm::mat4> matricesMeshes;

    std::vector<std::string> loadedTexName;
    std::vector<TextureClass> loadedTex;

    void loadMesh(unsigned int indMesh);

    // Traverses a node recursively, so it essentially traverses all connected nodes
    void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

    std::vector<unsigned char> getData();
    std::vector<float> getFloats(json accessor);
    std::vector<GLuint> getIndices(json accessor);
    std::vector<TextureClass> getTextures();

    std::vector<VertexClass> assembleVertices
            (
                    std::vector<glm::vec3> positions,
                    std::vector<glm::vec3> normals,
                    std::vector<glm::vec2> texUVs
            );

    std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
    std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
    std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};

#endif //CG2_MODELCLASS_H
