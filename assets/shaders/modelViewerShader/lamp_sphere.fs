#version 330 core
out vec4 FragColor;

// 定义材质
struct Material {
  sampler2D diffuse;
  sampler2D specular;
  sampler2D emission;
  float shininess;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D texture_diffuse2;
uniform vec3 lampColor;

void main()
{
    // 初始化所有片元的颜色
    FragColor = vec4(1.0); 

    // 使用纹理坐标初始化所有片元的颜色
    // FragColor = texture(texture_diffuse2, TexCoords);
}