#include "Material.h"
#include "Shader.h"
#include "Vertex.h"

Material::Material()
{
	m_ShaderProgram = -1;
	m_Type = "Material";
	m_AmbientColour = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	m_DiffuseColour = vec4(0.75f, 0.75f, 0.75f, 1.0f);
	m_SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecularPower = 200.0f;
}

Material::~Material()
{

}

void Material::destroy()
{
	glDeleteProgram(m_ShaderProgram);
}

void Material::Bind()
{
	glUseProgram(m_ShaderProgram);
	GLint vertexPosLoc = glGetAttribLocation(m_ShaderProgram, "vertexPosition");
	GLint vertexMormalsLoc = glGetAttribLocation(m_ShaderProgram, "vertexNormals");
	glEnableVertexAttribArray(vertexPosLoc);
	glVertexAttribPointer(vertexPosLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(vertexMormalsLoc);
	glVertexAttribPointer(vertexMormalsLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
}

bool Material::loadShader(const std::string& vsFilename, const std::string& fsFilename)
{
	GLuint vertexShaderProgram = 0;
	vertexShaderProgram = loadShaderFromFile(const_cast<std::string&>(vsFilename), VERTEX_SHADER);

	GLuint fragmentShaderProgram = 0;
	fragmentShaderProgram = loadShaderFromFile(const_cast<std::string&>(fsFilename), FRAGMENT_SHADER);

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

	GLint vertexPosLoc = glGetAttribLocation(m_ShaderProgram, "vertexPosition");
	GLint vertexMormalsLoc = glGetAttribLocation(m_ShaderProgram, "vertexNormals");

	glBindAttribLocation(m_ShaderProgram, vertexPosLoc, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram, vertexMormalsLoc, "vertexNormals");
	//glBindAttribLocation(m_ShaderProgram,2, "vertexTexCoords");
	//glBindAttribLocation(m_ShaderProgram, 3, "vertexColour");

	//Tell the shader that 0 is the position element

	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec3)));
	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec3) + sizeof(vec2)));

	return true;
}

GLint Material::getUniformLocation(const std::string& name)
{
	return glGetUniformLocation(m_ShaderProgram, name.c_str());
}

vec4& Material::getAmbientColour()
{
	return m_AmbientColour;
}

void Material::setAmbientColour(float r, float g, float b, float a)
{
	m_AmbientColour = vec4(r, g, b, a);
}

vec4& Material::getDiffuseColour()
{
	return m_DiffuseColour;
}

void Material::setDiffuseColour(float r, float g, float b, float a)
{
	m_DiffuseColour = vec4(r, g, b, a);
}

vec4& Material::getSpecularColour()
{
	return m_SpecularColour;
}

void Material::setSpecularColour(float r, float g, float b, float a)
{
	m_SpecularColour = vec4(r, g, b, a);
}

float Material::getSpecularPower()
{
	return m_SpecularPower;
}

void Material::setSpecularPower(float power)
{
	m_SpecularPower = power;
}