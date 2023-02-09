#pragma once

#include <GLFW/glfw3.h>
#include "glm/vec3.hpp"

class Shader;

class Camera
{
    glm::vec3 position;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    int width;
    int height;

    float speed = 0.01f;
    float sensitivity = 100.0f;
    
public:
    Camera(int width, int height, glm::vec3 position);

    // Send stuff to shader
    void Matrix(float FOV, float nearPlane, float farPlane, Shader& shader, const char* uniform);
    void Inputs(GLFWwindow* window);
};
