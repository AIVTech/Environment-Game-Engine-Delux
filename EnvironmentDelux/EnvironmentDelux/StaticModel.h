#ifndef STATICMODEL_H
#define STATICMODEL_H

#include "MeshTexture.h"
#include "Mesh.h"

class StaticModel
{
public:
	StaticModel() {}
	StaticModel(Mesh mesh) { this->mesh = mesh; }
	StaticModel(Mesh mesh, MeshTexture texture) { this->mesh = mesh; this->texture = texture; }

	Mesh mesh = Mesh(0, 0);
	MeshTexture texture = MeshTexture(0);
};

#endif // !STATICMODEL_H