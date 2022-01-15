#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <iostream>
#include <string>

#include "Camera.h"

class InputManager
{
public:
	bool firstClick = true;

	void ProcessInputs(GLFWwindow* window, Camera& camera, double deltaTime);
};

#endif