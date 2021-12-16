#ifndef CAMERA_S
#define CAMERA_S

#include <glm/glm.hpp>
#include <glfw/glfw3.h>

class Camera
{
public:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float speed = 20.0f;
	float pitch = 0.0f;
	float yaw = -90.0f;
	float mouseSensitivity = 0.1f;
	float fov = 45.0f;
	float nearClip = 0.1f;
	float farClip = 1000.0f;

	bool firstClick = true;

	void UpdateDirection();
};

#endif