#include "Material.h"
#include "Shader.h"
#include "Texture.h"

Material::Material()
{
	m_Type = "Material";
	m_ShaderProgram = -1;
	m_AmbientColour = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	m_DiffuseColour = vec4(0.75f, 0.75f, 0.75f, 1.0f);
	m_SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecularPower = 200.0f;
	m_DiffuseMap = 0;
}

Material::~Material()
{

}

void Material::destroy()
{
	glDeleteProgram(m_ShaderProgram);
	glDeleteTextures(1, &m_DiffuseMap);
}

bool Material::loadShader(const string& vertexShader, const string& fragmentShader)
{
	GLuint vertexShaderProgram = 0;
	std::string vsPath = vertexShader;
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
	//vertexShaderProgram = loadShaderFromFile(const_cast<std::string&>(vertexShader), VERTEX_SHADER);
	
	GLuint fragmentShaderProgram = 0;
	std::string fsPath = fragmentShader;
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
	//fragmentShaderProgram = loadShaderFromFile(const_cast<std::string&>(fragmentShader), FRAGMENT_SHADER);
	
	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);
	
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
	
	glBindAttribLocation(m_ShaderProgram, 0, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram, 1, "vertexNormals");
	glBindAttribLocation(m_ShaderProgram, 2, "vertexTexCoords");
	
	return true;
}

void Material::Bind()
{
	glUseProgram(m_ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseMap);
}

GLint Material::getUniformLocation(const string& name)
{
	GLint MVPLocation = glGetUniformLocation(m_ShaderProgram, name.c_str());
	return MVPLocation;
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

GLuint Material::getDiffuseMap()
{
	return m_DiffuseMap;
}

void Material::loadDiffuseMap(const std::string& filename)
{
	m_DiffuseMap = loadTextureFromFile(filename);
}