#include "Texture.h"

#include <string>
#include <sys/stat.h>
#include "Shader/Shader.h"
#include "Utility/Common.h"
#include "Utility/FileResolver.h"
#include "Utility/stb_image.h"

inline bool FileExists (const std::string& name) {
    struct stat buffer;   
    return (stat (name.c_str(), &buffer) == 0); 
}

Texture::Texture(const char* image, const char* texType, const GLuint slot, const GLenum format, const GLenum pixelType)
    : texType(texType), slot(slot)
{
    const std::string filePath = FileResolver::Resolve((PATH::TEXTURE + image).c_str());
    if (!FileExists(filePath))
    {
        printf("Missing texture \"%s\".\n", filePath.c_str());
    }
    
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(filePath.c_str(), &width, &height, &channels, 4);
    
    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, pixelType, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Apply(const Shader& shader, const char* uniform, const GLuint unit) const
{
    const GLuint texUni = glGetUniformLocation(id, uniform);
    shader.Activate();
    glUniform1i(texUni, unit);
}

void Texture::Bind() const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() const
{
    glDeleteTextures(1, &id);
}
