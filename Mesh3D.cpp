using namespace std;

// GLFW includes
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// Own includes
#include "Mesh3D.h"
#include "Helpers.h"

Mesh3D::Mesh3D()
{
	this->SetupBuffers();
}

Mesh3D::~Mesh3D()
{
	// if (transformedVertices != nullptr) { free(transformedVertices); }
	this->DeleteBuffers();
	this->DeleteShaders();
}

// This one just trusts length so probably crashes if it's wrong (larger) than the actual array
bool Mesh3D::SetVertices(float* vertices, uint16_t length)
{
	if (length % 3 != 0) { return false; }
	// free(this->_vertices);
	this->_vertices = vertices;

	// TODO: Dynamic allocated array stuff (rn basic vertex data is always just on stack)

	if (transformedVertices != nullptr)
	{
		free(transformedVertices);
		transformedVertices = nullptr;
	}
	// now ideally there are no outside references to the this old public property after it's been freed and reassigned
	// XD
	transformedVertices = (float*)malloc(this->floatsize * length);
	_initializedVertices = true;

	if (_lengthVertices != length)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vertexPositionBuffer);
		glBufferData(GL_ARRAY_BUFFER, length * floatsize, NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	_lengthVertices = length;
	return true;
}

// Trusts length also
bool Mesh3D::SetFaces(unsigned int* faces, uint16_t length)
{
	if (length % 3 != 0) { return false; }
	// free(this->_faces);
	this->_faces = faces;

	_initializedFaces = true;

	if (_lengthFaces != length)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(unsigned int), faces, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	_lengthFaces = length;
	return true;
}

const float* Mesh3D::GetVertices()
{
	return this->_vertices;
}

const unsigned int* Mesh3D::GetFaces()
{
	return this->_faces;
}

const uint16_t Mesh3D::GetLengthVertices()
{
	return this->_lengthVertices;
}

const uint16_t Mesh3D::GetLengthFaces()
{
	return this->_lengthFaces;
}

void Mesh3D::SetupBuffers()
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_vertexPositionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexPositionBuffer);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * floatsize, (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	
	glBindVertexArray(0);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh3D::DeleteBuffers()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_vertexPositionBuffer);
	glDeleteBuffers(1, &_EBO);
}

bool Mesh3D::SetupShaders()
{
	/*
	// if (!_initializedVertices || !_initializedFaces) { return false; }
	if (!_initializedVertices) { return false; }
	
	// unsigned int VAO;
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	// unsigned int VBO;
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _lengthVertices * floatsize, _vertices, GL_STATIC_DRAW);

	// GL_STREAM_DRAW (set once drawn few times)
	// GL_STATIC_DRAW (set once drawn often - UI?)
	// GL_DYNAMIC_DRAW (changed often drawn often)

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/

	// setup shaders 
	unsigned int vertexShader, fragmentShader;
	if (!load_compile_shader(GL_VERTEX_SHADER, "basic.vert", vertexShader)) { return false; }
	if (!load_compile_shader(GL_FRAGMENT_SHADER, "basic.frag", fragmentShader)) { return false; }

	// attach & link shader program
	// unsigned int shaderProgram;
	if (!attach_link_program({ vertexShader, fragmentShader }, _shaderProgram)) { return false; }
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// glUseProgram(_shaderProgram);
	_externalShader = false;
	return true;
}

void Mesh3D::LoadExternalShaders(unsigned int shaderProgram)
{
	_shaderProgram = shaderProgram;
	_externalShader = true;
}

void Mesh3D::DeleteShaders()
{
	if (!_externalShader)
	{
		glDeleteProgram(_shaderProgram);
	}
}

bool Mesh3D::Draw()
{
	if (!_initializedVertices || !_initializedFaces) { return false; }
	glUseProgram(_shaderProgram);
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexPositionBuffer);
	// glBufferData(GL_ARRAY_BUFFER, 9 * floatsize, transformedVertices, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, _lengthVertices * floatsize, transformedVertices);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * floatsize, (void*)0);
	// glEnableVertexAttribArray(0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glDrawElements(GL_TRIANGLES, _lengthFaces, GL_UNSIGNED_INT, 0);
	return true;
}

bool Mesh3D::Draw2() {
	if (!_initializedVertices) { return false; }
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * floatsize, transformedVertices, GL_STATIC_DRAW);

	glUseProgram(_shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


const unsigned int Mesh3D::GetShaderProgram()
{
	return this->_shaderProgram;
}
