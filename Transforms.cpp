// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// C/C++ includes
#include <cstdint>
#include <cmath>
#include <tuple>
#include <vector>

// Own includes
#include "Transforms.h"

// All this could probably be done by the vertex shader, will be moved over if I get it working here first

void Transforms::OriginTransform(float* vertices, uint16_t length, glm::vec3 cameraPosition)
{
	for (int i = 0; i < length; i += 3)
	{
		vertices[i + 0] -= cameraPosition.x;
		vertices[i + 1] -= cameraPosition.y;
		vertices[i + 2] -= cameraPosition.z;
	}
}

void Transforms::RotationTransform(float* vertices, uint16_t length, float rotationCoefficient)
{
	// TODO!
}

void Transforms::PerspectiveTransform(float* vertices, uint16_t length, float viewDistance) 
{
	// presumes already transformed so that FPM (first plane midpoint) is already at (0, 0, 0)
	float viewStart = 0.1;
	float startHorizontalSpan = 0.3;
	float startVerticalSpan = 0.3;

	float endHorizontalSpan = 20;
	float endVerticalSpan = 20;
	float horizontalChange = endHorizontalSpan - startHorizontalSpan;
	float verticalChange = endVerticalSpan - startVerticalSpan;
	
	for (int i = 0; i < length; i += 3)
	{
		float zDist = vertices[i + 2] / viewDistance;
		float xScale = startVerticalSpan + verticalChange * zDist;
		float yScale = startHorizontalSpan + horizontalChange * zDist;

		vertices[i + 0] /= xScale;
		vertices[i + 1] /= yScale;
		vertices[i + 2] = zDist;
	}
}

