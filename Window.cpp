#include "Window.h"

#include <iostream>
#include <ostream>

Window::Window(int width, int height)
{
   _height = height;
   _width = width;

   Init();
}

Window::~Window() {}

bool Window::ShouldClose() const
{
   return glfwWindowShouldClose(_window);
}

void Window::ClearColor(float r, float g, float b, float a)
{
   glClearColor(r, g, b, a);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::GetKeyDown(const int key)
{
   return glfwGetKey(_window, key);
}

void Window::ProcessInput()
{
   float currentFrame = glfwGetTime();
   _deltaTime = currentFrame - _lastFrame;
   _lastFrame = currentFrame;
   
   if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(_window, GLFW_TRUE);
   }
}

void Window::SwapBuffers() const
{
   glfwSwapBuffers(_window);
   glfwPollEvents();
}

void Window::Init()
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   _window = glfwCreateWindow(_width, _height, "Voxel Renderer", nullptr, nullptr);
   if (_window == nullptr) {
      std::cerr << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
   }

   glfwMakeContextCurrent(_window);

   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize GLAD" << std::endl;
   }

   glViewport(0, 0, _width, _height);
   glfwSetFramebufferSizeCallback(_window, FrameBufferSizeCallback);
   glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::FrameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
   glViewport(0, 0, width, height);
}
