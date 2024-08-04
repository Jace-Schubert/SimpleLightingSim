#pragma once
#include "vendor/glm/glm.hpp"

class Camera
{
public:
	Camera(glm::vec3 position);
	~Camera();
	void SetPos(glm::vec3 newPos);
	glm::vec3 GetPos();
	void SetSpeed(float newSpeed);
	float GetSpeed();
	void SetZoom(float zoom);
	float GetZoom();
	glm::vec3 GetForwardVec();
	glm::vec3 GetUpVec();
	void Rotate(float pitch, float yaw);
private:
	glm::vec3 m_Position;
	glm::vec3 m_Forward;
	glm::vec3 m_Up;
	float m_Speed;
	float m_Pitch;
	float m_Yaw;
	float m_Zoom;
};