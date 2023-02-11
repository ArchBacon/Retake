#pragma once

#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

class Shader;

class Camera
{
    glm::vec3 position;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);

    bool firstClick = true;
    
    int width;
    int height;

    float speed = 0.01f;
    float sensitivity = 100.0f;
    
public:
    Camera(int width, int height, glm::vec3 position);

    // Send stuff to shader
    void UpdateMatrix(float FOV, float nearPlane, float farPlane);
    void Matrix(Shader& shader, const char* uniform);
    void Inputs(GLFWwindow* window);

    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetOrientation() const { return orientation; }
};
