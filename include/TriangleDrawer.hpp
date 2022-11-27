#ifndef _PHYSICSIMU_TRIANGLEDRAWER_H_
#define _PHYSICSIMU_TRIANGLEDRAWER_H_

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "Shader.hpp"
#include <iostream>

// 动态处理窗体的IO事件
inline void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// 动态的调整窗体的大小
inline void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // set viewport, origin(0,0), height=800, width=600
    glViewport(0, 0, width, height);
}

// 窗体大小设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

inline void drawFirstTriangle()
{
}

inline void drawColorfulTriangle(GLFWwindow *window)
{
    // Shader shader("/Users/crystalized/cpp_project/Simulator/assets/shader/interpolateTriangle/vertice.vs", "/Users/crystalized/cpp_project/Simulator/assets/shader/interpolateTriangle/fragment.fs");
    Shader shader("../assets/shader/interpolateTriangle/vertice.vs", "../assets/shader/interpolateTriangle/fragment.fs");
    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top

    };

    // 定义顶点数组对象VAO和顶点缓冲对象VBO
    unsigned int VAO;
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // FIXME 啥意思？
    glBindVertexArray(VAO);

    // 将顶点数据绑定到VBO上
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置VAO中顶点数据（位置）的解析方式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // 设置VAO中顶点数据（颜色）的解析方式
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shader.use();

    // 循环渲染
    while (!glfwWindowShouldClose(window))
    {
        // 每次循环中检查窗体输入事件
        processInput(window);

        // TODO render things

        // 每次渲染前清空屏幕
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 调用最终的链接生成的那个着色器
        shader.use();

        // 通过VAO调用VBO绘制顶点
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // GLFW 交换缓冲 and 轮询IO事件 (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 终止glfw，释放资源
    glfwTerminate();
}

inline void drawPractice(GLFWwindow *window)
{
    Shader shader("../assets/shader/inverseTriangle/vertice.vs", "../assets/shader/inverseTriangle/fragment.fs");

    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
    };

    // 定义顶点数组对象VAO和顶点缓冲对象VBO
    unsigned int VAO;
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // FIXME 啥意思？
    glBindVertexArray(VAO);

    // 将顶点数据绑定到VBO上
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 因为在定义顶点数组vertices[]时，是coords、colors交替定义的，所以声明解析方式也要正确声明
    // 设置VAO中顶点数据（位置）的解析方式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // 设置VAO中顶点数据（颜色）的解析方式
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shader.use();
    // vShader中定义了一个uniform类型的变量(offset)，在此处给它赋值，
    // 注意！！必须在glUsePrograme()后才能向shader中间传值

    shader.setFloat("offset", 0.5);
    shader.setBool("inv", true);
    // 也可以用
    // int vertexOffsetLocation = glGetUniformLocation(shader.ID, "offset");
    // glUniform1f(vertexOffsetLocation, 0.5f);

    // 循环渲染
    while (!glfwWindowShouldClose(window))
    {
        // 每次循环中检查窗体输入事件
        processInput(window);

        // TODO render things

        // 每次渲染前清空屏幕
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 调用最终的链接生成的那个着色器
        shader.use();

        // 通过VAO调用VBO绘制顶点
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // GLFW 交换缓冲 and 轮询IO事件 (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 终止glfw，释放资源
    glfwTerminate();
}

#endif