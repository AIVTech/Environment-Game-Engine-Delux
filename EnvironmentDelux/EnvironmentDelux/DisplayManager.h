#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

class DisplayManager
{
public:
	DisplayManager();

	bool CreateDisplay(int width, int height, const char* title);
	void Update();
	void Destroy();
	bool WindowShouldClose();

	GLFWwindow* GetWindow() { return this->window; }
	int GetScreenWidth() { return this->screen_width; }
	int GetScreenHeight() { return this->screen_height; }

	~DisplayManager();
private:
	GLFWwindow* window;
	int screen_width = 0;
	int screen_height = 0;
};

