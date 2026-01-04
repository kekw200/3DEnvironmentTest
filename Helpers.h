#pragma once

// C++ includes
#include <tuple>
#include <vector>
#include <string>

// C includes
#include <string.h>

// probably delete
typedef struct triangleStruct {
	std::tuple<float, float, float> A;
	std::tuple<float, float, float> B;
	std::tuple<float, float, float> C;
} triangle;


const char* read_file_into_chararray(const std::string& filename);
void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
bool load_compile_shader(GLenum shaderType, const char* filename, unsigned int& shader);
bool attach_link_program(std::vector<unsigned int> shaders, unsigned int& program);
