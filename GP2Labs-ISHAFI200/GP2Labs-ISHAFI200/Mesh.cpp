#include "Mesh.h"
#include "Vertex.h"

Mesh::Mesh()
{
	m_VBO = 0;
	m_EBO = 0;
	m_VAO = 0;
	m_IndexCount = 0;
	m_VertexCount = 0;
}

Mesh::~Mesh()
{

}

void Mesh::init()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	//Create buffer
	glGenBuffers(1, &m_VBO);
	//Make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//Create buffer
	glGenBuffers(1, &m_EBO);
	//Make the new EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec2)));
}

void Mesh::destroy()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void Mesh::Bind()
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

void Mesh::copyVertexData(int count, int stride, void **data)
{
	m_VertexCount = count;
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, count*stride, data, GL_STATIC_DRAW);
}

void Mesh::copyIndexData(int count, int stride, void **data)
{
	m_IndexCount = count;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*stride, data, GL_STATIC_DRAW);
}

int Mesh::getIndexCount()
{
	return m_IndexCount;
}

int Mesh::getVertexCount()
{
	return m_VertexCount;
}