#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &id);
}

void VAO::LinkVBO(VBO& VBO, const GLuint layout) const
{
    VBO.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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
