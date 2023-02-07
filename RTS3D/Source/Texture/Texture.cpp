#include "Texture.h"

#include "Shader/Shader.h"
#include "Utility/Common.h"
#include "Utility/FileResolver.h"
#include "Utility/stb_image.h"

Texture::Texture(const char* image, const GLenum texType, const GLenum slot, const GLenum format, const GLenum pixelType)
    : texType(texType)
{
    const std::string filePath = FileResolver::Resolve((PATH::TEXTURE + image).c_str());
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(filePath.c_str(), &width, &height, &channels, 4);
    
    glGenTextures(1, &id);
    glActiveTexture(slot);
    glBindTexture(texType, id);
    
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(texType, 0, GL_RGBA, width, height, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);
    
    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}

void Texture::Apply(const Shader& shader, const char* uniform, const GLuint unit) const
{
    const GLuint texUni = glGetUniformLocation(id, uniform);
    shader.Active();
    glUniform1i(texUni, unit);
}

void Texture::Bind() const
{
    glBindTexture(texType, id);
}

void Texture::Unbind() const
{
    glBindTexture(texType, 0);
}

void Texture::Delete() const
{
    glDeleteTextures(1, &id);
}
