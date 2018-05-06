#include "Renderer.h"

Renderer::Renderer(Shader& shader, DisplayManager* display)
{
	this->shader = shader;
	this->display = *display;
	CreateProjectionMatrix();
	shader.Start();
	shader.LoadProjectionMatrix(projectionMatrix);
	shader.Stop();
}

Renderer::~Renderer()
{
}

void Renderer::Prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(Entity* entity)
{
	glBindVertexArray(entity->GetModel().mesh.GetVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entity->GetModel().texture.GetTextureID());

	glm::mat4 transformationMatrix = Math::CreateTransformationMatrix(entity->GetPosition(),
		entity->GetRotX(), entity->GetRotY(), entity->GetRotZ(), entity->GetScale());
	shader.LoadTransformationMatrix(transformationMatrix);

	glDrawElements(GL_TRIANGLES, entity->GetModel().mesh.GetVertexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

void Renderer::CreateProjectionMatrix()
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

