#include "Camera.h"
#include "GUI.h"
#include "imgui_impl_opengl3.h"
#include "Light.h"
#include "MagicaVoxParser.h"
#include "PostProcessor.h"
#include "Shader.h"
#include "VoxelMesh.h"
#include "Window.h"

int main(int argc, char *argv[])
{
   auto window = Window(1920, 1080);
   auto camera = Camera(window);
   auto shader = Shader("Shaders/vertex.glsl", "Shaders/fragment.glsl");

   VoxModel model;
   MagicaVoxParser::LoadModel("Assets/monu9.vox", model);
   auto mesh = VoxelMesh(model, shader, camera);

   auto light = DirectionalLight{
      glm::vec3(0.2f, -1.0f, 0.3f),
      glm::vec3(0.8f, 0.8f, 0.8f),
      glm::vec3(1.0f, 1.0f, 1.0f)
   };

   auto postProcessor = std::make_unique<PostProcessor>();

   shader.Use();
   shader.setVec3("light.direction", light.direction);
   shader.setVec3("light.ambient", light.ambient);
   shader.setVec3("light.diffuse", light.diffuse);

   GUI::InitOpenGL(window.GetGLFWwindow());

   while (!window.ShouldClose()) {
      window.ProcessInput();
      GUI::InitFrame();
      camera.MoveCamera();

      postProcessor->BindPostProcessingFramebuffer();
      mesh.RenderMesh();
      postProcessor->RenderPostProcessQuad();

      GUI::Render(window);
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      window.SwapBuffers();
   }

   GUI::Shutdown();

   glfwTerminate();

   return 0;
}
