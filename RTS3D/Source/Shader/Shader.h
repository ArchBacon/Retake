#pragma once

#include <string>
#include <glad/glad.h>

std::string GetFileContents(const char* filename);

class Shader
{
    GLuint id;
    
public:
    Shader(const char* vertexFile, const char* fragmentFile);

    void Active();
    void Delete();
};
