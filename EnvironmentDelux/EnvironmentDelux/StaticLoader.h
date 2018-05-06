#ifndef STATICLOADER_H
#define STATICLOADER_H

#include "Mesh.h"
#include "VAO.h"
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class StaticLoader
{
public:
	StaticLoader();

	Mesh LoadMesh(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<int> indices);
	Mesh LoadAssimpMesh(const char* modelPath);
	unsigned int LoadTexture(const char* filepath);
	void CleanUp();

	~StaticLoader();

private:
	std::vector<VAO> vaos;
	std::vector<unsigned int> textures;
};

#endif // !STATICLOADER_H