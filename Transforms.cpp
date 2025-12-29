#include "Transforms.h"
#include <cstdint>
#include <cmath>
#include <tuple>
#include <vector>

// All this could probably be done by the vertex shader, will be moved over if I get it working here first

void Transforms::OriginTransform(float* vertices, uint16_t length, std::tuple<float, float, float> cameraPosition)
{
	for (int i = 0; i < length; i += 3)
	{
		vertices[i + 0] -= std::get<0>(cameraPosition);
		vertices[i + 1] -= std::get<1>(cameraPosition);
		vertices[i + 2] -= std::get<2>(cameraPosition);
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
	
	// std::tuple<float, float, float> lustart = { -startHorizontalSpan, startVerticalSpan, viewStart };
	// std::tuple<float, float, float> llstart = { -startHorizontalSpan, -startVerticalSpan, viewStart };
	// std::tuple<float, float, float> rustart = { startHorizontalSpan, startVerticalSpan, viewStart };
	// std::tuple<float, float, float> rlstart = { startHorizontalSpan, -startVerticalSpan, viewStart };

	// viewEnd
	float endHorizontalSpan = 20;
	float endVerticalSpan = 20;
	// std::tuple<float, float, float> luend = { -endHorizontalSpan, endVerticalSpan, viewEnd };
	// std::tuple<float, float, float> llend = { -endHorizontalSpan, -endVerticalSpan, viewEnd };
	// std::tuple<float, float, float> ruend = { endHorizontalSpan, endVerticalSpan, viewEnd };
	// std::tuple<float, float, float> rlend = { endHorizontalSpan, -endVerticalSpan, viewEnd };
	float horizontalChange = endHorizontalSpan - startHorizontalSpan;
	float verticalChange = endVerticalSpan - startVerticalSpan;
	
	for (int i = 0; i < length; i += 3)
	{
		float zDist = vertices[i + 2] / viewDistance;
		// float dist = sqrt(pow(vertices[0 + i], 2) + pow(vertices[1 + i], 2) + pow(vertices[2 + i], 2));
		float xScale = startVerticalSpan + verticalChange * zDist;
		float yScale = startHorizontalSpan + horizontalChange * zDist;

		vertices[i + 0] /= xScale;
		vertices[i + 1] /= yScale;
		vertices[i + 2] = zDist;
	}
}

