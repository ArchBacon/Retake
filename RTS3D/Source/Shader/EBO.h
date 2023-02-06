#pragma once

#include<glad/glad.h>

/**
 * An EBO is a buffer, just like a vertex buffer object, that stores indices
 */
class EBO
{
    GLuint id;
    
public:
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};