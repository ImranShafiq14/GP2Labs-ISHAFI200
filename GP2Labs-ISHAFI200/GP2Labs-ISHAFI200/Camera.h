#ifndef CAMERA_H
#define CAMERA_H

#include "Component.h"

//maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera : public Component
{
public:
	Camera();
	~Camera();

	void setPosition(float x, float y, float z)
	{
		m_Position = vec3(x, y, z);
	}
	void setLookAt(float x, float y, float z)
	{
		m_LookAt = vec3(x, y, z);
	}
	void setUp(float x, float y, float z)
	{
		m_Up = vec3(x, y, z);
	}
	void setFOV(float FOV)
	{
		m_FOV = FOV;
	}
	void setAspectRatio(float aspectRatio)
	{
		m_AspectRatio = aspectRatio;
	}
	void setNearClip(float nearClip)
	{
		m_NearClip = nearClip;
	}
	void setFarClip(float farClip)
	{
		m_FarClip = farClip;
	}
	mat4 getViewMatrix();
	mat4 getProjectMatrix();
	void update();
private:
	vec3 m_Position;
	vec3 m_LookAt;
	vec3 m_Up;
	float m_FOV;
	float m_AspectRatio;
	float m_NearClip;
	float m_FarClip;
	mat4 m_ViewMatrix;
	mat4 m_ProjectionMatrix;
};

#endif