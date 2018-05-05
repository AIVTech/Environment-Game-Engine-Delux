#include "DisplayManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

DisplayManager::DisplayManager()
{
}

DisplayManager::~DisplayManager()
{
}

bool DisplayManager::CreateDisplay(int width, int height, const char* title)
{
	this->screen_width = width;
	this->screen_height = height;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}
}

bool DisplayManager::WindowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void DisplayManager::Update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void DisplayManager::Destroy()
{
	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
