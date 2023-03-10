#pragma once

#include <glad/glad.h>

class Shader;

class Texture
{
    GLuint id = -1;
    GLenum texType;
    GLuint slot;
    
public:
    Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType);

    // Assigns a texture unit to a texture
    void Apply(const Shader& shader, const char* uniform, GLuint unit) const;

    void Bind() const;
    void Unbind() const;
    void Delete() const;
};
