#ifndef MATERIAL_H
#define MATERIAL_H

#include "Component.h"
#include <string>
#include <GL\glew.h>

#include <glm/glm.hpp>
using glm::vec4;

using namespace std;

class Material : public Component
{
public:
	Material();
	~Material();

	void destroy();
	bool loadShader(const string& vertexShader, const string& fragmentShader);
	void Bind();
	GLint getUniformLocation(const string& name);

	vec4& getAmbientColour();
	void setAmbientColour(float r, float g, float b, float a);

	vec4& getDiffuseColour();
	void setDiffuseColour(float r, float g, float b, float a);

	vec4& getSpecularColour();
	void setSpecularColour(float r, float g, float b, float a);
	
	float getSpecularPower();
	void setSpecularPower(float power);
private:
	GLuint m_ShaderProgram;

	vec4 m_AmbientColour;
	vec4 m_DiffuseColour;
	vec4 m_SpecularColour;
	float m_SpecularPower;
};

#endif 