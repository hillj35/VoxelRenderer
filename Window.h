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
   bool GetKeyDown(const int key);
   float GetDeltaTime() { return _deltaTime; }
   GLFWwindow* GetGLFWwindow() { return _window; }
   void ProcessInput();
   void SwapBuffers() const;

private:
   int _height, _width;
   float _deltaTime = 0.0f;
   float _lastFrame = 0.0f;
   GLFWwindow *_window;

   static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);

   void Init();
};
