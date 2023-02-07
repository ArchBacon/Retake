#pragma once

#include <glad/glad.h>

/**
 * An EBO is a buffer, just like a vertex buffer object, that stores indices
 */
class EBO
{
    GLuint id = -1;
    
public:
    EBO(const GLuint* indices, GLsizeiptr size);

    void Bind() const;
    void Unbind() const;
    void Delete() const;
};