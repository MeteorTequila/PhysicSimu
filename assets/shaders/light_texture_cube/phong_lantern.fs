#version 330 core

// 如果片段着色器只有一个输出变量(地址为0)，那么将会用这个变量来渲染
out vec4 FragColor;



void main()
{
    // 初始化所有片元的颜色
    FragColor = vec4(1.0); 
}