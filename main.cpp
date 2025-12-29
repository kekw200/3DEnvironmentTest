// GLFW includes
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

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

// custom declarations
const char* read_file_into_chararray(const std::string& filename);
void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
bool load_compile_shader(GLenum shaderType, const char* filename, unsigned int& shader);
bool attach_link_program(std::vector<unsigned int> shaders, unsigned int& program);

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
	// TODO: add Vsync toggle
	glfwSwapInterval(1);

	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

	// GL stuff

	
	float verticesTest[] = {
		-0.5f, -0.5f, 1.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, -1.0f
	};
	


	/* 
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// GL_STREAM_DRAW (set once drawn few times)
	// GL_STATIC_DRAW (set once drawn often - UI?)
	// GL_DYNAMIC_DRAW (changed often drawn often)

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/

	/*
	// setup shaders 
	unsigned int vertexShader, fragmentShader;
	if (!load_compile_shader(GL_VERTEX_SHADER, "basic.vert", vertexShader)) { return 1; }
	if (!load_compile_shader(GL_FRAGMENT_SHADER, "basic.frag", fragmentShader)) { return 1; }

	// attach & link shader program
	unsigned int shaderProgram;
	if (!attach_link_program({ vertexShader, fragmentShader }, shaderProgram)) { return 1; }
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	glUseProgram(shaderProgram);
	*/

	/*
	float triangle1coords[] = {
		0, 0, 10,
		0, 2, 10,
		-2, 5, 10
	};

	float triangle2coords[] = {
		0, 0, 15,
		0, 2, 15,
		2, 2, 15
	};
	*/

	unsigned int triangleFaces[] = {
		0, 1, 2
	};

	float box1coords[] = {
		-8, -10, 10,
		-8, -8, 10,
		8, -10, 10,
		8, -8, 10,
		-8, -10, 15,
		-8, -8, 15,
		8, -10, 15,
		8, -8, 15,
	};

	float box2coords[] = {
		-2, 4, 12,
		-2, 8, 12,
		2, 4, 12,
		2, 8, 12,
		-2, 4, 16,
		-2, 8, 16,
		2, 4, 16,
		2, 8, 16
	};

	unsigned int boxFaces[] = {
		0, 1, 2,
		1, 2, 3,
		0, 1, 4,
		1, 4, 5,
		2, 3, 6,
		3, 6, 7,
		4, 5, 6,
		5, 6, 7,
		1, 3, 5,
		3, 5, 7,
		0, 2, 4,
		2, 4, 6
	};

	float rectangle1coords[] = {
		5, -5, 5,
		5, 5, 5,
		5, -5, 10,
		5, 5, 10
	};

	float rectangle2coords[] = {
		-5, -5, 5,
		-5, 5, 5,
		-5, -5, 10,
		-5, 5, 10
	};

	unsigned int rectangleFaces[] = {
		0, 1, 2,
		3, 2, 1
	};

	Mesh3D camera;

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
	
	while (!glfwWindowShouldClose(mainWindow))
	{
		// CLEAR BUFFERS
		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// GET ALL ELEMENTS READY FOR DRAWING
		
		for (Mesh3D& mesh : meshes)
		{
			const float* vertices = mesh.GetVertices();
			std::copy(vertices, vertices + mesh.GetLengthVertices(), mesh.transformedVertices);

			Transforms::OriginTransform(mesh.transformedVertices, mesh.GetLengthVertices(), camera.position);
			Transforms::RotationTransform(mesh.transformedVertices, mesh.GetLengthVertices(), 0);
			Transforms::PerspectiveTransform(mesh.transformedVertices, mesh.GetLengthVertices(), 20);
			mesh.Draw();
		}

		//glUseProgram(shaderProgram);
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

