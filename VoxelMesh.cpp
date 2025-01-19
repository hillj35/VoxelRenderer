#include "VoxelMesh.h"

VoxelMesh::VoxelMesh(VoxModel &model, Shader &shader, Camera &camera) : _shader(shader), _modelInfo(model), _camera(camera)
{
   BuildMesh();
}

void VoxelMesh::RenderMesh()
{
   glEnable(GL_DEPTH_TEST);
   glCullFace(GL_BACK);
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

      vertices = {
          // Front face (z = 1.0f)
          { { 0.0f, 0.0f, 1.0f }, {  0.0f,  0.0f,  1.0f }, parsedColor }, // Bottom-left
          { { 1.0f, 0.0f, 1.0f }, {  0.0f,  0.0f,  1.0f }, parsedColor }, // Bottom-right
          { { 1.0f, 1.0f, 1.0f }, {  0.0f,  0.0f,  1.0f }, parsedColor }, // Top-right
          { { 0.0f, 1.0f, 1.0f }, {  0.0f,  0.0f,  1.0f }, parsedColor }, // Top-left

          // Back face (z = 0.0f)
          { { 0.0f, 0.0f, 0.0f }, {  0.0f,  0.0f, -1.0f }, parsedColor }, // Bottom-left
          { { 0.0f, 1.0f, 0.0f }, {  0.0f,  0.0f, -1.0f }, parsedColor }, // Top-left
          { { 1.0f, 1.0f, 0.0f }, {  0.0f,  0.0f, -1.0f }, parsedColor }, // Top-right
          { { 1.0f, 0.0f, 0.0f }, {  0.0f,  0.0f, -1.0f }, parsedColor }, // Bottom-right

          // Top face (y = 1.0f)
          { { 0.0f, 1.0f, 0.0f }, {  0.0f,  1.0f,  0.0f }, parsedColor }, // Bottom-left
          { { 0.0f, 1.0f, 1.0f }, {  0.0f,  1.0f,  0.0f }, parsedColor }, // Top-left
          { { 1.0f, 1.0f, 1.0f }, {  0.0f,  1.0f,  0.0f }, parsedColor }, // Top-right
          { { 1.0f, 1.0f, 0.0f }, {  0.0f,  1.0f,  0.0f }, parsedColor }, // Bottom-right

          // Bottom face (y = 0.0f)
          { { 0.0f, 0.0f, 0.0f }, {  0.0f, -1.0f,  0.0f }, parsedColor }, // Bottom-left
          { { 1.0f, 0.0f, 0.0f }, {  0.0f, -1.0f,  0.0f }, parsedColor }, // Bottom-right
          { { 1.0f, 0.0f, 1.0f }, {  0.0f, -1.0f,  0.0f }, parsedColor }, // Top-right
          { { 0.0f, 0.0f, 1.0f }, {  0.0f, -1.0f,  0.0f }, parsedColor }, // Top-left

          // Right face (x = 1.0f)
          { { 1.0f, 0.0f, 0.0f }, {  1.0f,  0.0f,  0.0f }, parsedColor }, // Bottom-left
          { { 1.0f, 1.0f, 0.0f }, {  1.0f,  0.0f,  0.0f }, parsedColor }, // Top-left
          { { 1.0f, 1.0f, 1.0f }, {  1.0f,  0.0f,  0.0f }, parsedColor }, // Top-right
          { { 1.0f, 0.0f, 1.0f }, {  1.0f,  0.0f,  0.0f }, parsedColor }, // Bottom-right

          // Left face (x = 0.0f)
          { { 0.0f, 0.0f, 0.0f }, { -1.0f,  0.0f,  0.0f }, parsedColor }, // Bottom-left
          { { 0.0f, 0.0f, 1.0f }, { -1.0f,  0.0f,  0.0f }, parsedColor }, // Bottom-right
          { { 0.0f, 1.0f, 1.0f }, { -1.0f,  0.0f,  0.0f }, parsedColor }, // Top-right
          { { 0.0f, 1.0f, 0.0f }, { -1.0f,  0.0f,  0.0f }, parsedColor }, // Top-left
      };

      indices = {
         // Front face
         0, 1, 2,  // First triangle
         0, 2, 3,  // Second triangle

         // Back face
         4, 5, 6,  // First triangle
         4, 6, 7,  // Second triangle

         // Top face
         8, 9, 10, // First triangle
         8, 10, 11, // Second triangle

         // Bottom face
         12, 13, 14, // First triangle
         12, 14, 15, // Second triangle

         // Right face
         16, 17, 18, // First triangle
         16, 18, 19, // Second triangle

         // Left face
         20, 21, 22, // First triangle
         20, 22, 23  // Second triangle
     };

      auto subMesh = SubMesh(vertices, indices, { voxel.x,voxel.z,voxel.y });

      _subMeshes.push_back(subMesh);
   }
}
