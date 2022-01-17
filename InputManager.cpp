#include "InputManager.h"

void InputManager::ProcessInputs(GLFWwindow* window, Camera& camera, double deltaTime)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        float midx = (float)width / 2;
        float midy = (float)height / 2;

        if (firstClick)
        {
            glfwSetCursorPos(window, midx, midy);
            firstClick = false;
        }

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        float xoffset = xpos - midx;
        float yoffset = midy - ypos;
        xoffset *= camera.mouseSensitivity;
        yoffset *= camera.mouseSensitivity;

        camera.UpdateMouseLook(xoffset, yoffset);

        glfwSetCursorPos(window, midx, midy);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}