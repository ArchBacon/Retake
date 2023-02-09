#include "Camera.h"

#include <glad/glad.h>
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader/Shader.h"

Camera::Camera(const int width, const int height, const glm::vec3 position)
    : position(position), width(width), height(height)
{}

void Camera::Matrix(float FOV, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(position, position + orientation, up);
    projection = glm::perspective(glm::radians(FOV), (float)(width / height), nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.GetId(), uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Inputs()
{
}
