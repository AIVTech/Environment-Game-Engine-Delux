#include "Entity.h"


Entity::Entity(StaticModel model, glm::vec3 position, float rx, float ry, float rz, float scale)
{
	this->model = model;
	this->position = position;
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
	this->scale = scale;
}


Entity::~Entity()
{
}
