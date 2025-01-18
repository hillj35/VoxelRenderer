#pragma once
#include "MagicaVoxParser.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

class SubMesh
{
public:
   glm::vec3 position;
   std::vector<Vertex> vertices;
   std::vector<unsigned int> indices;
   // todo: add material

   SubMesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, glm::vec3 position) : position(position), vertices(vertices), indices(indices)
   {
      BuildBuffers();
   }

   void Draw()
   {
      glBindVertexArray(_vao);
      glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
   }

   void BuildBuffers()
   {
      glGenVertexArrays(1, &_vao);
      glBindVertexArray(_vao);

      unsigned int vbo;
      glGenBuffers(1, &vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

      unsigned int ebo;
      glGenBuffers(1, &ebo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
      glEnableVertexAttribArray(1);
   }

private:
   unsigned int _vao;
};

class VoxelMesh
{
public:
   VoxelMesh(VoxModel &model, Shader &shader);

   void RenderMesh();

private:
   Shader &_shader;
   VoxModel &_modelInfo;
   std::vector<SubMesh> _subMeshes;

   void BuildMesh();
};
