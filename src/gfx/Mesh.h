#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

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

    const std::vector<Vertex>& GetVertices() { return m_Vertices; }
    
private:
    std::vector<Vertex> m_Vertices;
};