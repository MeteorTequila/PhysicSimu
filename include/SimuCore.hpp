#ifndef _PHYSICSIMU_SIMUCORE_H_
#define _PHYSICSIMU_SIMUCORE_H_
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "Shader.hpp"
#include "glad/glad.h"
#include "GUIHelper.hpp"
#include "test.hpp"
#include "Model.hpp"

#include "Camera.hpp"
#include "Lights.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>


// 函数定义
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(char const *path);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void modelViewer(GLFWwindow *window)
{
    // GUI初始化
    GUIHelper gh(window);

    // 深度测试，解决自遮挡效果
    glEnable(GL_DEPTH_TEST);

    // 载入shader 和model 文件
    //  "../assets/model/nanosuit/nanosuit.obj";
    // "/Users/crystalized/model_3D/bunny.obj"
    // "/Users/crystalized/model_3D/Dragon_1.obj"

    // 光源模型
    static char l_fileStr[128] = "/Users/crystalized/model_3D/blenderSphere.obj";
    static char vLStr[128] = "../assets/shaders/modelViewerShader/lamp_sphere.vs";
    static char fLStr[128] = "../assets/shaders/modelViewerShader/lamp_sphere.fs";

    // 渲染模型
    static char fileStr[128] = "/Users/crystalized/model_3D/bunny.obj";
    static char vStr[128] = "../assets/shaders/modelViewerShader/model_viewer.vs";
    static char fStr[128] = "../assets/shaders/modelViewerShader/model_viewer.fs";

    Shader shader(vStr, fStr);
    Shader l_shader(vLStr, fLStr);
    Model ourModel(fileStr);
    Model l_Model(l_fileStr);

    // 平行光，点光源，聚光
    static bool lightSwitch[] = {false, false, false};

    while (!glfwWindowShouldClose(window))
    {

        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        // 监听输入事件
        processInput(window);

        // 清空屏幕
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        // glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 旋转光源

        float radius = 3;
        float camX = static_cast<float>(sin(glfwGetTime()) * radius);
        float camY = static_cast<float>(cos(glfwGetTime()) * radius / 2);
        float camZ = static_cast<float>(sin(glfwGetTime()) * cos(glfwGetTime()) * radius);
        glm::vec3 tempA(-camX, -camY, camZ);
        glm::vec3 tempB(camX, -camY, -camZ);
        glm::vec3 tempC(-camX, camY, -camZ);
        glm::vec3 pointLightPositions[] = {tempA, tempB, tempC};

        glm::vec3 colorHigh(1.0f, 1.0f, 1.0f);
        glm::vec3 colorMid = colorHigh * glm::vec3(0.8f);
        glm::vec3 colorLow = colorMid * glm::vec3(0.2f);

        shader.use();
        // 设置摄像机视角
        shader.setVec3("viewPos", camera.Position);

        // 设置光源开关
        shader.setBool("dirLightOpen", lightSwitch[0]);
        shader.setBool("pointLightOpen", lightSwitch[1]);
        shader.setBool("spotLightOpen", lightSwitch[2]);

        if (lightSwitch[0])
        {
            // 设置平行光参数
            shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
            shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
            shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
            shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        }
        if (lightSwitch[1])
        {
            // 注意： 若Fragment Shader中定义了光源上限为n，那么这里的i必须遍历n(不能小于n)
            for (unsigned int i = 0; i < 3; ++i)
            {
                std::string tempStr = "pointLights[" + std::to_string(i) + "].";
                shader.setVec3(tempStr + "position", pointLightPositions[i]);
                shader.setVec3(tempStr + "ambient", colorLow);
                shader.setVec3(tempStr + "diffuse", colorMid);
                shader.setVec3(tempStr + "specular", colorHigh);
                shader.setFloat(tempStr + "constant", 1.0f);
                shader.setFloat(tempStr + "linear", 0.09f);
                shader.setFloat(tempStr + "quadratic", 0.032f);
            }
        }

        if (lightSwitch[2])
        {
            shader.setVec3("spotLight.position", camera.Position);
            shader.setVec3("spotLight.direction", camera.Front);
            shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
            shader.setFloat("spotLight.constant", 1.0f);
            shader.setFloat("spotLight.linear", 0.09f);
            shader.setFloat("spotLight.quadratic", 0.032f);
            shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
        }

        // 视口转换
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // 渲染模型
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // 让模型处于中间位置
        // 模型坐标的缩放尺度
        // model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f)); // 龙用的缩放尺度，缩小为原来的0.05倍
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f)); // stanford bunny用的缩放尺度，放大为原来的4倍
        // model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f)); // nanosuit
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setMat4("model", model);
        ourModel.Draw(shader);

        // 渲染光球
        l_shader.use();
        l_shader.setMat4("projection", projection);
        l_shader.setMat4("view", view);

        for (unsigned int i = 0; i < 3; ++i)
        {
            glm::mat4 light_model = glm::mat4(1.0f);
            light_model = glm::translate(light_model, pointLightPositions[i]);
            light_model = glm::scale(light_model, glm::vec3(0.2f, 0.2f, 0.2f));
            l_shader.setMat4("model", light_model);
            l_Model.Draw(l_shader);
        }
        // 绘制GUI

        gh.controlPanel(lightSwitch, camera.Position, pointLightPositions);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // TODO GUI关闭
    gh.guiShutdown();
}

// 封装的载入纹理方法
// ---------------------------------------------------------------------------------------------
unsigned int loadTexture(char const *path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // 纹理重复方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // 纹理过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // 将纹理图片载入到gl中就可以释放掉stb_image中的内存了
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
    }
    if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPosCallback(window, NULL);
        glfwSetScrollCallback(window, NULL);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

#endif