#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;// 注意：用的是sampleCube来接受skybox纹理采样


// 载入skybox的纹理
void main()
{    
    FragColor = texture(skybox, TexCoords);
}