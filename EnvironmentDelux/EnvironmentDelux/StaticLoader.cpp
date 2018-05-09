#include "StaticLoader.h"

StaticLoader::StaticLoader()
{
}

StaticLoader::~StaticLoader()
{
}

Mesh StaticLoader::LoadMesh(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<int> indices)
{
	VAO vao = VAO();
	vao.AddIndexBuffer(indices);
	vao.AddAtributef(0, 3, vertices);
	vao.AddAtributef(1, 2, textureCoords);
	vaos.push_back(vao);
	return Mesh(vao.GetID(), indices.size());
}

unsigned int StaticLoader::LoadTexture(const char* filepath)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
											// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load(filepath, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.2f);
	}
	else
	{
		// Failed to Load Texture
	}
	stbi_image_free(data);
	textures.push_back(textureID);
	return textureID;
}

void StaticLoader::CleanUp()
{
	// Delete VAOs
	for (VAO vao : vaos)
	{
		vao.DeleteVbos();
		glDeleteVertexArrays(1, &vao.GetID());
	}

	// Delete Textures
	for (unsigned int texture : textures)
	{
		glDeleteTextures(1, &texture);
	}
}

Mesh StaticLoader::LoadAssimpMesh(const char* modelPath)
{
	Assimp::Importer aiImporter;
	const aiScene* scene = aiImporter.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		return Mesh();
	}

	aiMesh* mesh = scene->mMeshes[0];

	std::vector<float> vertices;
	std::vector<float> uvs;
	std::vector<int> indices;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);

		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			uvs.push_back(mesh->mTextureCoords[0][i].x);
			uvs.push_back(1 - mesh->mTextureCoords[0][i].y);
			//std::cout << mesh->mTextureCoords[0][i].x << ", " << 1 - mesh->mTextureCoords[0][i].y << "\n";
		}
		else
		{
			uvs.push_back(0.0f);
			uvs.push_back(0.0f);
		}

		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
	}
	//std::cout << "UVS total: " << uvs.size() << "\n";

	return LoadMesh(vertices, uvs, indices);
}

