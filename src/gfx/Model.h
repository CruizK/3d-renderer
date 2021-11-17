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

class Model
{
public:
    Model();
    ~Model();

    void LoadOBJ(const std::string& path);

    const std::vector<Vertex>& GetVertices() { return m_Vertices; }
    const glm::mat4& GetModelMatrix() { return m_ModelMatrix; }

    void SetPosition(const glm::vec3& pos) { m_Position = pos; RecalcModelMatrix(); }
    void SetRotation(float rot) { m_Rotation = rot; RecalcModelMatrix(); }

private:
    void RecalcModelMatrix();
    
private:
    glm::vec3 m_Position;
    float m_Rotation;
    std::vector<Vertex> m_Vertices;
    glm::mat4 m_ModelMatrix;
};