#include "Material.h"
#include "Shader.h"

Material::Material()
{

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
	
	GLuint fragmentShaderProgram = 0;
	std::string fsPath = fragmentShader;
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
	
	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);
	
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
	
	glBindAttribLocation(m_ShaderProgram, 0, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram, 1, "vertexTexCoords");
	glBindAttribLocation(m_ShaderProgram, 2, "vertexColour");

	return true;
}

void Material::Bind()
{
	glUseProgram(m_ShaderProgram);
}

GLint Material::getUniformLocation(const string& name)
{
	GLint MVPLocation = glGetUniformLocation(m_ShaderProgram, name.c_str());
	return MVPLocation;
}