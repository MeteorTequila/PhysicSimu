#version 330 core
// layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec2 aTexCoords;

// https://learnopengl.com/code_viewer_gh.php?code=src/5.advanced_lighting/8.1.deferred_shading/deferred_shading.cpp
// 上面是LearnOpenGL的链接，但是它的renderQuad()方法与Geometry.hpp的renderQuad()方法不一致
// 因为Geometry.hpp的Quad的vertex读取方式与LearnOpenGL的不一样，所以要使用下述layout
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;


out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}