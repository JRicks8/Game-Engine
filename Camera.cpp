#include "Camera.h"

void Camera::UpdateDirection()
{
	if (locked) return;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
}

void Camera::UpdateMouseLook(float xoffset, float yoffset)
{
	if (locked) return;
	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
}
/// <summary>
/// Camera receives WASD input and is free to roam.
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="window"></param>
void Camera::CameraOperations(double deltaTime, GLFWwindow* window)
{
	locked = false;
	float vel = deltaTime * speed;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += vel * front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= vel * front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= glm::normalize(glm::cross(front, up)) * vel;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += glm::normalize(glm::cross(front, up)) * vel;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		position += vel * up;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		position += vel * -up;
}
/// <summary>
/// Camera is positionally locked to specified position, however pitch and yaw can change.
/// </summary>
/// <param name="pos"></param>
/// <param name="offset"></param>
void Camera::CameraOperations(glm::vec3 pos, glm::vec3 offset)
{
	locked = false;
	position = pos + offset;
}
/// <summary>
/// Camera is locked to specified location.
/// </summary>
/// <param name="p"></param>
/// <param name="y"></param>
/// <param name="pos"></param>
/// <param name="offset"></param>
void Camera::CameraOperations(float p, float y, glm::vec3 pos, glm::vec3 offset)
{
	locked = true;
	position = pos + offset;
	pitch = p;
	yaw = y;
}