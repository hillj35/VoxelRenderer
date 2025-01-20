#pragma once

#include "Window.h"

class GUI
{
public:
   GUI(Window &window);
   static void InitOpenGL(GLFWwindow *window);
   static void InitFrame();
   static void Render(Window &window);
   static void Shutdown();

private:
   Window &_window;

   static void StatsWindow(Window &window);

};
