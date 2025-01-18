#include "VoxelMesh.h"

VoxelMesh::VoxelMesh(VoxModel &model) : _modelInfo(model)
{
   BuildMesh();
}

void VoxelMesh::BuildMesh()
{
   // build local mesh
   for (auto voxel : _modelInfo.voxels) {
      // add a submesh for each voxel
      std::vector<Vertex> vertices;
      std::vector<unsigned int> indices;

      int color = _modelInfo.colors[voxel.colorIndex + 1];
      float a = (color & 0xFF) / 255.0f;
      float b = (color >> 8 & 0xFF) / 255.0f;
      float g = (color >> 16 & 0xFF) / 255.0f;
      float r = (color >> 24 & 0xFF) / 255.0f;
      glm::vec3 parsedColor = { r,g,b };

      vertices.push_back({ { 0,0,0 },parsedColor });
      vertices.push_back({ { 0,0,1 },parsedColor });
      vertices.push_back({ { 1,0,1 },parsedColor });
      vertices.push_back({ { 1,0,0 },parsedColor });
      vertices.push_back({ { 0,1,0 },parsedColor });
      vertices.push_back({ { 0,1,1 },parsedColor });
      vertices.push_back({ { 1,1,1 },parsedColor });
      vertices.push_back({ { 1,1,0 },parsedColor });

      indices.insert(indices.end(), { 0,2,1 });
      indices.insert(indices.end(), { 0,3,2 });
      indices.insert(indices.end(), { 4,6,5 });
      indices.insert(indices.end(), { 4,7,6 });
      indices.insert(indices.end(), { 0,7,4 });
      indices.insert(indices.end(), { 0,3,7 });
      indices.insert(indices.end(), { 3,6,7 });
      indices.insert(indices.end(), { 3,2,6 });
      indices.insert(indices.end(), { 2,5,6 });
      indices.insert(indices.end(), { 2,1,5 });
      indices.insert(indices.end(), { 1,4,5 });
      indices.insert(indices.end(), { 1,0,4 });

      _subMeshes.push_back({ vertices,indices });
   }
}
