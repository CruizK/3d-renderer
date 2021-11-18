#pragma once

#include <glm/glm.hpp>
#include <gfx/Texture2D.h>
#include <gfx/Shader.h>

struct Material
{
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    float Shininess;
    Texture2D* DiffuseTexture;
    Shader* Shader;
};