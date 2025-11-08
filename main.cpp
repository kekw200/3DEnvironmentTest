#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GLFW/glfw3native.h>

void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	glfwSetErrorCallback(error_callback);
	if (glfwInit() != GLFW_TRUE)
	{ 
		return 1;
	}

	// TODO: Check if can do with lower version (probably yes)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(600, 400, "Epic game", NULL, NULL);
	if (!mainWindow)
	{
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(mainWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Error initializing GLAD.";
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, 600, 400);
	// TODO: add Vsync toggApple
	glfwSwapInterval(1);

	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

	while (!glfwWindowShouldClose(mainWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void error_callback(int error, const char* description)
{
	std::cerr << description;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
