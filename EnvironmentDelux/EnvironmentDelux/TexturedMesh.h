#ifndef TEXTUREDMESH_H
#define TEXTUREDMESH_H

#include "Mesh.h"
#include "MeshTexture.h"

class TexturedMesh
{
public:
	TexturedMesh() {}
	TexturedMesh(Mesh mesh, MeshTexture texture)
	{
		this->mesh = mesh;
		this->texture = texture;
	}

	Mesh GetRawMesh() { return this->mesh; }
	MeshTexture GetTexture() { return this->texture; }

private:
	Mesh mesh;
	MeshTexture texture;
};

#endif // !TEXTUREDMESH_H