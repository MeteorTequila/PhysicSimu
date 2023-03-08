#ifndef _PHYSICSIMU_LIGHTS_H_
#define _PHYSICSIMU_LIGHTS_H_
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Shader.hpp"

enum LightType
{
    PARALLE_LIGHT,
    POINT_LIGHT,
    SPOT_LIGHT
};

struct ParalleLight
{
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct PointLight
{
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    // 光线衰减参数
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

class Lights
{
private:
    // 场景内光源的最大值
    int paralleMax = 3;
    int pointMax = 3;
    int spotMax = 3;

    // 各项光源当前计数
    unsigned int paralleCount = 0;
    unsigned int pointCount = 0;
    unsigned int spotCount = 0;

public:
    // 保存各项光源
    vector<ParalleLight> paralleLights;
    vector<PointLight> pointLights;
    vector<SpotLight> spotLights;

    // 构造函数
    Lights(const int &_paralleMax, const int &_pointMax, const int &_spotCount) : paralleMax(_paralleMax), pointMax(_pointMax), spotCount(_spotCount){};

    // = = = = = = = = = = = = = = = = = =
    // = = = = = = = 添加光源 = = = = = = =
    // = = = = = = = = = = = = = = = = = =
    void addLight(ParalleLight &L, Shader &shader)
    {
        std::string tempStr = "dirLight[" + std::to_string(paralleCount) + "].";
        if (paralleCount < paralleMax)
        {
            shader.use();
            shader.setVec3(tempStr + "direction", L.direction);
            shader.setVec3(tempStr + "ambient", L.ambient);
            shader.setVec3(tempStr + "diffuse", L.diffuse);
            shader.setVec3(tempStr + "specular", L.specular);
            paralleLights.push_back(L);
            paralleCount++;
        }
    }

    void addLight(PointLight &L, Shader &shader)
    {
        std::string tempStr = "pointLight[" + std::to_string(paralleCount) + "].";
        if (pointCount < pointMax)
        {
            shader.use();
            shader.setVec3(tempStr + "position", L.position);
            shader.setVec3(tempStr + "ambient", L.ambient);
            shader.setVec3(tempStr + "diffuse", L.diffuse);
            shader.setVec3(tempStr + "specular", L.specular);
            shader.setFloat(tempStr + "constant", L.constant);
            shader.setFloat(tempStr + "linear", L.linear);
            shader.setFloat(tempStr + "quadratic", L.quadratic);
            pointLights.push_back(L);
            pointCount++;
        }
    }

    void addLight(SpotLight &L, Shader &shader)
    {
        std::string tempStr = "spotLight[" + std::to_string(paralleCount) + "].";
        if (spotCount < spotMax)
        {
            shader.use();
            shader.setVec3(tempStr + "position", L.position);
            shader.setVec3(tempStr + "direction", L.direction);
            shader.setVec3(tempStr + "ambient", L.ambient);
            shader.setVec3(tempStr + "diffuse", L.diffuse);
            shader.setVec3(tempStr + "specular", L.specular);

            shader.setFloat(tempStr + "cutOff", L.cutOff);
            shader.setFloat(tempStr + "outerCutOff", L.outerCutOff);

            shader.setFloat(tempStr + "constant", L.constant);
            shader.setFloat(tempStr + "linear", L.linear);
            shader.setFloat(tempStr + "quadratic", L.quadratic);
            spotLights.push_back(L);
            spotCount++;
        }
        spotLights.push_back(L);
    }

    // = = = = = = = = = = = = = = = = = =
    // = = = = = = = 删除光源 = = = = = = =
    // = = = = = = = = = = = = = = = = = =

    void deletParalleLight()
    {
        paralleLights.pop_back();
    }

    void deletPointLight()
    {
        pointLights.pop_back();
    }

    void deletSpotLight()
    {
        spotLights.pop_back();
    }

    // = = = = = = = = = = = = = = = = = =
    // = = = = = = = 旋转光源 = = = = = = =
    // = = = = = = = = = = = = = = = = = =

    void rotatePointLights(Shader &shader)
    {

        // float radius = 3;
        // float rX = static_cast<float>(sin(glfwGetTime()) * radius);
        // float rY = static_cast<float>(cos(glfwGetTime()) * radius / 2);
        // float rZ = static_cast<float>(sin(glfwGetTime()) * cos(glfwGetTime()) * radius);
        // glm::vec3 tempA(-rX, -rY, rZ);
        // glm::vec3 tempB(rX, -rY, -rZ);
        // glm::vec3 tempC(-rX, rY, -rZ);

        glm::vec3 tempArry[] = {glm::vec3(0.0f, 1.0f, 0.0f),
                                glm::vec3(1.0f, 0.0f, 0.0f),
                                glm::vec3(0.0f, 0.0f, 1.0f)};

        for (unsigned int i = 0; i < pointLights.size(); ++i)
        {
            glm::mat4 model = glm::mat4(1.0f);
            // pointLights[i].position = glm::rotate((pointLights[i].position, 1), (float)glfwGetTime() * glm::radians(10.0f), tempArry[i]);

            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // 模型坐标的缩放尺度

            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(10.0f), tempArry[i]);
            shader.setMat4("model", model);
            // l_Model.Draw(shader);
        }
    }
};

#endif