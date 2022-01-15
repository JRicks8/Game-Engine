#include "InputManager.h"

void InputManager::ProcessInputs(GLFWwindow* window, Camera& camera, double deltaTime)
{
    float vel = deltaTime * camera.speed;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.position += vel * camera.front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.position -= vel * camera.front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.position -= glm::normalize(glm::cross(camera.front, camera.up)) * vel;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.position += glm::normalize(glm::cross(camera.front, camera.up)) * vel;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.position += vel * camera.up;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.position += vel * -camera.up;

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

        camera.yaw += xoffset;
        camera.pitch += yoffset;

        if (camera.pitch > 89.0f)
            camera.pitch = 89.0f;
        if (camera.pitch < -89.0f)
            camera.pitch = -89.0f;

        glfwSetCursorPos(window, midx, midy);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}