#pragma once

// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdint>
#include <tuple>

class Transforms {
public:
	static void OriginTransform(float* vertices, uint16_t length, glm::vec3 cameraPosition);
	static void RotationTransform(float* vertices, uint16_t length, float rotationCoefficient);
	static void PerspectiveTransform(float* vertices, uint16_t length, float viewDistance);
};
