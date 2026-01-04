// GLFW includes
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// Own includes
#include "Helpers.h"

// C++ includes
#include <iostream>
#include <fstream>
#include <vector>


bool load_compile_shader(GLenum shaderType, const char* filename, unsigned int& shader)
{
	shader = glCreateShader(shaderType);
	const GLchar* shaderSource = nullptr;
	// const char* shaderSource = read_file_into_chararray(filename);
	if (shaderType == GL_FRAGMENT_SHADER) {
		shaderSource = R"END(
		#version 440 core
		out vec4 FragColor;

		void main()
		{
			FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
		)END";
	}
	else {
		shaderSource = R"END(
		#version 440 core
		layout (location = 0) in vec3 aPos;

		void main()
		{
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
		)END";
	}
		// std::cout << shaderSource << std::endl;
	if (shaderSource == NULL)
	{
		glfwTerminate();
		std::cerr << "Error loading shader source: " << filename << std::endl;
		return false;
	}
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int shader_status;
	char log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);
	if (!shader_status)
	{
		std::cerr << "Error compiling shader: " << filename << '\n';
		glGetShaderInfoLog(shader, 512, NULL, log);
		std::cerr << log << std::endl;
		return false;
	}
	return true;
}

bool attach_link_program(std::vector<unsigned int> shaders, unsigned int& program)
{
	program = glCreateProgram();
	// Don't check for different shader types
	for (unsigned int shader : shaders)
	{
		glAttachShader(program, shader);
	}
	glLinkProgram(program);

	int status;
	char log[512];
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status)
	{
		std::cerr << "Error linking shader program:\n";
		glGetProgramInfoLog(program, 512, NULL, log);
		std::cerr << log << std::endl;
		return false;
	}
	return true;
}

const char* read_file_into_chararray(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) { return NULL; }

	std::string temp;
	file.seekg(0, std::ios::end);
	unsigned int length = file.tellg();
	temp.resize(length);
	file.seekg(0, std::ios::beg);

	file.read(&temp[0], length);

	temp.erase(std::remove(temp.begin(), temp.end(), '\r'), temp.end());
	char* result = new char[length];
	strcpy_s(result, length, temp.c_str());
	return result;
}

void error_callback(int error, const char* description)
{
	std::cerr << description;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}