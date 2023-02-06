#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader/EBO.h"
#include "Shader/Shader.h"
#include "Shader/VAO.h"

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
// Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
    "}\n\0";

int main(int argc, char* argv[])
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Vertices coordinates
    GLfloat vertices[] =
    {
        -0.5f, -0.5f * static_cast<float>(sqrt(3)) / 3, 0.0f, // Lower left corner
        0.5f, -0.5f * static_cast<float>(sqrt(3)) / 3, 0.0f, // Lower right corner
        0.0f, 0.5f * static_cast<float>(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
        -0.5f / 2, 0.5f * static_cast<float>(sqrt(3)) / 6, 0.0f, // Inner left
        0.5f / 2, 0.5f * static_cast<float>(sqrt(3)) / 6, 0.0f, // Inner right
        0.0f, -0.5f * static_cast<float>(sqrt(3)) / 3, 0.0f // Inner down
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 3, 5, // Lower left triangle
        3, 2, 4, // Lower right triangle
        5, 4, 1 // Upper triangle
    };

    GLFWwindow* window = glfwCreateWindow(800, 800, "Hello Triangle", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 800, 800);

    //---------- SHADERS BEGIN ----------//
    Shader shaderProgram("default.vert", "default.frag");
    //---------- SHADERS END ----------//

    //---------- OBJECTS BEGIN ----------//
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof vertices);
    EBO EBO1(indices, sizeof indices);

    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    //---------- OBJECTS END ----------//

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Active();
        
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
