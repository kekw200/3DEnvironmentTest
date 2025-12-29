#pragma once

// C++ includes
#include <cstdint>
#include <vector>
#include <tuple>

// Own includes

class Mesh3D {
	unsigned int floatsize = sizeof(float);

	float* _vertices = nullptr;
	unsigned int* _faces = nullptr;
	uint16_t _lengthVertices = 0;
	uint16_t _lengthFaces = 0;
	bool _initializedVertices = false;
	bool _initializedFaces = false;
	bool _externalShader = true;

	unsigned int _vertexPositionBuffer = 0;
	unsigned int _VAO = 0;
	unsigned int _EBO = 0;
	unsigned int _shaderProgram = 0;

public:
	float* transformedVertices = nullptr;
	std::tuple<float, float, float> position = { 0, 0, 0 };
	float orientation = 0;

	Mesh3D();
	~Mesh3D();

	bool SetVertices(float* vertices, uint16_t length);
	bool SetFaces(unsigned int* faces, uint16_t length);

	const float* GetVertices();
	const unsigned int* GetFaces();
	const uint16_t GetLengthVertices();
	const uint16_t GetLengthFaces();

	const unsigned int GetShaderProgram();

	void SetupBuffers();
	void DeleteBuffers();
	bool SetupShaders();
	void LoadExternalShaders(unsigned int shaderProgram);
	void DeleteShaders();
	bool Draw();
	bool Draw2();
};
