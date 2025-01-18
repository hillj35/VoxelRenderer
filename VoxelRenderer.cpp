#include "MagicaVoxParser.h"
#include "VoxelMesh.h"

int main(int argc, char *argv[])
{
   VoxModel model;
   MagicaVoxParser::LoadModel("Assets/monu9.vox", model);
   auto mesh = VoxelMesh(model);
   return 0;
}
