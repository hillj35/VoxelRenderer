#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
   Window(int width, int height);
   ~Window();

   bool ShouldClose() const;
   void ClearColor(float r, float g, float b, float a);
   void ProcessInput() const;
   void SwapBuffers() const;

private:
   int _height, _width;
   GLFWwindow *_window;

   static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);

   void Init();
};
