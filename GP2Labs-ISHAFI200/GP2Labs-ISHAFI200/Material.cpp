#include "Material.h"
#include "Shader.h"
#include "Vertex.h"

Material::Material()
{
	m_Type = "Material";
	m_ShaderProgram = -1;
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
		
	return true;
}

void Material::Bind()
{
	glUseProgram(m_ShaderProgram);

	GLint vertexPosLocation = glGetAttribLocation(m_ShaderProgram, "vertexPosition");
	GLint vertexNormalsLocation = glGetAttribLocation(m_ShaderProgram, "vertexNormals");
	GLint vertexTexLocation = glGetAttribLocation(m_ShaderProgram, "vertexTexCoords");
	GLint vertexColourLocation = glGetAttribLocation(m_ShaderProgram, "vertexColour");

	glBindAttribLocation(m_ShaderProgram, vertexPosLocation, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram, vertexNormalsLocation, "vertexNormals");
	glBindAttribLocation(m_ShaderProgram, vertexTexLocation, "vertexTexCoords");
	glBindAttribLocation(m_ShaderProgram, vertexColourLocation, "vertexColour");

	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(vertexPosLocation);
	glVertexAttribPointer(vertexPosLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(vertexNormalsLocation);
	glVertexAttribPointer(vertexNormalsLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
	glEnableVertexAttribArray(vertexTexLocation);
	glVertexAttribPointer(vertexTexLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec2)));
	glEnableVertexAttribArray(vertexColourLocation);
	glVertexAttribPointer(vertexColourLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec3) + sizeof(vec2)));
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