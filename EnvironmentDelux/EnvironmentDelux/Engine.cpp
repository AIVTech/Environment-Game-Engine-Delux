#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>

// Local Includes
#include "DisplayManager.h"
#include "StaticLoader.h"
#include "Shader.h"
#include "CoreRenderer.h"
#include "StaticModel.h"
#include "Entity.h"
#include "Terrain.h"
#include "Camera.h"
#include "ModelManager.h"

int main()
{
	DisplayManager display = DisplayManager();
	display.CreateDisplay(1600, 1040, "Environment Delux");

	StaticLoader loader = StaticLoader();
	CoreRenderer renderer = CoreRenderer(&display);
	ModelManager models = ModelManager(loader);

	std::vector<float> vertices = {
		-0.5f,0.5f,0,
		-0.5f,-0.5f,0,
		0.5f,-0.5f,0,
		0.5f,0.5f,0,

		-0.5f,0.5f,1,
		-0.5f,-0.5f,1,
		0.5f,-0.5f,1,
		0.5f,0.5f,1,

		0.5f,0.5f,0,
		0.5f,-0.5f,0,
		0.5f,-0.5f,1,
		0.5f,0.5f,1,

		-0.5f,0.5f,0,
		-0.5f,-0.5f,0,
		-0.5f,-0.5f,1,
		-0.5f,0.5f,1,

		-0.5f,0.5f,1,
		-0.5f,0.5f,0,
		0.5f,0.5f,0,
		0.5f,0.5f,1,

		-0.5f,-0.5f,1,
		-0.5f,-0.5f,0,
		0.5f,-0.5f,0,
		0.5f,-0.5f,1

	};

	std::vector<float> textureCoords = {
	
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0
		
	};

	std::vector<int> indices = {

		0,1,3,
		3,1,2,
		4,5,7,
		7,5,6,
		8,9,11,
		11,9,10,
		12,13,15,
		15,13,14,
		16,17,19,
		19,17,18,
		20,21,23,
		23,21,22

	};

	StaticModel cubeModel;
	cubeModel.mesh = loader.LoadMesh(vertices, textureCoords, indices);
	cubeModel.texture = MeshTexture(loader.LoadTexture("Assets/Textures/woodenCrate.png"));
	Entity* cube = new Entity(cubeModel, glm::vec3(0, 0.5f, -12), 0, 0, 0, 1);

	std::vector<Entity*> entities;
	std::vector<Terrain*> terrains;
	Entity* stall = new Entity(models.Stall, glm::vec3(2, 0, -16), 0, 150, 0, 0.2f);
	Entity* farmhouse = new Entity(models.Farmhouse, glm::vec3(2, 0, -36), 0, 0, 0, 0.2f);
	Entity* pineTree = new Entity(models.Pine, glm::vec3(-3, 0, -18), 0, 0, 0, 0.22f);
	entities.push_back(stall);
	entities.push_back(farmhouse);
	entities.push_back(pineTree);
	
	for (int i = 0; i < 100; i++)
	{
		Entity* fern = new Entity(models.Fern, glm::vec3(rand() % 100 - 50, -0.2f, rand() % 100 - 100), 0, 0, 0, 0.2f);
		entities.push_back(fern);
	}

	Camera camera = Camera(&display);

	Terrain* terrain = new Terrain(0, -1, loader, MeshTexture(loader.LoadTexture("Assets/Textures/desertGround.jpg")));
	Terrain* terrain2 = new Terrain(-1, -1, loader, MeshTexture(loader.LoadTexture("Assets/Textures/desertGround.jpg")));
	terrains.push_back(terrain);
	terrains.push_back(terrain2);

	while (!display.WindowShouldClose())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (glfwGetKey(display.GetWindow(), GLFW_KEY_1) == GLFW_PRESS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		// Logic
		camera.Move();

		// Rendering
		renderer.RenderScene(entities, camera, terrains);

		// Update Display
		display.Update();
	}

	// Clean Up
	loader.CleanUp();
	renderer.CleanUp();

	display.Destroy();

	return 0;
}