#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera():
	m_ProjectionMatrix(glm::mat4(1.0f)), m_ViewMatrix(glm::mat4(1.0f))
{
}

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float near, float far)
	: m_ProjectionMatrix(glm::perspective(fov, aspectRatio, near, far)), m_ViewMatrix(glm::mat4(1.0f))
{
	m_ViewMatrix = glm::translate(m_ViewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
}

PerspectiveCamera::~PerspectiveCamera()
{
}
