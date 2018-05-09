#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW\glfw3.h>
#include "DisplayManager.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
public:
	Camera(DisplayManager* display) { this->display = display; }
	
	glm::vec3 GetPosition() { return this->position; }
	float GetPitch() { return this->pitch; }
	float GetYaw() { return this->yaw; }
	float GetRoll() { return this->roll; }

	void Move()
	{
		if (glfwGetKey(display->GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) // run
		{
			movingSensitivity = 0.12f;
		}
		if (glfwGetKey(display->GetWindow(), GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS) // normal speed
		{
			movingSensitivity = 0.08f;
		}
		if (glfwGetKey(display->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
		{
			this->position.z -= movingSensitivity;
		}
		if (glfwGetKey(display->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
		{
			this->position.z += movingSensitivity;
		}
		if (glfwGetKey(display->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
		{
			this->position.x -= movingSensitivity;
		}
		if (glfwGetKey(display->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
		{
			this->position.x += movingSensitivity;
		}
		if (glfwGetKey(display->GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			this->yaw += movingSensitivity*3;
		}
		if (glfwGetKey(display->GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			this->yaw -= movingSensitivity*3;
		}
		if (glfwGetKey(display->GetWindow(), GLFW_KEY_UP) == GLFW_PRESS)
		{
			this->position.y += movingSensitivity;
		}
		if (glfwGetKey(display->GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			this->position.y -= movingSensitivity;
			if (position.y < 0.8f)
				position.y = 0.8f;
		}
	}

private:
	float movingSensitivity = 0.08f;
	DisplayManager* display;
	glm::vec3 position = glm::vec3(0, 1.2f, 0);
	float pitch, yaw, roll;
};

#endif