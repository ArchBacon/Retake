#pragma once

#include <vector>
#include <glad/glad.h>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct Vertex
{
    glm::vec3 position{};
    glm::vec3 normal{};
    glm::vec3 color{};
    glm::vec2 texUV{}; // Texture coordinates
};

/**
 * @see https://en.wikipedia.org/wiki/Vertex_buffer_object
 * 
 * A vertex buffer object (VBO) is an OpenGL feature that provides methods for uploading vertex data (position, normal vector, color, etc.)
 */
class VBO
{
    GLuint id = -1;
    
public:
    VBO(std::vector<Vertex>& vertices);

    void Bind() const;
    void Unbind() const;
    void Delete() const;
};
