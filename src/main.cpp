//
// Created by Murilo on 26/04/2024.
//
#include <iostream>
// o CLION não tá achando pq eu configurei no CMAKE para achar
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <math.h>

#include "../include/headers/shaderClass.h"
#include "../include/headers/elementBufferClass.h"
#include "../include/headers/vertexArrayClass.h"
#include "../include/headers/vertexBufferClass.h"
#include "../include/headers/textureClass.h"

using namespace std;
using namespace glm;

// Vertices coordinates
//Pyramid
GLfloat vertices[] =
        { //     COORDINATES     /        COLORS      /   TexCoord  //
                -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
                -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
                0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
                0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
                0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
        };

// Indices for vertices order
GLuint indices[] =
        {
                0, 1, 2,
                0, 2, 3,
                0, 1, 4,
                1, 2, 4,
                2, 3, 4,
                3, 0, 4
        };

int height = 800;
int width = 800;

int main()
{

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Teste", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, width, height);

    ShaderClass shader("../resource_files/shaders/default.vert", "../resource_files/shaders/default.frag");

    VertexArrayClass VAO;
    VAO.Bind();

    VertexBufferClass VBO(vertices, sizeof(vertices));
    ElementBufferClass EBO(indices, sizeof(indices));

    VAO.LinkVBO(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO.LinkVBO(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO.LinkVBO(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); //texture


    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();

    //outra forma de fazer input no shaders, é com uniforms
    GLuint uniId = glGetUniformLocation(shader.id, "scale");

    //Texture
    TextureClass TEX("../resource_files/textures/pop-cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    TEX.texUnit(shader, "tex0", 0);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        shader.Activate();

        double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1 / 60)
        {
            rotation += 0.005f;
            prevTime = crntTime;
        }

        mat4 model = mat4(1.0f);
        mat4 view = mat4(1.0f);
        mat4 proj  = mat4(1.0f);

        model = rotate(model, radians(rotation), vec3(0.0f, 1.0f, 0.0f));
        view = translate(view, vec3(0.0f, -0.5f, -2.0f));
        proj = perspective(radians(45.0f), (float)(width/height), 0.1f, 100.0f);
        // toda a visão que temso vai de 0.1 até 1000


        int modelUni = glGetUniformLocation(shader.id, "model");
        glUniformMatrix4fv(modelUni, 1, GL_FALSE, value_ptr(model));

        int viewUni = glGetUniformLocation(shader.id, "view");
        glUniformMatrix4fv(viewUni, 1, GL_FALSE, value_ptr(view));

        int projUni = glGetUniformLocation(shader.id, "proj");
        glUniformMatrix4fv(projUni, 1, GL_FALSE, value_ptr(proj));


        glUniform1f(uniId, 0.5f);
        TEX.Bind();
        // Bind the VAO so OpenGL knows to use it
        VAO.Bind();
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }
    // Delete all the objects we've created
    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
    TEX.Delete();
    shader.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}