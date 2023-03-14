#ifndef _PHYSICSIMU_SHADER_H_
#define _PHYSICSIMU_SHADER_H_

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader
{
public:
  // 程序ID
  unsigned int ID;

  // 构造器读取并构建着色器
  Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath =nullptr);
  // 使用/激活程序
  void use();
  // uniform工具函数
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setVec2(const std::string &name, const glm::vec2 &vec) const;
  void setVec2(const std::string &name, float x, float y) const;
  void setVec3(const std::string &name, const glm::vec3 &vec) const;
  void setVec3(const std::string &name, float x, float y, float z) const;
  void setVec4(const std::string &name, const glm::vec4 &vec) const;
  void setVec4(const std::string &name, float x, float y, float z, float w) const;
  void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
  void checkCompileErrors(unsigned int shader, std::string type);
};

#endif