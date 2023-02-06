#pragma once

#include <glad/glad.h>

/**
 * @see https://en.wikipedia.org/wiki/Vertex_buffer_object
 * 
 * A vertex buffer object (VBO) is an OpenGL feature that provides methods for uploading vertex data (position, normal vector, color, etc.)
 */
class VBO
{
    GLuint id = -1;
    
public:
    VBO(const GLfloat* vertices, GLsizeiptr size);

    void Bind() const;
    void Unbind() const;
    void Delete() const;
};
