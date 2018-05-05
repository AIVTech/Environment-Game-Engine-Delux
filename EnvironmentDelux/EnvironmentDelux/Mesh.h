#ifndef MESH_H
#define MESH_H

class Mesh
{
public:
	Mesh() {}
	Mesh(unsigned int vaoID, int vertexCount)
	{
		this->vaoID = vaoID;
		this->vertexCount = vertexCount;
	}

	unsigned int GetVaoID() { return this->vaoID; }
	unsigned int GetVertexCount() { return this->vertexCount; }

private:
	unsigned int vaoID;
	int vertexCount;
};

#endif // !MESH_H