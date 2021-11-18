#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <gfx/buffers/VertexArray.h>

struct Vertex
{
    glm::vec3 Position;
    glm::vec2 TexCoord;
    glm::vec3 Normal;
};

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void LoadOBJ(const std::string& path);
    
    void Draw();

private:
    VertexArray m_VertexArray;
    VertexBuffer m_VertexBuffer;
    VertexBufferLayout m_Layout;
    std::vector<Vertex> m_Vertices;
};