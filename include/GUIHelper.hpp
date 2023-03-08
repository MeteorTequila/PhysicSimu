#ifndef _PHYSICSIMU_GUIHELPER_H_
#define _PHYSICSIMU_GUIHELPER_H_

// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GUIHelper
{
public:
    GLFWwindow *window;

    GUIHelper(GLFWwindow *w);

    void customDraw() const;
    void customDraw(bool &bval_1, bool &bval_2, bool &bval_3) const;
    void guiShutdown() const;
    void inputDialog(char &filePath, char &vsPath, char &fsPath) const;
    void controlPanel(bool *light_switch, glm::vec3 &cPos,glm::vec3 *pLightPos) const;
};

#endif