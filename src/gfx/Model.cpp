#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>

Model::Model() :
	m_Mesh(nullptr), m_ModelMatrix(glm::mat4(1.0f)), m_Position(glm::vec3(0.0f)), m_Color(glm::vec3(1.0f)), m_Scale(glm::vec3(1.0f))
{

}

Model::~Model()
{

}

void Model::Draw(PerspectiveCamera& camera, Material* material, const Light& light)
{
	Shader& shader = *material->MShader;
	shader.Use();
	shader.SetVec3("material.ambient", material->Ambient);
	shader.SetVec3("material.specular", material->Specular);
	shader.SetFloat("material.shininess", material->Shininess);
	shader.SetInt("material.diffuse", 0);

	shader.SetVec3("light.position", light.Position);
	shader.SetVec3("light.ambient", light.Ambient);
	shader.SetVec3("light.diffuse", light.Diffuse);
	shader.SetVec3("light.specular", light.Specular);

	shader.SetFloat("light.constant", light.Constant);
	shader.SetFloat("light.linear", light.Linear);
	shader.SetFloat("light.quadratic", light.Quadratic);

	shader.SetVec3("viewPos", camera.GetPosition());

	shader.SetMat4("model", m_ModelMatrix);
	shader.SetMat4("view", camera.GetViewMatrix());
	shader.SetMat4("projection", camera.GetProjectionMatrix());

	material->DiffuseTexture->Bind(0);
	m_Mesh->Draw();
}

void Model::RecalcModelMatrix()
{
	m_ModelMatrix = glm::mat4(1.0f);
	m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
	m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);
}
