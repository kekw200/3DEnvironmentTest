using namespace std;

// GLFW includes
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// Own includes
#include "Mesh3D.h"
#include "Helpers.h"
#include "Camera.h"

Camera::Camera()
{
	
}

void Camera::Move(int key, double deltaTime)
{
	switch (key)
	{
		case GLFW_KEY_W:
			this->position.z += deltaTime * speedPerSec * speedMult;
			break;
		case GLFW_KEY_S:
			this->position.z -= deltaTime * speedPerSec * speedMult;
			break;
		case GLFW_KEY_A:
			this->position.x -= deltaTime * speedPerSec * speedMult;
			break;
		case GLFW_KEY_D:
			this->position.x += deltaTime * speedPerSec * speedMult;
			break;
		case GLFW_KEY_SPACE:
			this->position.y += deltaTime * speedPerSec * speedMult;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			this->position.y -= deltaTime * speedPerSec * speedMult;
			break;
		default:
			break;
	}
}