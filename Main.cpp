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

#include "InputManager.h"
#include "Model.h"
#include "Light.h"
#include "Color.h"

int windowWidth = 1280;
int windowHeight = 720;
float aspectRatio() { return (float)windowWidth / (float)windowHeight; }

void Framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	// GLFW & window init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Bengine2", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// GLAD init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD." << std::endl;
		return -1;
	}

	// GL init
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);
	glfwSetFramebufferSizeCallback(window, Framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Shaders
	std::string vertFilepath = "cube.vert";
	std::string fragFilepath = "cube.frag";
	Shader cubeShader(vertFilepath, fragFilepath);

	vertFilepath = "lightSource.vert";
	fragFilepath = "lightSource.frag";
	Shader lightSourceShader(vertFilepath, fragFilepath);

	// Textures
	cubeShader.Use();
	cubeShader.SetInt("material.diffuse", 0);
	cubeShader.SetInt("material.specular", 1);

	// Camera
	Camera camera;

	// Input Manager
	InputManager inputManager;

	// Models
	Model scene("Models/scene/scene.gltf");

	// lights
	DirLight dirLight;
	dirLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	dirLight.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	dirLight.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	dirLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);

	// etc setup
	double lastTime = 0.0; // for delta time
	double deltaTime = 0.0;

	
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	do
	{
		// Delta time
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		// Operations
		inputManager.ProcessInputs(window, camera, deltaTime);
		camera.UpdateDirection();

		// Rendering
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Render wireframe

		// lights
		cubeShader.Use();

		SendLightInfo(dirLight, cubeShader);

		cubeShader.SetVec3("viewPos", camera.position.x, camera.position.y, camera.position.z);

		// default material values (When maps are not applied)
		cubeShader.SetVec3("material.diffuse", Color::purpleLight);
		cubeShader.SetVec3("material.specular", Color::gray);
		cubeShader.SetFloat("material.shininess", 32.0f);

		glm::mat4 proj = glm::perspective(camera.fov, aspectRatio(), camera.nearClip, camera.farClip);
		glm::mat4 view = glm::lookAt(camera.position, camera.position + camera.front, camera.up);
		cubeShader.SetMat4("proj", proj);
		cubeShader.SetMat4("view", view);

		// model matrix set in draw functions
		scene.Draw(cubeShader);

		// Swap buffers & poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (!glfwWindowShouldClose(window));

	glfwTerminate();
	return 0;
}

void Framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
}