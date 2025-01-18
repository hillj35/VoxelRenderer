#include "MagicaVoxParser.h"
#include "VoxelMesh.h"
#include "Window.h"

int main(int argc, char *argv[])
{
   auto window = Window(1920, 1080);

   VoxModel model;
   MagicaVoxParser::LoadModel("Assets/monu9.vox", model);
   auto mesh = VoxelMesh(model);

   while (!window.ShouldClose()) {
      window.ProcessInput();
      window.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      window.SwapBuffers();
   }

   glfwTerminate();

   return 0;
}
