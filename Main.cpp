// create object
//unsigned int objectId = 0;
//glGenObject(1, &objectId);
// 
// bind/assign object to context
//glBindObject(GL_WINDOW_TARGET, objectId);
// 
// set options of object currently bound to GL_WINDOW_TARGET
//glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_WIDTH, 800);
//glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_HEIGHT, 600);
// 
// set context target back to default
//glBindObject(GL_WINDOW_TARGET, 0);

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return 0;
}