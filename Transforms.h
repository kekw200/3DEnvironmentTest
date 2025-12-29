#pragma once
#include <cstdint>
#include <tuple>

class Transforms {
public:
	static void OriginTransform(float* vertices, uint16_t length, std::tuple<float, float, float> cameraPosition);
	static void RotationTransform(float* vertices, uint16_t length, float rotationCoefficient);
	static void PerspectiveTransform(float* vertices, uint16_t length, float viewDistance);
};
