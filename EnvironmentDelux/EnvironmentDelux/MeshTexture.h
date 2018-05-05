#ifndef MESHTEXTURE_H
#define MESHTEXTURE_H

class MeshTexture
{
public:
	MeshTexture() {}
	MeshTexture(unsigned int id) 
	{
		this->textureID = id;
	}

	unsigned int GetTextureID() { return this->textureID; }

private:
	unsigned int textureID;
};

#endif // !MESHTEXTURE_H