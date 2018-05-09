#include "CoreRenderer.h"

CoreRenderer::CoreRenderer(DisplayManager* display)
{
	this->display = *display;
	CreateProjectionMatrix();
	this->shader = Shader();
	this->terrainShader = TerrainShader();
	this->entityRenderer = EntityRenderer(shader, projectionMatrix);
	this->terrainRenderer = TerrainRenderer(terrainShader, projectionMatrix);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

CoreRenderer::~CoreRenderer()
{
}

void CoreRenderer::Prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CoreRenderer::RenderScene(std::vector<Entity*> entities, Camera camera, std::vector<Terrain*> terrains)
{
	Prepare();

	// rendering entities
	shader.Start();
	shader.LoadViewMatrix(camera);
	entityRenderer.Render(entities);
	shader.Stop();

	// rendering terrains
	terrainShader.Start();
	terrainShader.LoadViewMatrix(camera);
	terrainRenderer.Render(terrains);
	terrainShader.Stop();

	entities.clear();
}

/*
void CoreRenderer::ProcessEntity(Entity* entity)
{
	std::cout << entities.size() << "\n";
	StaticModel model = entity->GetModel();
	if (entities.size() == 0)
	{
		std::vector<Entity*> newBatch;
		newBatch.push_back(entity);
		std::pair<unsigned int, std::vector<Entity*>> newPair(model.texture.GetTextureID(), newBatch);
		entities.insert(newPair);
	}
	else
	{
		std::cout << entities.size() << "  |  id: " << model.texture.GetTextureID() << "\n";
		std::vector<Entity*> batch;
		if (entities.find(model.texture.GetTextureID()) == entities.end())
		{
			// not found
			std::vector<Entity*> newBatch;
			newBatch.push_back(entity);
			std::pair<unsigned int, std::vector<Entity*>> newPair(model.texture.GetTextureID(), newBatch);
			entities.insert(newPair);
		}
		else
		{
			// found
			batch = entities.at(model.texture.GetTextureID());
			batch.push_back(entity);
		}
	}
}
*/

void CoreRenderer::CleanUp()
{
	shader.CleanUp();
	terrainShader.CleanUp();
}

void CoreRenderer::CreateProjectionMatrix()
{
	float aspectRatio = (float)display.GetScreenWidth() / (float)display.GetScreenHeight();
	float factor = fov / 2.0f;
	float factorResult = factor * 3.141592653589793 / 180.0f;
	float y_scale = (float)((1.0f / tanf(factorResult)) * aspectRatio);
	float x_scale = y_scale / aspectRatio;
	float frustum_length = far_plane - near_plane;

	projectionMatrix = glm::mat4(1.0);
	projectionMatrix[0][0] = x_scale;
	projectionMatrix[1][1] = y_scale;
	projectionMatrix[2][2] = -((far_plane + near_plane) / frustum_length);
	projectionMatrix[2][3] = -1;
	projectionMatrix[3][2] = -((2 * near_plane * far_plane) / frustum_length);
	projectionMatrix[3][3] = 0;
}


