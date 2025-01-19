#include "Camera.h"
#include "Light.h"
#include "MagicaVoxParser.h"
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

   auto light = DirectionalLight {
      glm::vec3(0.2f, -1.0f, 0.3f),
      glm::vec3(0.8f, 0.8f, 0.8f),
      glm::vec3(1.0f, 1.0f, 1.0f)
   };

   shader.Use();
   shader.setVec3("light.direction", light.direction);
   shader.setVec3("light.ambient", light.ambient);
   shader.setVec3("light.diffuse", light.diffuse);

   while (!window.ShouldClose()) {
      window.ProcessInput();
      camera.MoveCamera();
      window.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

      mesh.RenderMesh();

      window.SwapBuffers();
   }

   glfwTerminate();

   return 0;
}
