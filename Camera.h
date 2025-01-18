#pragma once
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"

class Camera
{
public:
   glm::mat4 view;
   
   Camera(Window &window);
   void MoveCamera();
   
private:
   const float _cameraSpeed = 10.0f;

   Window &_window;
   
   glm::vec3 _position;
   glm::vec3 _right;
   glm::vec3 _up;
   glm::vec3 _lookat;

   // mouse variables
   float _lastMouseX = 960.0f, _lastMouseY = 540.0f;
   float _yaw = 90.0f, _pitch = 0.0f;

   void ProcessInput();
   void MouseCallback(GLFWwindow* window, double xpos, double ypos);

   static void StaticMouseCallback(GLFWwindow* window, double xpos, double ypos);
};
