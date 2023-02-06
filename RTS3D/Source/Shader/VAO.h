#pragma once

#include <glad/glad.h>
#include "VBO.h"

/**
 * @see https://www.khronos.org/opengl/wiki/Vertex_Specification#:~:text=A%20Vertex%20Array%20Object%20(VAO,providing%20the%20vertex%20data%20arrays. 
 *
 * A Vertex Array Object (VAO) is an OpenGL Object that stores all of the state needed to supply vertex data.
 * It stores the format of the vertex data as well as the Buffer Objects providing the vertex data arrays.
 */
class VAO
{
    GLuint id = -1;
    
public:
    VAO();

    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) const;
    
    void Bind() const;
    void Unbind() const;
    void Delete() const;
};
