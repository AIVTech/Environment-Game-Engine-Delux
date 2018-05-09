#ifndef TERRAIN_H
#define TERRAIN_H

#include "Mesh.h"
#include "MeshTexture.h"
#include "StaticLoader.h"

class Terrain
{
public:
	Terrain() {}
	Terrain(int gridX, int gridZ, StaticLoader loader, MeshTexture texture)
	{
		this->texture = texture;
		this->x = gridX * SIZE;
		this->z = gridZ * SIZE;
		this->mesh = GenerateTerrain(loader);
	}

	float GetPosX() { return this->x; }
	float GetPosZ() { return this->z; }
	Mesh GetMesh() { return this->mesh; }
	MeshTexture GetTexture() { return this->texture; }

private:
	const float SIZE = 800;
	const int VERTEX_COUNT = 120;
	float x, z;
	Mesh mesh;
	MeshTexture texture;
	Mesh GenerateTerrain(StaticLoader loader);
};

#endif // 
