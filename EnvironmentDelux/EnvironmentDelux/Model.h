#ifndef MODEL_H
#define MODEL_H

#include "TexturedMesh.h"
#include <vector>

class Model
{
public:
	Model() {}
	Model(std::vector<TexturedMesh> meshes)
	{
		this->meshes = meshes;
	}

	std::vector<TexturedMesh> GetMeshList() { return this->meshes; }

private:
	std::vector<TexturedMesh> meshes;
};

#endif // !MODEL_H