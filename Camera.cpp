#include "Camera.h"

#include <algorithm>
#include <functional>

Camera::Camera(Window& window) : _window(window)
{
    _position = glm::vec3(0.0f, 20.0f, 3.0f);
    _lookat = glm::vec3(0.0f, 0.0f, 1.0f);
    _up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    glfwSetWindowUserPointer(_window.GetGLFWwindow(), this);
    glfwSetCursorPosCallback(_window.GetGLFWwindow(), StaticMouseCallback);
    glfwSetMouseButtonCallback(_window.GetGLFWwindow(), StaticMouseButtonCallback);
}

void Camera::MoveCamera()
{
    ProcessInput();
    
    view = glm::lookAt(_position, _position + _lookat, _up);
}

void Camera::ProcessInput()
{
    float cameraSpeed = _cameraSpeed * _window.GetDeltaTime();
    if (_window.GetKeyDown(GLFW_KEY_W))
        _position += cameraSpeed * _lookat;
    if (_window.GetKeyDown(GLFW_KEY_S))
        _position -= cameraSpeed * _lookat;
    if (_window.GetKeyDown(GLFW_KEY_A))
        _position -= glm::normalize(glm::cross(_lookat, _up)) * cameraSpeed;
    if (_window.GetKeyDown(GLFW_KEY_D))
        _position += glm::normalize(glm::cross(_lookat, _up)) * cameraSpeed;
}

void Camera::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (!_mouseButtonHeld)
        return;

    if (_firstFrameHeld)
    {
        _lastMouseX = xpos;
        _lastMouseY = ypos;
        _firstFrameHeld = false;
    }
    
    float xOffset = xpos - _lastMouseX;
    float yOffset = _lastMouseY - ypos;

    _lastMouseX = xpos;
    _lastMouseY = ypos;

    const float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    _yaw += xOffset;
    _pitch += yOffset;

    _pitch = std::min(_pitch, 89.0f);
    _pitch = std::max(_pitch, -89.0f);

    glm::vec3 direction;
    direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    direction.y = sin(glm::radians(_pitch));
    direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _lookat = glm::normalize(direction);
}

void Camera::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        _mouseButtonHeld = true;
        glfwSetInputMode(_window.GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        _firstFrameHeld = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        _mouseButtonHeld = false;
        glfwSetInputMode(_window.GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Camera::StaticMouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    Camera* instance = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    instance->MouseCallback(window, xpos, ypos);
}

void Camera::StaticMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    Camera* instance = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    instance->MouseButtonCallback(window, button, action, mods);
}



