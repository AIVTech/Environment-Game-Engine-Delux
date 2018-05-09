#pragma once

#include <glad\glad.h>
#include "Mesh.h"
#include "TexturedMesh.h"
#include <glad/glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Maths.h"
#include "Shader.h"
#include "Entity.h"
#include "DisplayManager.h"
#include <map>
#include <vector>

class EntityRenderer
{
public:
	EntityRenderer() {}
	EntityRenderer(Shader& shader, glm::mat4 projMat);

	//void Render(std::map<unsigned int, std::vector<Entity*>> entities);
	void Render(std::vector<Entity*> entities);

	~EntityRenderer();

private:
	Shader shader;

	//void PrepareStaticModel(StaticModel& model);
	//void UnbindTexturedMesh();
	//void PrepareInstance(Entity& entity);
};

