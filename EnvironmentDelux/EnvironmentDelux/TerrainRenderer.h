#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H

#include <glad\glad.h>
#include "Mesh.h"
#include "TexturedMesh.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Maths.h"
#include "TerrainShader.h"
#include "Terrain.h"
#include "DisplayManager.h"

class TerrainRenderer
{ 
public:
	TerrainRenderer(TerrainShader& shader, DisplayManager* display);

	void Prepare();
	void Render(Terrain* terrain);

	~TerrainRenderer();

private:
	TerrainShader shader;
	DisplayManager display;
	glm::mat4 projectionMatrix;

	float fov = 60;
	float near_plane = 0.1f;
	float far_plane = 1000.0f;

	void CreateProjectionMatrix();
};

#endif // !TERRAINRENDERER_H