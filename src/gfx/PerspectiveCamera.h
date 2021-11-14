#pragma once

#include <glm/glm.hpp>

class PerspectiveCamera
{
public:
	PerspectiveCamera();
	PerspectiveCamera(float fov, float aspectRatio, float near, float far);
	~PerspectiveCamera();


	const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
	const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }

private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
};