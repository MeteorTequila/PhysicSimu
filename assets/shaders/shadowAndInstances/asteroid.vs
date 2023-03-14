#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstanceMatrix;//传入instance属性

out vec2 TexCoords;

// 接口块
out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    vec4 temp = transpose(inverse(aInstanceMatrix)) * vec4(aNormal, 1.0);// 法线也需要旋转
    vs_out.FragPos = aPos;
    vs_out.Normal = vec3(temp);
    vs_out.TexCoords = aTexCoords;

    gl_Position = projection * view * aInstanceMatrix * vec4(aPos, 1.0); 
}