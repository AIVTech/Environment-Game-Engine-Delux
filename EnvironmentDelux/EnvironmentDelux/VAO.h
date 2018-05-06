#ifndef VAO_H
#define VAO_H

#include <glad\glad.h>
#include <vector>

class VAO
{
public:
	VAO();

	void AddAtributef(int attribNum, int size, std::vector<float> data);
	void AddAttributei(int attribNum, int size, std::vector<int> data);
	void AddIndexBuffer(std::vector<int> indices);
	static void Bind(unsigned int id) { glBindVertexArray(id); }
	static void Unbind() { glBindVertexArray(0); }
	void DeleteVbos();

	unsigned int& GetID() { return this->ID; }

	~VAO();

private:
	unsigned int ID;
	std::vector<unsigned int> vbos;
	void bind();
	void unbind();
};

#endif