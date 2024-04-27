#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string readShaderFile(const char* filePath) {
    ifstream shaderFile(filePath);
    if (!shaderFile) {
        cerr << "Failed to open shader file: " << filePath << endl;
        return "";
    }
    stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

float value = 0.2f;
bool increasing = true;

void idleFunction() {
    const float step = 0.01f; // Rate of color change

    // If red component is increasing and hasn't reached 1.0 yet
    if (increasing && value < 1.0f) {
        value += step;
    }

    // If red component is decreasing and hasn't reached 0.0 yet
    else if (!increasing && value > 0.0f) {
        value -= step;
    }

    // If red component has reached its limit, change direction
    else {
        increasing = !increasing;
    }

    glClearColor(value, value, value, 0);

    glfwPostEmptyEvent();
}

int main() {
    
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    
    // Set GLFW window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(500, 500, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    string vertexShaderSource = readShaderFile("shaders/vertex_shader.glsl");
    const char* vertexShaderCode = vertexShaderSource.c_str();

    // Build and compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed\n" << infoLog << std::endl;
    }
    
    std::string fragmentShaderSource = readShaderFile("shaders/fragment_shader.glsl");
    const char* fragmentShaderCode = fragmentShaderSource.c_str();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    // Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader compilation failed\n" << infoLog << std::endl;
    }

    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed\n" << infoLog << std::endl;
    }
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data and attribute pointers
    GLfloat vertices[] = {
         0.0f,  0.5f, 0.0f,  // Top Right
         0.5f, -0.5f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,  // Bottom Left
    };

    GLfloat colors[] = {
         1.0f,  0.0f, 0.0f,  
         0.0f,  1.0f, 0.0f,  
         0.0f,  0.0f, 1.0f,  
    };

    GLuint VBO, VBO2, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO2);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);


    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
    glBindVertexArray(0); // Unbind VAO 

    // Rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Check if the ESC key was pressed or the window was closed
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Clear the colorbuffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);
        // Draw the triangle
        glBindVertexArray(VAO);

        //glPointSize(10.0f);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        idleFunction();
    }

    // Clean up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
