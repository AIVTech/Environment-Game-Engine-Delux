#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "StaticModel.h"

class Entity
{
public:
	Entity(StaticModel model, glm::vec3 position, float rx, float ry, float rz, float scale);

	StaticModel GetModel() { return this->model; }
	glm::vec3 GetPosition() { return this->position; }
	float GetRotX() { return this->rx; }
	float GetRotY() { return this->ry; }
	float GetRotZ() { return this->rz; }
	float GetScale() { return this->scale; }
	float GetWidth() { return this->Width; }
	float GetHeight() { return this->Height; }

	void IncreasePosition(float dx, float dy, float dz) { this->position.x += dx; this->position.y += dy; this->position.z += dz; }
	void IncreaseRotation(float dx, float dy, float dz) { this->rx += dx; this->ry += dy; this->rz += dz; }

	void SetPosition(glm::vec3 pos) { this->position = pos; }
	void SetWidth(float value) { this->Width = value; }
	void SetHeight(float value) { this->Height = value; }
	void SetScale(float value) { this->scale = value; }

	~Entity();

private:
	StaticModel model;
	glm::vec3 position;
	float rx, ry, rz, scale;
	float Width = 0, Height = 0; // Not absolutely necessery, therefore initially will be 0
};
