#include "Camera.h"

Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f))
	: m_Position(position), m_Forward(glm::vec3(0.0f, 0.0f, -1.0f)), m_Up(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_Speed(0.0f), m_Pitch(0.0f), m_Yaw(-90.0f), m_Zoom(45.0f)
{

}

Camera::~Camera()
{

}

void Camera::SetPos(glm::vec3 newPos)
{
	m_Position = newPos;
}

glm::vec3 Camera::GetPos()
{
	return m_Position;
}

void Camera::SetSpeed(float newSpeed)
{
	m_Speed = newSpeed;
}

float Camera::GetSpeed()
{
	return m_Speed;
}

void Camera::SetZoom(float zoom)
{
	if (zoom > 75.0f) { zoom = 75.0f; }
	if (zoom < 1.0f) { zoom = 1.0f; }
	m_Zoom = zoom; 
}

float Camera::GetZoom()
{
	return m_Zoom;
}

glm::vec3 Camera::GetForwardVec()
{
	return m_Forward;
}

glm::vec3 Camera::GetUpVec()
{
	return m_Up;
}

void Camera::Rotate(float pitch, float yaw)
{
	m_Pitch += pitch;
	m_Yaw += yaw;
	if (m_Pitch > 89.0f) { m_Pitch = 89.0f; }
	if (m_Pitch < -89.0f) { m_Pitch = -89.0f; }
	glm::vec3 direction(0.0f);
	direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	direction.y = sin(glm::radians(m_Pitch));
	direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Forward = glm::normalize(direction);
}