#include "VoxelMesh.h"

VoxelMesh::VoxelMesh(VoxModel &model, Shader &shader, Camera &camera) : _shader(shader), _modelInfo(model), _camera(camera)
{
   BuildMesh();
}

void VoxelMesh::RenderMesh()
{
   glEnable(GL_DEPTH_TEST);
   _shader.Use();

   for (auto &subMesh : _subMeshes) {
      auto model = translate(glm::mat4(1.0f), subMesh.position);
      auto view = _camera.view;
      glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 1.0f, 1000.0f);
      int modelLoc = glGetUniformLocation(_shader.id, "model");
      int viewLoc = glGetUniformLocation(_shader.id, "view");
      int projectionLoc = glGetUniformLocation(_shader.id, "projection");

      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
      glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
      glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

      subMesh.Draw();
   }
}

void VoxelMesh::BuildMesh()
{
   // build local mesh
   for (auto &voxel : _modelInfo.voxels) {
      // add a submesh for each voxel
      std::vector<Vertex> vertices;
      std::vector<unsigned int> indices;

      int color = _modelInfo.colors[voxel.colorIndex - 1];
      float r = (color & 0xFF) / 255.0f;
      float g = (color >> 8 & 0xFF) / 255.0f;
      float b = (color >> 16 & 0xFF) / 255.0f;
      float a = (color >> 24 & 0xFF) / 255.0f;
      glm::vec3 parsedColor = { r,g,b };

      vertices.push_back({ { 0.0f,0.0f,0.0f },parsedColor });
      vertices.push_back({ { 0.0f,0.0f,1.0f },parsedColor });
      vertices.push_back({ { 1.0f,0.0f,1.0f },parsedColor });
      vertices.push_back({ { 1.0f,0.0f,0.0f },parsedColor });
      vertices.push_back({ { 0.0f,1.0f,0.0f },parsedColor });
      vertices.push_back({ { 0.0f,1.0f,1.0f },parsedColor });
      vertices.push_back({ { 1.0f,1.0f,1.0f },parsedColor });
      vertices.push_back({ { 1.0f,1.0f,0.0f },parsedColor });

      indices = {
         // Bottom face (CCW)
         0,1,2,0,2,3,
         // Top face (CCW corrected)
         4,5,6,4,6,7,
         // Front face (CCW)
         0,4,5,0,5,1,
         // Back face (CCW)
         3,2,6,3,6,7,
         // Left face (CCW corrected)
         0,7,3,0,4,7,
         // Right face (CCW)
         1,5,6,1,6,2
      };

      auto subMesh = SubMesh(vertices, indices, { voxel.x,voxel.z,voxel.y });

      _subMeshes.push_back(subMesh);
   }
}
