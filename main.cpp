// GLFW includes
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// IMGUI includes
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// C++ includes
#include <iostream>
#include <fstream>
#include <vector>

// C includes
#include <string.h>

// own includes
#include "Mesh3D.h"
#include "Helpers.h"
#include "Transforms.h"
#include "objects.h"
#include "Camera.h"

// custom declarations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void process_movement(double deltaTime);


Camera camera;
bool keys[1024];
std::tuple<bool, bool, bool, bool> pressed = { false, false, false, false };

int main()
{
	glfwSetErrorCallback(error_callback);
	if (glfwInit() != GLFW_TRUE)
	{ 
		return 1;
	}

	// TODO: probably don't need version this high
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
	// TODO	
	glfwSwapInterval(1);

	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

	// object data from "objects.h" for now 	
	

	Mesh3D triangle1, triangle2, rectangleLeft, rectangleRight, box1, box2;

	std::vector<Mesh3D> meshes = { box1, box2, rectangleLeft, rectangleRight };

	for (Mesh3D& mesh : meshes)
	{
		mesh.SetupBuffers();
		mesh.SetupShaders();
	}
	
	meshes[0].SetVertices(box1coords, 8 * 3);
	meshes[1].SetVertices(box2coords, 8 * 3);
	meshes[2].SetVertices(rectangle1coords, 12);
	meshes[3].SetVertices(rectangle2coords, 12);

	meshes[0].SetFaces(boxFaces, 6 * 2 * 3);
	meshes[1].SetFaces(boxFaces, 6 * 2 * 3);
	meshes[2].SetFaces(rectangleFaces, 6);
	meshes[3].SetFaces(rectangleFaces, 6);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glfwSetKeyCallback(mainWindow, key_callback);

	double lastTime = glfwGetTime(), currentTime;
	double deltaTime;
	
	while (!glfwWindowShouldClose(mainWindow))
	{
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;

		// input process
		glfwPollEvents();
		process_movement(deltaTime);
		// END input processing

		lastTime = glfwGetTime();

		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// TRANSFORMATIONS		
		for (Mesh3D& mesh : meshes)
		{
			const float* vertices = mesh.GetVertices();
			std::copy(vertices, vertices + mesh.GetLengthVertices(), mesh.transformedVertices);

			Transforms::OriginTransform(mesh.transformedVertices, mesh.GetLengthVertices(), camera.position);
			Transforms::RotationTransform(mesh.transformedVertices, mesh.GetLengthVertices(), 0);
			Transforms::PerspectiveTransform(mesh.transformedVertices, mesh.GetLengthVertices(), 20);
			mesh.Draw();
		}
		glfwSwapBuffers(mainWindow);
	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		keys[key] = true;
		if (key == GLFW_KEY_LEFT_SHIFT) { camera.speedMult = 2; }
	}
	if (action == GLFW_RELEASE)
	{
		keys[key] = false;
		if (key == GLFW_KEY_LEFT_SHIFT) { camera.speedMult = 1; }
	}
}


void process_movement(double deltaTime)
{
	if (keys[GLFW_KEY_W])
	{
		camera.Move(GLFW_KEY_W, deltaTime);
	}
	if (keys[GLFW_KEY_S])
	{
		camera.Move(GLFW_KEY_S, deltaTime);
	}
	if (keys[GLFW_KEY_A])
	{
		camera.Move(GLFW_KEY_A, deltaTime);
	}
	if (keys[GLFW_KEY_D])
	{
		camera.Move(GLFW_KEY_D, deltaTime);
	}
	if (keys[GLFW_KEY_SPACE])
	{
		camera.Move(GLFW_KEY_SPACE, deltaTime);
	}
	if (keys[GLFW_KEY_LEFT_CONTROL]) {
		camera.Move(GLFW_KEY_LEFT_CONTROL, deltaTime);
	}
}

