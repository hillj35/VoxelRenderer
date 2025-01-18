#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
   unsigned int id;

   Shader(const char *vertexPath, const char *fragmentPath)
   {
      // read shader files   
      std::string vertexCode;
      std::string fragmentCode;
      std::ifstream vShaderFile;
      std::ifstream fShaderFile;

      vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
      fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

      try {
         vShaderFile.open(vertexPath);
         fShaderFile.open(fragmentPath);
         std::stringstream vShaderStream, fShaderStream;

         vShaderStream << vShaderFile.rdbuf();
         fShaderStream << fShaderFile.rdbuf();

         vShaderFile.close();
         fShaderFile.close();

         vertexCode = vShaderStream.str();
         fragmentCode = fShaderStream.str();
      }
      catch (std::ifstream::failure e) {
         std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
      }

      const char *vShaderCode = vertexCode.c_str();
      const char *fShaderCode = fragmentCode.c_str();

      // compile shaders
      unsigned int vertex, fragment;
      vertex = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertex, 1, &vShaderCode, nullptr);
      glCompileShader(vertex);
      checkCompileErrors(vertex, "VERTEXSHADER");

      fragment = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragment, 1, &fShaderCode, nullptr);
      glCompileShader(fragment);
      checkCompileErrors(fragment, "FRAGMENTSHADER");

      id = glCreateProgram();
      glAttachShader(id, vertex);
      glAttachShader(id, fragment);
      glLinkProgram(id);
      checkCompileErrors(id, "PROGRAM");

      glDeleteShader(vertex);
      glDeleteShader(fragment);
   }
   void Use()
   {
      glUseProgram(id);
   }
   void setBool(const std::string &name, bool value) const
   {
      glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
   }
   void setInt(const std::string &name, int value) const
   {
      glUniform1i(glGetUniformLocation(id, name.c_str()), value);
   }
   void setFloat(const std::string &name, float value) const
   {
      glUniform1f(glGetUniformLocation(id, name.c_str()), value);
   }

private:
   void checkCompileErrors(unsigned int shader, std::string type)
   {
      int success;
      char infoLog[1024];
      if (type != "PROGRAM") {
         glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
         if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
         }
      } else {
         glGetProgramiv(shader, GL_LINK_STATUS, &success);
         if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
         }
      }
   }
};
