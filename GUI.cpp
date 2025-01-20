#include "GUI.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

GUI::GUI(Window &window) : _window(window) {}

void GUI::InitOpenGL(GLFWwindow *window)
{
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO &io = ImGui::GetIO();
   (void)io;
   ImGui::StyleColorsDark();
   ImGui_ImplGlfw_InitForOpenGL(window, true);
   ImGui_ImplOpenGL3_Init("#version 330");
}

void GUI::InitFrame()
{
   ImGui_ImplOpenGL3_NewFrame();
   ImGui_ImplGlfw_NewFrame();
   ImGui::NewFrame();
}

void GUI::Render(Window &window)
{
   StatsWindow(window);
   ImGui::Render();
}

void GUI::Shutdown()
{
   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();
}

void GUI::StatsWindow(Window &window)
{
   ImGui::Begin("Stats");
   ImGui::Text("FPS: %.2f (Frame Time: %.2f)", 1.0f / window.GetDeltaTime(), window.GetDeltaTime());
   ImGui::End();
}
