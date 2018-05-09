#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(TerrainShader& shader, glm::mat4 projMat)
{
	this->shader = shader;
	shader.Start();
	shader.LoadProjectionMatrix(projMat);
	shader.Stop();
}

TerrainRenderer::~TerrainRenderer()
{

}

void TerrainRenderer::Render(std::vector<Terrain*> terrains)
{
	for (Terrain* terrain : terrains)
	{
		glBindVertexArray(terrain->GetMesh().GetVaoID());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, terrain->GetTexture().GetTextureID());

		glm::mat4 transformationMatrix = Math::CreateTransformationMatrix(glm::vec3(terrain->GetPosX(), 0, terrain->GetPosZ()),
			0, 0, 0, 1);
		shader.LoadTransformationMatrix(transformationMatrix);

		glDrawElements(GL_TRIANGLES, terrain->GetMesh().GetVertexCount(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
	}
}


