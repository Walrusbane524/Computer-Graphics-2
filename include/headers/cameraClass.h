//
// Created by Murilo on 27/04/2024.
//

#ifndef CG2_CAMERACLASS_H
#define CG2_CAMERACLASS_H
#define GLM_ENABLE_EXPERIMENTAL

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

using namespace glm;

class CameraClass{

public:
    vec3 Position;
    vec3 Orientation = vec3(0.0f, 0.0f, -1.0f); // olhando sempre pro z negativo
    vec3 Up = vec3(0.0f, 1.0f, 0.0f);
    mat4 cameraMatrix = mat4(1.0f);

    int width, height;

    float speed = 0.005f;
    float sensitivity = 100.0f;

    bool firstClick = true;

    CameraClass(int width, int height, vec3 position);

    void updateMatrix(float FOVdegree, float nearPlane, float farPlane);
    void Matrix(ShaderClass& shader, const char* uniform);
    void Inputs(GLFWwindow* window);

};
#endif //CG2_CAMERACLASS_H
