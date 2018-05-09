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
	TerrainRenderer() {}
	TerrainRenderer(TerrainShader& shader, glm::mat4 projMat);

	void Prepare();
	void Render(std::vector<Terrain*> terrains);

	~TerrainRenderer();

private:
	TerrainShader shader;
};

#endif // !TERRAINRENDERER_H