#pragma once

#include <vector>
#include <glad/glad.h>
#include "Shader/VAO.h"

class Texture;
class Shader;
class Camera;
struct Vertex;

class Mesh
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    VAO vao;
    
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
    void Draw(Shader& shader, Camera& camera);
};
