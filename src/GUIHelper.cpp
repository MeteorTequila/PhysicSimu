
#include "GUIHelper.hpp"

GUIHelper::GUIHelper(GLFWwindow *w)
{
    this->window = w;

    /* Make the window's context current */
    // glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui_ImplGlfw_InitForOpenGL(w, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void GUIHelper::customDraw() const
{
    // 需要传入的参数

    // imgui 帧初始化
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // imgui 窗口主体
    ImGui::Begin("Setting pannel");
    // 当前帧数
    ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    // 复选框
    static bool bval_1 = false;
    static bool bval_2 = false;
    static bool bval_3 = false;
    ImGui::Checkbox("switcher", &bval_1);
    ImGui::SameLine();
    ImGui::Checkbox("switcher", &bval_2);
    ImGui::SameLine();
    ImGui::Checkbox("switcher", &bval_3);
    // 单选框
    static int e = 0;
    ImGui::RadioButton("radio a", &e, 0);
    ImGui::SameLine();
    ImGui::RadioButton("radio b", &e, 1);
    ImGui::SameLine();
    ImGui::RadioButton("radio c", &e, 2);
    // label标签
    ImGui::LabelText("label", "Value");
    // 文本输入
    static float foo = 1.0f;
    ImGui::InputFloat("red", &foo, 0.05f, 0, "%.3f");
    // combox
    const char *comboxItems[] = {"AAAA", "BBBB", "CCCC", "DDDD"};
    static int comboxItem = -1;
    ImGui::Combo("Combo", &comboxItem, comboxItems, IM_ARRAYSIZE(comboxItems));
    // listbox
    const char *listItems[] = {"Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon"};
    static int list_item_current = 1;
    ImGui::ListBox("listbox", &list_item_current, listItems, IM_ARRAYSIZE(listItems), 4);
    // 滑动条
    static float fval = 0.0f;
    ImGui::SliderFloat("float", &fval, 0.0f, 1.0f);
    // 按钮
    static int counter = 0;
    if (ImGui::Button("Button"))
        counter++;
    ImGui::SameLine(); // 使上下两行的控件在同一行
    ImGui::Text("counter = %d", counter);
    // 取色器
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGui::ColorEdit3("clear color", (float *)&clear_color);
    ImGui::End();

    // 渲染gui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // /* Swap front and back buffers */
    // glfwSwapBuffers(window);

    // /* Poll for and process events */
    // glfwPollEvents();
}

void GUIHelper::customDraw(bool &bval_1, bool &bval_2, bool &bval_3) const
{
    // 需要传入的参数

    // imgui 帧初始化
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // imgui 窗口主体
    ImGui::Begin("Setting pannel");
    // 当前帧数
    ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    // 复选框
    // static bool bval_1 = false;
    // static bool bval_2 = false;
    // static bool bval_3 = false;
    ImGui::Checkbox("direction light", &bval_1);
    ImGui::SameLine();
    ImGui::Checkbox("point light", &bval_2);
    ImGui::SameLine();
    ImGui::Checkbox("cast light", &bval_3);
    // 单选框
    static int e = 0;
    ImGui::RadioButton("radio a", &e, 0);
    ImGui::SameLine();
    ImGui::RadioButton("radio b", &e, 1);
    ImGui::SameLine();
    ImGui::RadioButton("radio c", &e, 2);
    // label标签
    ImGui::LabelText("label", "Value");
    // 文本输入
    static float foo = 1.0f;
    ImGui::InputFloat("red", &foo, 0.05f, 0, "%.3f");
    // combox
    const char *comboxItems[] = {"AAAA", "BBBB", "CCCC", "DDDD"};
    static int comboxItem = -1;
    ImGui::Combo("Combo", &comboxItem, comboxItems, IM_ARRAYSIZE(comboxItems));
    // listbox
    const char *listItems[] = {"Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon"};
    static int list_item_current = 1;
    ImGui::ListBox("listbox", &list_item_current, listItems, IM_ARRAYSIZE(listItems), 4);
    // 滑动条
    static float fval = 0.0f;
    ImGui::SliderFloat("float", &fval, 0.0f, 1.0f);
    // 按钮
    static int counter = 0;
    if (ImGui::Button("Button"))
        counter++;
    ImGui::SameLine(); // 使上下两行的控件在同一行
    ImGui::Text("counter = %d", counter);
    // 取色器
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGui::ColorEdit3("clear color", (float *)&clear_color);
    ImGui::End();

    // 渲染gui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // /* Swap front and back buffers */
    // glfwSwapBuffers(window);

    // /* Poll for and process events */
    // glfwPollEvents();
}

void GUIHelper::inputDialog(char &filePath, char &vsPath, char &fsPath) const
{
    // imgui 帧初始化
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static char str1[128] = "model path";
    static char str2[128] = "vertice shader path";
    static char str3[128] = "fragment shader path";

    // imgui 窗口主体
    ImGui::Begin("model load infomation");
    ImGui::InputText(" ", str1, IM_ARRAYSIZE(str1));
    ImGui::InputText(" ", str2, IM_ARRAYSIZE(str2));
    ImGui::InputText(" ", str3, IM_ARRAYSIZE(str3));
    if (ImGui::Button("confirm"))
    {
        // filePath = str1;

        strcpy(&filePath, str1);
        strcpy(&vsPath, str2);
        strcpy(&fsPath, str3);
        // strcpy(str1, "");
        // strcpy(str1, "");
        // strcpy(str1, "");
    }
    // 结束
    ImGui::End();

    // 渲染gui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIHelper::controlPanel(bool *light_switch, glm::vec3 &cPos, glm::vec3 *pLightPos) const
{
    // 需要传入的参数

    // imgui 帧初始化
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // imgui 窗口主体
    ImGui::Begin("Setting pannel");

    // 当前帧数
    ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Spacing();

    // 摄像机信息
    if (ImGui::CollapsingHeader("Camera Info"))
    {
        if (ImGui::TreeNode("Position"))
        {
            // 文本输入
            ImGui::InputFloat("x", &cPos.x, 0.05f, 0, "%.3f");
            ImGui::InputFloat("y", &cPos.y, 0.05f, 0, "%.3f");
            ImGui::InputFloat("z", &cPos.z, 0.05f, 0, "%.3f");
            ImGui::TreePop();   // 树节点结束
            ImGui::Separator(); // 分离器，就是除最后一个节点外，之前增加的节点都增加一个。
        }
    }

    // 灯光
    if (ImGui::CollapsingHeader("Lamp setting"))
    {
        if (ImGui::TreeNode("Parallel light"))
        {
            if (ImGui::TreeNode("light direction"))
            {
                ImGui::InputFloat("x", &cPos.x, 0.05f, 0, "%.3f");
                ImGui::InputFloat("y", &cPos.y, 0.05f, 0, "%.3f");
                ImGui::InputFloat("z", &cPos.z, 0.05f, 0, "%.3f");
                ImGui::TreePop();   // 树节点结束
                ImGui::Separator(); // 分离器，就是除最后一个节点外，之前增加的节点都增加一个。
            }

            if (ImGui::TreeNode("light color"))
            {
                static ImVec4 d_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
                ImGui::ColorEdit3(" ", (float *)&d_color);
                ImGui::TreePop();   // 树节点结束
                ImGui::Separator(); // 分离器，就是除最后一个节点外，之前增加的节点都增加一个。
            }

            // ImGui::ShowStyleEditor(); // 调用IMGUI函数显示设置

            ImGui::TreePop();   // 树节点结束
            ImGui::Separator(); // 分离器，就是除最后一个节点外，之前增加的节点都增加一个。
        }

        if (ImGui::TreeNode("Point light"))
        {
            if (ImGui::Button("Add"))
            {
            }
            ImGui::SameLine(); // 使上下两行的控件在同一行
            ImGui::Text("Add point light");

            if (ImGui::TreeNode("light 1 color & positon"))
            {
                // 颜色
                static ImVec4 p_color_1 = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
                ImGui::ColorEdit3(" ", (float *)pLightPos);
                // 坐标
                ImGui::InputFloat("x", &(pLightPos)->x, 0.05f, 0, "%.3f");
                ImGui::InputFloat("y", &(pLightPos)->y, 0.05f, 0, "%.3f");
                ImGui::InputFloat("z", &(pLightPos)->z, 0.05f, 0, "%.3f");
                ImGui::TreePop();   // 树节点结束
                ImGui::Separator(); // 分离器，就是除最后一个节点外，之前增加的节点都增加一个。
            }

            if (ImGui::TreeNode("light 2 color & positon"))
            {
                // 颜色
                static ImVec4 p_color_2 = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
                ImGui::ColorEdit3(" ", (float *)(pLightPos + 1));
                // 坐标
                ImGui::InputFloat("x", &(pLightPos + 1)->x, 0.05f, 0, "%.3f");
                ImGui::InputFloat("y", &(pLightPos + 1)->y, 0.05f, 0, "%.3f");
                ImGui::InputFloat("z", &(pLightPos + 1)->z, 0.05f, 0, "%.3f");
                ImGui::TreePop();   // 树节点结束
                ImGui::Separator(); // 分离器，就是除最后一个节点外，之前增加的节点都增加一个。
            }

            if (ImGui::TreeNode("light 3 color & positon"))
            {
                // 颜色
                static ImVec4 p_color_3 = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
                ImGui::ColorEdit3(" ", (float *)(pLightPos + 2));
                // 坐标
                ImGui::InputFloat("x", &(pLightPos + 2)->x, 0.05f, 0, "%.3f");
                ImGui::InputFloat("y", &(pLightPos + 2)->y, 0.05f, 0, "%.3f");
                ImGui::InputFloat("z", &(pLightPos + 2)->z, 0.05f, 0, "%.3f");
                ImGui::TreePop();   // 树节点结束
                ImGui::Separator(); // 分离器，就是除最后一个节点外，之前增加的节点都增加一个。
            }
            ImGui::TreePop();   // 树节点结束
            ImGui::Separator(); // 分离器，就是除最后一个节点外，之前增加的节点都增加一个。
        }

        if (ImGui::TreeNode("Spot light"))
        {
            if (ImGui::TreeNode("light color "))
            {
                static ImVec4 s_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
                ImGui::ColorEdit3("spot color", (float *)&s_color);

                ImGui::TreePop();   // 树节点结束
                ImGui::Separator(); // 分离器，就是除最后一个节点外，之前增加的节点都增加一个。
            }

            if (ImGui::TreeNode("spot params"))
            {
                static float cutoff = 0.1f, outerCutoff = 0.2f;
                ImGui::InputFloat("cutoff", &cutoff, 0.05f, 0, "%.3f");
                ImGui::InputFloat("outerCutoff", &outerCutoff, 0.05f, 0, "%.3f");
                ImGui::TreePop();   // 树节点结束
                ImGui::Separator(); // 分离器，就是除最后一个节点外，之前增加的节点都增加一个。
            }
            ImGui::TreePop();   // 树节点结束
            ImGui::Separator(); // 分离器，就是除最后一个节点外，之前增加的节点都增加一个。
        }
    }

    // 复选框
    ImGui::Checkbox("direction light", light_switch);
    ImGui::SameLine();
    ImGui::Checkbox("point light", light_switch + 1);
    ImGui::SameLine();
    ImGui::Checkbox("cast light", light_switch + 2);
    ImGui::End();

    // 渲染gui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIHelper::guiShutdown() const
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
