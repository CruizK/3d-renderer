#pragma once

#include <gfx/Mesh.h>
#include <gfx/Shader.h>
#include <gfx/PerspectiveCamera.h>
#include <gfx/Material.h>



class Model
{
public:
	Model();
	~Model();

	void SetMesh(Mesh& mesh) { m_Mesh = &mesh; }

	void SetPosition(const glm::vec3& pos) { m_Position = pos; RecalcModelMatrix(); }
	void SetColor(const glm::vec3& color) { m_Color = color; }
	void SetScale(const glm::vec3& scale) { m_Scale = scale; RecalcModelMatrix(); }



	const glm::vec3& GetColor() { return m_Color; }

	void Draw(PerspectiveCamera& camera, Material* material, const glm::vec3& lightPos);
	void Draw(PerspectiveCamera& camera, Shader& shader, const glm::vec3& lightPos);

private:
	void RecalcModelMatrix();

private:
	
	glm::mat4 m_ModelMatrix;
	
	
	glm::vec3 m_Color;
	glm::vec3 m_Scale;
	glm::vec3 m_Position;

	Mesh* m_Mesh;
};