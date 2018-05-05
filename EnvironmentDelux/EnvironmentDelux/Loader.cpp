#include "Loader.h"

Loader::Loader()
{

}

Loader::~Loader()
{
}

Mesh* Loader::LoadMesh(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<int> indices)
{
	unsigned int vaoID = CreateVAO();
	BindIndicesBuffer(indices);
	StoreDataInAttributeList(0, 3, vertices);
	StoreDataInAttributeList(1, 2, textureCoords);
	UnbindVAO();
	return new Mesh(vaoID, indices.size());
}

unsigned int Loader::LoadTexture(const char* filepath)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
											// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load(filepath, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return textureID;
}

unsigned int Loader::CreateVAO()
{
	unsigned int vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	vaos.push_back(vaoID);
	return vaoID;
}

void Loader::BindIndicesBuffer(std::vector<int> indices)
{
	unsigned int vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(int), &indices[0], GL_STATIC_DRAW);
}

void Loader::StoreDataInAttributeList(int attributeNumber, int coordSize, std::vector<float> data)
{
	unsigned int vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	vbos.push_back(vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordSize, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::UnbindVAO()
{
	glBindVertexArray(0);
}

void Loader::CleanUp()
{
	// Delete VAOs
	for (unsigned int vao : vaos)
	{
		glDeleteVertexArrays(1, &vao);
	}
	// Delete VBOs
	for (unsigned int vbo : vbos)
	{
		glDeleteBuffers(1, &vbo);
	}
	// Delete Textures
	for (unsigned int texture : textures)
	{
		glDeleteTextures(1, &texture);
	}
}

Mesh* Loader::LoadAssimpMesh(const char* modelPath)
{
	Assimp::Importer aiImporter;
	const aiScene* scene = aiImporter.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Failed to Load Model\n";
		return nullptr;
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
			uvs.push_back(mesh->mTextureCoords[0][i].y);
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

	return LoadMesh(vertices, uvs, indices);
}
