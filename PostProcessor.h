#pragma once

#include "Shader.h"

class PostProcessor
{
public:
   PostProcessor();
   ~PostProcessor();

   void BindPostProcessingFramebuffer() const;
   void RenderPostProcessQuad();

private:
   unsigned int _fbo;
   unsigned int _rbo;
   unsigned int _vao;
   unsigned int _sceneColorTexture;

   std::unique_ptr<Shader> _lineShader;

   void Init();
};
