#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(Shader& shader, glm::mat4 projMat)
{
	this->shader = shader;
	shader.Start();
	shader.LoadProjectionMatrix(projMat);
	shader.Stop();
}

EntityRenderer::~EntityRenderer()
{
}

/*
void EntityRenderer::PrepareStaticModel(StaticModel& model)
{
	Mesh rawMesh = model.mesh;
	glBindVertexArray(rawMesh.GetVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model.texture.GetTextureID());
}

void EntityRenderer::UnbindTexturedMesh()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

void EntityRenderer::PrepareInstance(Entity& entity)
{
	glm::mat4 transformationMatrix = Math::CreateTransformationMatrix(entity.GetPosition(),
		entity.GetRotX(), entity.GetRotY(), entity.GetRotZ(), entity.GetScale());
	shader.LoadTransformationMatrix(transformationMatrix);
}

void EntityRenderer::Render(std::map<unsigned int, std::vector<Entity*>> entities)
{
	for (auto const& i : entities)
	{
		std::pair<unsigned int, std::vector<Entity*>> pair = i;
		StaticModel model = i.second.at(0)->GetModel();
		PrepareStaticModel(model);
		std::vector<Entity*> batch = entities.at(Render(std::vector<Entity*> entities));
		for (Entity* entity : batch)
		{
			PrepareInstance(*entity);
			glDrawElements(GL_TRIANGLES, entity->GetModel().mesh.GetVertexCount(), GL_UNSIGNED_INT, 0);
		}
		UnbindTexturedMesh();
	}

	for (auto const& tm : entities)
	{
		StaticModel model = tm.first;
		PrepareStaticModel(model);
		std::vector<Entity*> batch = entities.at(model);
		for (Entity* entity : batch)
		{
			PrepareInstance(*entity);
			glDrawElements(GL_TRIANGLES, entity->GetModel().mesh.GetVertexCount(), GL_UNSIGNED_INT, 0);
		}
		UnbindTexturedMesh();
	}
}
*/

void EntityRenderer::Render(std::vector<Entity*> entities)
{
	for (Entity* entity : entities)
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
}



