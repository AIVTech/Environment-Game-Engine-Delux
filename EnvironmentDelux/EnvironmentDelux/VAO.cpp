#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{

}

void VAO::bind()
{
	glBindVertexArray(ID);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

void VAO::AddIndexBuffer(std::vector<int> indices)
{
	bind();
	unsigned int vboID;
	vbos.push_back(vboID);
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
	unbind();
}

void VAO::AddAtributef(int attribNum, int size, std::vector<float> data)
{
	bind();
	unsigned int vboID;
	vbos.push_back(vboID);
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attribNum, size, GL_FLOAT, false, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	unbind();
}

void VAO::AddAttributei(int attribNum, int size, std::vector<int> data)
{
	bind();
	unsigned int vboID;
	vbos.push_back(vboID);
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(int), &data[0], GL_STATIC_DRAW);
	glVertexAttribIPointer(attribNum, size, GL_INT, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	unbind();
}

void VAO::DeleteVbos()
{
	for (unsigned int vbo : vbos)
	{
		glDeleteBuffers(1, &vbo);
	}
}
