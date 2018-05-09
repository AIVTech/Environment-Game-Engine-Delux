#ifndef CORERENDERER_H
#define CORERENDERER_H

#include <glad\glad.h>
#include <glad/glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <map>
#include "Maths.h"
#include "Shader.h"
#include "TerrainShader.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "Entity.h"
#include "DisplayManager.h"


class CoreRenderer
{
public:
	CoreRenderer(DisplayManager* display);

	void Prepare();
	void RenderScene(std::vector<Entity*> entities, Camera camera, std::vector<Terrain*> terrains);
	//void ProcessEntity(Entity* entity);
	void CleanUp();

	~CoreRenderer();

private:
	DisplayManager display;
	
	// Shaders
	Shader shader;
	TerrainShader terrainShader;

	// Sub-renderers
	EntityRenderer entityRenderer;
	TerrainRenderer terrainRenderer;

	// projection matrix
	float fov = 60;
	float near_plane = 0.1f;
	float far_plane = 1000.0f;

	glm::mat4 projectionMatrix;
	void CreateProjectionMatrix();

	// entities
	//std::map<unsigned int, std::vector<Entity*>> entities;
};

#endif