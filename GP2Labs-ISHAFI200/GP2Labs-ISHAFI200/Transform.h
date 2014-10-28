#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

//maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform : public Component
{
public:
	Transform();
	~Transform();
	
	void update();

	vec3 getPosition();
	vec3 getScale();
	vec3 getRotation();
	mat4 getModel();

	void setPosition(vec3 position);
	void setScale(vec3 scale);
	void setRotation(vec3 rotation);
protected:
private:
	vec3 m_Position;
	vec3 m_Scale;
	vec3 m_Rotation;
	mat4 m_Model;
};

#endif