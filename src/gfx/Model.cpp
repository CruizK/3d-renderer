#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>

Model::Model() :
	m_Mesh(nullptr), m_ModelMatrix(glm::mat4(1.0f)), m_Position(glm::vec3(0.0f)), m_Color(glm::vec3(1.0f))
{

}

Model::~Model()
{

}

void Model::Draw(PerspectiveCamera& camera, Shader& shader, const glm::vec3& lightPos)
{
	shader.Use();
	shader.SetMat4("model", m_ModelMatrix);
	shader.SetMat4("view", camera.GetViewMatrix());
	shader.SetMat4("projection", camera.GetProjectionMatrix());
	shader.SetVec3("objectColor", m_Color);

	m_Mesh->Draw();
}

void Model::Draw(PerspectiveCamera& camera, Material* material, const glm::vec3& lightPos)
{
	Shader& shader = *material->Shader;
	shader.Use();
	shader.SetVec3("material.ambient", material->Ambient);
	shader.SetVec3("material.diffuse", material->Diffuse);
	shader.SetVec3("material.specular", material->Specular);
	shader.SetFloat("material.shininess", material->Shininess);
	Draw(camera, shader, lightPos);
}

void Model::RecalcModelMatrix()
{
	m_ModelMatrix = glm::mat4(1.0f);
	m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
	m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);
}
