#pragma once

// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// C++ includes
#include <cstdint>
#include <vector>
#include <tuple>

// Own includes



class Camera {
private:
	double speedPerSec = 2;

public:
	glm::vec3 position = { 0, 0, 0 };
	int speedMult = 1;
	Camera();
	void Move(int key, double deltaTime);
};
