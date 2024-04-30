//
// Created by Murilo on 26/04/2024.
//

#include "../include/headers/meshClass.h"
#include "../include/headers/lightClass.h"
#include "../include/headers/modelClass.h"

const unsigned int width = 800;
const unsigned int height = 800;

using std::vector;


// Vertices coordinates
VertexClass vertices[] =
        { //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
                VertexClass{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
                VertexClass{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
                VertexClass{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
                VertexClass{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
        };

// Indices for vertices order
GLuint indices[] =
        {
                0, 1, 2,
                0, 2, 3
        };

VertexClass lightVertices[] =
        { //     COORDINATES     //
                VertexClass{glm::vec3(-0.1f, -0.1f,  0.1f)},
                VertexClass{glm::vec3(-0.1f, -0.1f, -0.1f)},
                VertexClass{glm::vec3(0.1f, -0.1f, -0.1f)},
                VertexClass{glm::vec3(0.1f, -0.1f,  0.1f)},
                VertexClass{glm::vec3(-0.1f,  0.1f,  0.1f)},
                VertexClass{glm::vec3(-0.1f,  0.1f, -0.1f)},
                VertexClass{glm::vec3(0.1f,  0.1f, -0.1f)},
                VertexClass{glm::vec3(0.1f,  0.1f,  0.1f)}
        };

GLuint lightIndices[] =
        {
                0, 1, 2,
                0, 2, 3,
                0, 4, 7,
                0, 7, 3,
                3, 7, 6,
                3, 6, 2,
                2, 6, 5,
                2, 5, 1,
                1, 5, 4,
                1, 4, 0,
                4, 5, 6,
                4, 6, 7
        };
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

    TextureClass textures[]{
            TextureClass(("../resource_files/textures/planks.png"), "diffuse", 0),
            TextureClass(("../resource_files/textures/planksSpec.png"), "specular", 1)
    };

    ShaderClass shader("../resource_files/shaders/default.vert", "../resource_files/shaders/default.frag");

    std::vector <VertexClass> verts(vertices, vertices + sizeof(vertices) / sizeof(VertexClass));
    std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector <TextureClass> tex(textures, textures + sizeof(textures) / sizeof(TextureClass));
    MeshClass floor(verts, ind, tex); // Mesh plana criada

    ShaderClass lightShader("../resource_files/shaders/light.vert", "../resource_files/shaders/light.frag");
    std::vector <VertexClass> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(VertexClass));
    std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
    LightClass light(lightVerts, lightInd, 0); // Criando a "mesh" luz, mandadno tex como placeholder

    vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    vec3 lightPosition = vec3(0.0f, 0.5f, 0.0f);
    mat4 lightModel = mat4(1.0f);
    unsigned int type = light.type;
    lightModel = translate(lightModel, lightPosition);

    vec3 floorPosition = vec3(0.0f, -0.05f, 0.0f);
    mat4 floorModel = mat4(1.0f);
    floorModel = translate(floorModel, floorPosition);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.id, "model"), 1, GL_FALSE, value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.id, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

    shader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader.id, "model"), 1, GL_FALSE, value_ptr(floorModel));
    glUniform4f(glGetUniformLocation(shader.id, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader.id, "lightPos"), lightPosition.x, lightPosition.y, lightPosition.z);
    glUniform1ui(glGetUniformLocation(shader.id, "type"), type);

    ModelClass model("../resource_files/models/scene.gltf");

    //outra forma de fazer input no shaders, é com uniforms

    glEnable(GL_DEPTH_TEST);

    CameraClass camera(width, height, vec3(0.0f, 0.0f, 2.0f));

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use

        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        model.Draw(shader, camera);
        floor.Draw(shader ,camera, floorModel);
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }
    // Delete all the objects we've created
    shader.Delete();
    lightShader.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}