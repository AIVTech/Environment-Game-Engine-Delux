#include "ModelManager.h"

ModelManager::ModelManager(StaticLoader loader)
{
	this->loader = loader;
	LoadModels();
}

void ModelManager::LoadModels()
{
	Stall.mesh = loader.LoadAssimpMesh("Assets/Models/stall.obj");
	Stall.texture = MeshTexture(loader.LoadTexture("Assets/Textures/stallTexture.png"));

	Farmhouse.mesh = loader.LoadAssimpMesh("Assets/Models/farmhouse.obj");
	Farmhouse.texture = MeshTexture(loader.LoadTexture("Assets/Textures/farmhouseTexture.jpg"));

	Pine.mesh = loader.LoadAssimpMesh("Assets/Models/pine.obj");
	Pine.texture = MeshTexture(loader.LoadTexture("Assets/Textures/pine.png"));
}

