#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>

// Local Includes
#include "DisplayManager.h"
#include "Loader.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "MeshTexture.h"
#include "TexturedMesh.h"
#include "Entity.h"
#include "Camera.h"

int main()
{
	DisplayManager display = DisplayManager();
	display.CreateDisplay(1600, 1040, "Environment Delux");

	Loader loader = Loader();
	Shader shader = Shader();
	Renderer renderer = Renderer(shader, &display);

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

	Mesh* rawQuad = loader.LoadMesh(vertices, textureCoords, indices);
	TexturedMesh* texturedQuad = new TexturedMesh(*rawQuad, MeshTexture(loader.LoadTexture("Assets/Textures/brick.jpg")));
	Entity* quad = new Entity(*texturedQuad, glm::vec3(0, 0, -12), 0, 0, 0, 1);

	Mesh* stallRawModel = loader.LoadAssimpMesh("Assets/Models/stall.obj");
	TexturedMesh* texturedStall = new TexturedMesh(*stallRawModel, MeshTexture(loader.LoadTexture("Assets/Textures/stallTexture.png")));
	Entity* stall = new Entity(*texturedStall, glm::vec3(2, -0.5f, -16), 0, 0, 0, 0.2f);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Camera camera = Camera(&display);

	while (!display.WindowShouldClose())
	{
		// Logic
		quad->IncreaseRotation(0.3f, 0.3f, 0.3f);
		stall->IncreaseRotation(0, 0.4f, 0);
		camera.Move();

		// Rendering
		renderer.Prepare();
		shader.Start();
		shader.LoadViewMatrix(camera);

		renderer.Render(quad);
		//renderer.Render(stall);

		shader.Stop();
		// Update Display
		display.Update();
	}

	// Clean Up
	loader.CleanUp();
	shader.CleanUp();

	display.Destroy();

	return 0;
}