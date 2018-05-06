#ifndef ANIMATEDMESH_H
#define ANIMATEDMESH_H

class AnimatedMesh
{
public:
	AnimatedMesh() {}
	AnimatedMesh(unsigned int vaoID, int vertexCount)
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

#endif // !ANIMATEDMESH_H