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
#include "PhysicsManager.h"
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
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_CULL_FACE);

	// Shaders
	std::string vertFilepath = "cube.vert";
	std::string fragFilepath = "cube.frag";
	Shader cubeShader(vertFilepath, fragFilepath);

	vertFilepath = "singleColor.vert";
	fragFilepath = "singleColor.frag";
	Shader singleColorShader(vertFilepath, fragFilepath);

	// Camera
	Camera camera;

	// Physics Manager
	PhysicsManager physicsManager;

	// Input Manager
	InputManager inputManager;

	// Models
	Model scene("Models/scene/newNewScene.gltf");
	Mesh* house = scene.GetMesh(0);
	Mesh* roof = scene.GetMesh(1);
	Mesh* ground = scene.GetMesh(2);

	Model physicsObjectsScene("Models/scene/PhysicsObjects.gltf");
	Mesh* cube = physicsObjectsScene.GetMesh(0);
	
	// RigidBodies & Constraints
	// Static
	house->physBody.convex = false;
	house->GeneratePhysBody(0.0f);
	physicsManager.dynamicsWorld->addRigidBody(house->physBody.body);

	roof->physBody.convex = false;
	roof->GeneratePhysBody(0.0f);
	physicsManager.dynamicsWorld->addRigidBody(roof->physBody.body);

	ground->physBody.convex = false;
	ground->GeneratePhysBody(0.0f);
	physicsManager.dynamicsWorld->addRigidBody(ground->physBody.body);

	// Kinematic

	// Dynamic
	cube->GeneratePhysBody(1.0f);
	physicsManager.dynamicsWorld->addRigidBody(cube->physBody.body);
	cube->physBody.body->setRestitution(0.0);

	// lights
	DirLight dirLight{};
	dirLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	dirLight.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	dirLight.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	dirLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);

	// etc setup
	double lastTime = 0.0; // for delta time
	double deltaTime = 0.0;

	do
	{
		// Delta time
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		// Operations
		inputManager.ProcessInputs(window, camera, deltaTime);
		camera.UpdateDirection();

		// Physics Tick
		physicsManager.dynamicsWorld->stepSimulation(deltaTime);

		// Sync Meshes with Physics Bodies
		for (int i = 0; i < physicsObjectsScene.meshes.size(); i++) 
		{
			physicsObjectsScene.GetMesh(i)->SyncRigidBody();
		}

		// Rendering
		glClearColor(Color::blueSky.r, Color::blueSky.g, Color::blueSky.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Render wireframe

		// shader information
		SendLightInfo(dirLight, cubeShader);

		cubeShader.SetVec3("viewPos", camera.position.x, camera.position.y, camera.position.z);

		glm::mat4 proj = glm::perspective(camera.fov, aspectRatio(), camera.nearClip, camera.farClip);
		glm::mat4 view = glm::lookAt(camera.position, camera.position + camera.front, camera.up);
		cubeShader.SetMat4("proj", proj);
		cubeShader.SetMat4("view", view);

		// model matrix set in draw functions
		scene.Draw(cubeShader);
		physicsObjectsScene.Draw(cubeShader);

		// Swap buffers & poll events
		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) 
		{
			btTransform trans = btTransform(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(camera.position.x, camera.position.y, camera.position.z));
			cube->physBody.body->setWorldTransform(trans);
			cube->physBody.body->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
			cube->physBody.body->activate();
		}

	} while (!glfwWindowShouldClose(window));

	physicsManager.Cleanup();
	glfwTerminate();
	return 0;
}

void Framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
}