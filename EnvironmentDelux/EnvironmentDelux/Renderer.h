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

class Renderer
{
public:
	Renderer(Shader& shader, DisplayManager* display);

	void Prepare();
	void Render(Entity* mesh);

	~Renderer();

private:
	Shader shader;
	DisplayManager display;
	glm::mat4 projectionMatrix;

	float fov = 60;
	float near_plane = 0.1f;
	float far_plane = 1000.0f;

	void CreateProjectionMatrix();
};

