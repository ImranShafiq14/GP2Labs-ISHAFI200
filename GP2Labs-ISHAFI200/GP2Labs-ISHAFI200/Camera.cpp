#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

mat4 Camera::getViewMatrix()
{
	return m_ViewMatrix;
}

mat4 Camera::getProjectMatrix()
{
	return m_ProjectionMatrix;
}

void Camera::update()
{
	m_Position = m_Parent->getTransform()->getPosition();
	m_ViewMatrix = glm::lookAt(m_Position, m_LookAt, m_Up);
	m_ProjectionMatrix = glm::ortho(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
}