#include "Model.h"
#include <iostream>
#include <fstream>
#include <core/Log.h>
#include <core/Core.h>

Model::Model()
{

}

Model::~Model()
{

}

void Model::LoadOBJ(const std::string& path)
{
    std::ifstream file(path);
    
    std::vector<glm::vec3> tmpVertices;
    std::vector<glm::vec2> tmpTexCoords;
    std::vector<glm::vec3> tmpNormals;

    if(file.is_open())
    {
        std::string tp;
        while(std::getline(file, tp)) 
        {
            const char* line = tp.c_str();
            char lineHeader[128];
            sscanf(line, "%s", lineHeader);
            const char* postHeader = line + strlen(lineHeader);
            if(strcmp("v", lineHeader) == 0) {    
                glm::vec3 vertex;
                sscanf(postHeader, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
                tmpVertices.push_back(vertex);
            }
            else if(strcmp("vt", lineHeader) == 0) {
                glm::vec2 textureCoord;
                sscanf(postHeader, "%f %f", &textureCoord.x, &textureCoord.y);
                tmpTexCoords.push_back(textureCoord);
            }
            else if(strcmp("vn", lineHeader) == 0) {
                glm::vec3 normal;
                sscanf(postHeader, "%f %f %f", &normal.x, &normal.y, &normal.z);
                tmpNormals.push_back(normal);
            }
            else if(strcmp("f", lineHeader) == 0) {
                u32 v[3],t[3],n[3];
                int matches = sscanf(postHeader, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &v[0], &t[0], &n[0], &v[1], &t[1], &n[1], &v[2], &t[2], &n[2]);
                if (matches != 9)
                {
                    CORE_ERROR("(Model Loading Error) Could not load model, invalid format: {0}", path);
                    return;
                }

                for(int i = 0; i < 3; i++) {
                    Vertex vertex = {
                        tmpVertices[v[i]-1],
                        tmpTexCoords[t[i]-1],
                        tmpNormals[n[i]-1]
                    };
                    m_Vertices.push_back(vertex);
                }
            }
        }

        file.close();
    }
    else
    {
        CORE_ERROR("(Model Loading Error) Could not laod model at path: {0}", path);
    }
}