#include "PostProcessor.h"

#include <iostream>
#include <ostream>
#include <glad/glad.h>

PostProcessor::PostProcessor()
{
   Init();
}

PostProcessor::~PostProcessor()
{
   glDeleteFramebuffers(1, &_fbo);
}

void PostProcessor::BindPostProcessingFramebuffer() const
{
   glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
   glClearColor(0.6509803921568628f, 0.5372549019607843f, 0.8823529411764706f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
}

void PostProcessor::RenderPostProcessQuad()
{
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);

   _lineShader->Use();
   glBindVertexArray(_vao);
   glDisable(GL_DEPTH_TEST);
   glBindTexture(GL_TEXTURE_2D, _sceneColorTexture);
   glDrawArrays(GL_TRIANGLES, 0, 6);
}


void PostProcessor::Init()
{
   // build frame and render buffer objects
   glGenFramebuffers(1, &_fbo);
   glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
   glGenTextures(1, &_sceneColorTexture);

   glBindTexture(GL_TEXTURE_2D, _sceneColorTexture);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glBindTexture(GL_TEXTURE_2D, 0);

   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _sceneColorTexture, 0);

   glGenRenderbuffers(1, &_rbo);
   glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
   glBindRenderbuffer(GL_RENDERBUFFER, 0);

   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);

   if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
   }
   glBindFramebuffer(GL_FRAMEBUFFER, 0);

   // build vertex array object
   float quadVertices[] = {
      // positions   // texCoords
      -1.0f,1.0f,0.0f,1.0f,
      -1.0f,-1.0f,0.0f,0.0f,
      1.0f,-1.0f,1.0f,0.0f,

      -1.0f,1.0f,0.0f,1.0f,
      1.0f,-1.0f,1.0f,0.0f,
      1.0f,1.0f,1.0f,1.0f
   };

   glGenVertexArrays(1, &_vao);
   glBindVertexArray(_vao);

   unsigned int vbo;
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
   glEnableVertexAttribArray(1);

   // create post-processing shader
   _lineShader = std::make_unique<Shader>("Shaders/outline_vert.glsl", "Shaders/outline_frag.glsl");
}
