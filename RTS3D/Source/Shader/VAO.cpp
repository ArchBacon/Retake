#include "VAO.h"

#include "VBO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &id);
}

void VAO::LinkAttrib(const VBO& VBO, const GLuint layout, const GLint numComponents, const GLenum type, const GLsizei stride, const void* offset) const
{
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind() const
{
    glBindVertexArray(id);
}

void VAO::Unbind() const
{
    glBindVertexArray(0);
}

void VAO::Delete() const
{
    glDeleteVertexArrays(1, &id);
}
