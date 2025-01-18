#pragma once
#include "MagicaVoxParser.h"
#include <glm/glm.hpp>

struct Vertex
{
   glm::vec3 position;
   glm::vec3 color;
};

struct VoxelCube
{
   float x, y, z;
   glm::vec4 color;
};

struct SubMesh
{
   std::vector<Vertex> vertices;
   std::vector<unsigned int> indices;
   // todo: add material
};

class VoxelMesh
{
public:
   VoxelMesh(VoxModel &model);

private:
   VoxModel &_modelInfo;
   std::vector<SubMesh> _subMeshes;

   void BuildMesh();
};
