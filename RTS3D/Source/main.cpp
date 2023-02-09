#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera/Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.inl"
#include "glm/gtx/transform.hpp"
#include "Shader/EBO.h"
#include "Shader/Shader.h"
#include "Shader/VAO.h"
#include "Shader/VBO.h"
#include "Texture/Texture.h"

int main(int argc, char* argv[])
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Vertices coordinates
    GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
         0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
         0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	0.5f, 1.0f
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

    int width = 800, height = 800;
    GLFWwindow* window = glfwCreateWindow(width, height, "Hello Triangle", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    gladLoadGL();
    glViewport(0, 0, width, height);
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    //---------- SHADERS BEGIN ----------//
    Shader shaderProgram("default.vert", "default.frag");
    //---------- SHADERS END ----------//

    //---------- OBJECTS BEGIN ----------//
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof vertices);
    EBO EBO1(indices, sizeof indices);

    /** Define Vertices position */
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    /** Define Vertices color */
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    /** Define Vertices texture coordinates */
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    //---------- OBJECTS END ----------//

    //---------- TEXTURE BEGIN ----------//
    Texture carTexture("JDM_Car.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    carTexture.Apply(shaderProgram, "tex0", 0);
    //---------- TEXTURE END ----------//
    
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
        
        shaderProgram.Active();

        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
        
        carTexture.Bind();
        
        //---------- RENDER BEGIN ----------//
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        //---------- RENDER END ----------//
        
        glfwSwapBuffers(window);
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    carTexture.Delete();
    shaderProgram.Delete();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
