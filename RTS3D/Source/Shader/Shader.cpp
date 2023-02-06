#include "Shader.h"

#include <fstream>
#include <iostream>

#include "Utility/FileResolver.h"

std::string GetFileContents(const char* filename)
{
    if (std::ifstream in(filename, std::ios::binary); in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(contents.data(), contents.size());
        in.close();

        return contents;
    }

    printf("ERROR: Could not find file %s.", filename);
    exit(-1);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    int success;
    char infoLog[1024];

    const std::string shaderPath = "Resource/Shader/";
    
    std::string vertexCode = GetFileContents(FileResolver::Resolve(shaderPath + vertexFile).c_str());
    std::string fragmentCode = GetFileContents(FileResolver::Resolve(shaderPath + fragmentFile).c_str());

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    /*----------------- Vertex Shader -----------------*/
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);
        std::cout << "ERROR::VERTEX::SHADER_COMPILATION_ERROR\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }

    /*----------------- Fragment Shader -----------------*/
    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);
        std::cout << "ERROR::FRAGMENT::SHADER_COMPILATION_ERROR\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }

    /*----------------- Shader Program -----------------*/
    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 1024, nullptr, infoLog);
        std::cout << "ERROR::PROGRAM::PROGRAM_LINKING_ERROR\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Active()
{
    glUseProgram(id);
}

void Shader::Delete()
{
    glDeleteProgram(id);
}
