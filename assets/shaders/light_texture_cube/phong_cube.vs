#version 330 core

// layout location对应glVertexAttribPointer的解析方式
// 传入VAO中的顶点坐标和顶点法线坐标
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

// 输出顶点坐标和法线坐标
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

// 全局定义的mvp矩阵
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() {

  // 讲解析后的材质坐标传递给片段着色器
  TexCoords = aTexCoords;
  // 将aPos裁剪为
  FragPos = vec3(model * vec4(aPos, 1.0));

  // 将顶点法线的方向始终垂直于表面
  Normal = mat3(transpose(inverse(model))) * aNormal; 

  gl_Position = projection * view * vec4(FragPos, 1.0);
}
