#include "Mesh.h"

#include "Camera/Camera.h"
#include "Shader/EBO.h"
#include "Shader/Shader.h"
#include "Shader/VBO.h"
#include "Texture/Texture.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
    : vertices(vertices), indices(indices), textures(textures)
{
    vao.Bind();

    VBO vbo(vertices);
    EBO ebo(indices);

    /** Define Vertices position */
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    /** Define Vertices normals */
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    /** Define Vertices color */
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    /** Define Vertices texture coordinates */
    vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
    shader.Activate();
    vao.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        std::string num;
        std::string type = textures[i].GetTextureType();
        if (type == "diffuse")
        {
            num = std::to_string(numDiffuse++);
        } else if (type == "specular")
        {
            num = std::to_string(numSpecular++);
        }

        textures[i].Apply(shader, (type + num).c_str(), i);
        textures[i].Bind();
    }

    glUniform3f(glGetUniformLocation(shader.GetId(), "camPos"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
    camera.Matrix(shader, "camMatrix");

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
