#pragma once

#include <glad\glad.h>
#include <vector>
#include <iostream>
#include "Mesh.h"
#include "AnimatedMesh.h"
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Loader
{
public:
	Loader();

	Mesh* LoadMesh(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<int> indices);
	Mesh* LoadAssimpMesh(const char* modelPath);
	AnimatedMesh* LoadAnimatedMesh(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<int> indices, std::vector<float> jointIds, std::vector<float> vertexWeights);
	unsigned int LoadTexture(const char* filepath);
	void CleanUp();

	~Loader();

private:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
	std::vector<unsigned int> textures;

	unsigned int CreateVAO();
	void StoreDataInAttributeList(int attributeNumber, int coordSize, std::vector<float> data);
	void StoreIntInAttributeList(int attributeNumber, int attributeSize, std::vector<int> data);
	void UnbindVAO();
	void BindIndicesBuffer(std::vector<int> indices);
};

