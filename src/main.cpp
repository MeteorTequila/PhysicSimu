

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

#include "Shader.hpp"

#include "GUIHelper.hpp"
// #include "TriangleDrawer.hpp"
// #include "CubeViewer.hpp"
// #include "Illumination.hpp"
// #include "ModelViewer.hpp"

// #include "SimuCore.hpp"
// #include "AdvanceOpenGL.hpp"
#include "AdvanceIllumination.hpp"
// #include "ModernOpenGL.hpp"

int main(int, char **)
{
  // 初始化GLFW对象
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // 创建一个GLFW窗体
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "PhysicSimu", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // 初始化glad，载入所有的glad函数指针
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // imgui相关
  // GUIHelper gh(window);

  // gh.customDraw();

  // 画三角形主程序
  // drawColorfulTriangle(window);
  // drawPractice(window);
  // drawTexture(window);

  // practice1SpinningPix(window);
  // practice2_3Dbox(window);
  // practice3_3Dbox_freecheck(window);
  // cubeFreeChecker(window);
  // lightPractice(window);
  // phongLightPractice(window);
  // phongLightBox(window);
  // phongLightCast(window);
  // viewModel(window);
  // modelViewer(window);
  // stencilBuffer(window);
  // blendingTransparent(window);
  // frameBufferPrac(window);
  // skyBoxPrac(window);
  // instanceRender(window);
  // blinnPhong(window);
  // shadowTexture(window);

  // shadowTextureBox(window);
  // normalTextureBox(window);
  parallaxMappingQuad(window);

  glfwTerminate();
  return 0;
}
