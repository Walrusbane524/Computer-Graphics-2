//
// Created by Murilo on 26/04/2024.
//
#include <iostream>
// o CLION não tá achando pq eu configurei no CMAKE para achar
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <fstream>
#include <sstream>
#include <math.h>

#include "../include/headers/shaderClass.h"
#include "../include/headers/elementBufferClass.h"
#include "../include/headers/vertexArrayClass.h"
#include "../include/headers/vertexBufferClass.h"

using namespace std;

// Vertices coordinates
GLfloat vertices[] =
        { //               COORDINATES                  /     COLORS           //
                -0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
                0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
                0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
                -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
                0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
                0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
        };

// Indices for vertices order
GLuint indices[] =
        {
                0, 3, 5, // Lower left triangle
                3, 2, 4, // Upper triangle
                5, 4, 1 // Lower right triangle
        };
// Initialize GLFW

int main()
{

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Teste", NULL, NULL);
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
    glViewport(0, 0, 800, 800);

    ShaderClass shader("../resource_files/shaders/default.vert", "../resource_files/shaders/default.frag");

    VertexArrayClass VAO;
    VAO.Bind();

    VertexBufferClass VBO(vertices, sizeof(vertices));
    ElementBufferClass EBO(indices, sizeof(indices));

    VAO.LinkVBO(VBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO.LinkVBO(VBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();

    //outra forma de fazer input no shaders, é com uniforms
    GLuint uniId = glGetUniformLocation(shader.id, "scale");

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        shader.Activate();
        glUniform1f(uniId, 0.5f);
        // Bind the VAO so OpenGL knows to use it
        VAO.Bind();
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }
    // Delete all the objects we've created
    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
    shader.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}