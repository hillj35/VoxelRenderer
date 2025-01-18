#include "MagicaVoxParser.h"
#include "Shader.h"
#include "VoxelMesh.h"
#include "Window.h"

int main(int argc, char *argv[])
{
   auto window = Window(1920, 1080);
   auto shader = Shader("Shaders/vertex.glsl", "Shaders/fragment.glsl");

   VoxModel model;
   MagicaVoxParser::LoadModel("Assets/monu9.vox", model);
   auto mesh = VoxelMesh(model, shader);

   while (!window.ShouldClose()) {
      window.ProcessInput();
      window.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

      mesh.RenderMesh();

      window.SwapBuffers();
   }

   glfwTerminate();

   return 0;
}
