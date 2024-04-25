//
// Created by Murilo on 25/04/2024.
//
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/classes/color.h"
#include "../include/classes/vec.h"

GLfloat background_color[3] = {0.0f, 0.0f, 0.0f};

// Função chamada quando uma tecla é pressionada
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        // Gera uma nova cor aleatória
        for (int i = 0; i < 3; ++i) {
            background_color[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        }
        glClearColor(background_color[0], background_color[1], background_color[2], 1.0f);
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello, OpenGL!", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glColor3f(1.0f, 1.0f,1.0f);
        glRasterPos2f(-0.5f, 0.0f);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_DEPTH_TEST);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

