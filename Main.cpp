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

#include "VAO.h"
#include "EBO.h"
#include "Shader.h"
#include "Vertex.h"
#include "Texture.h"
#include "InputManager.h"

int windowWidth = 1280;
int windowHeight = 720;
float aspectRatio() { return (float)windowWidth / (float)windowHeight; }

void Framebuffer_size_callback(GLFWwindow* window, int width, int height);

float cubeVerts[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

std::vector<Vertex> cubeVertices;

int main()
{
	for (unsigned int i = 0; i < sizeof(cubeVerts) / sizeof(GLfloat); i)
	{
		Vertex vert;
		vert.position.x = cubeVerts[i++];
		vert.position.y = cubeVerts[i++];
		vert.position.z = cubeVerts[i++];
		vert.normals.x = cubeVerts[i++];
		vert.normals.y = cubeVerts[i++];
		vert.normals.z = cubeVerts[i++];
		vert.UVs.x = cubeVerts[i++];
		vert.UVs.y = cubeVerts[i++];
		cubeVertices.push_back(vert);
	}

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

	VAO cubevao;
	VBO cubevbo(cubeVertices);
	cubevao.Bind();
	cubevbo.Bind();
	cubevao.LinkAttrib(cubevbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0); // position
	cubevao.LinkAttrib(cubevbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	cubevao.LinkAttrib(cubevbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	cubevao.Unbind();
	cubevbo.Unbind();

	VAO lightSourcevao;
	VBO lightSourcevbo(cubeVertices);
	lightSourcevao.Bind();
	lightSourcevbo.Bind();
	lightSourcevao.LinkAttrib(lightSourcevbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	lightSourcevao.Unbind();
	lightSourcevbo.Unbind();

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
	Texture containerTex("container_diffuse.png", 0);
	Texture containerSpec("container_specular.png", 1);

	// Camera
	Camera camera;

	// Input Manager
	InputManager inputManager;

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

		glm::mat4 proj = glm::perspective(camera.fov, aspectRatio(), camera.nearClip, camera.farClip);
		glm::mat4 view = glm::lookAt(camera.position, camera.position + camera.front, camera.up);
		glm::mat4 model = glm::mat4(1.0f);

		// draw cube
		cubevao.Bind();
		cubevbo.Bind();
		cubeShader.Use();

		cubeShader.SetVec3("viewPos", camera.position.x, camera.position.y, camera.position.z);
		cubeShader.SetVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		cubeShader.SetVec3("material.specular", 0.5f, 0.5f, 0.5f);
		cubeShader.SetFloat("material.shininess", 32.0f);

		cubeShader.SetVec3("pointLights[0].position", pointLightPositions[0]);
		cubeShader.SetVec3("pointLights[0].ambient", 0.2f, 0.2f, 0.2f);
		cubeShader.SetVec3("pointLights[0].diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
		cubeShader.SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		cubeShader.SetFloat("pointLights[0].constant", 1.0f);
		cubeShader.SetFloat("pointLights[0].linear", 0.09f);
		cubeShader.SetFloat("pointLights[0].quadratic", 0.032f);

		cubeShader.SetVec3("pointLights[1].position", pointLightPositions[1]);
		cubeShader.SetVec3("pointLights[1].ambient", 0.2f, 0.2f, 0.2f);
		cubeShader.SetVec3("pointLights[1].diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
		cubeShader.SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		cubeShader.SetFloat("pointLights[1].constant", 1.0f);
		cubeShader.SetFloat("pointLights[1].linear", 0.09f);
		cubeShader.SetFloat("pointLights[1].quadratic", 0.032f);

		cubeShader.SetVec3("pointLights[2].position", pointLightPositions[2]);
		cubeShader.SetVec3("pointLights[2].ambient", 0.2f, 0.2f, 0.2f);
		cubeShader.SetVec3("pointLights[2].diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
		cubeShader.SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		cubeShader.SetFloat("pointLights[2].constant", 1.0f);
		cubeShader.SetFloat("pointLights[2].linear", 0.09f);
		cubeShader.SetFloat("pointLights[2].quadratic", 0.032f);

		cubeShader.SetVec3("pointLights[3].position", pointLightPositions[3]);
		cubeShader.SetVec3("pointLights[3].ambient", 0.2f, 0.2f, 0.2f);
		cubeShader.SetVec3("pointLights[3].diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
		cubeShader.SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		cubeShader.SetFloat("pointLights[3].constant", 1.0f);
		cubeShader.SetFloat("pointLights[3].linear", 0.09f);
		cubeShader.SetFloat("pointLights[3].quadratic", 0.032f);

		cubeShader.SetMat4("proj", proj);
		cubeShader.SetMat4("view", view);

		containerTex.Bind();
		containerSpec.Bind();

		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			cubeShader.SetMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// draw light source
		lightSourceShader.Use();
		cubevbo.Bind();

		lightSourceShader.SetMat4("view", view);
		lightSourceShader.SetMat4("proj", proj);

		for (int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));

			lightSourceShader.SetMat4("model", model);



			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

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