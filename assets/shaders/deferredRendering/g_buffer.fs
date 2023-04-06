#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{    
    // store the fragment position vector in the first gbuffer texture
    // 将position存储在第一个gbuffer纹理中
    gPosition = FragPos;
    // gPosition = vec3(1.0,1.0,1.0);
    // also store the per-fragment normals into the gbuffer
    // 还将每个片段的normal存储到gbuffer中
    gNormal = normalize(Normal);
    // gNormal = vec3(0.0, 0.0, 1.0);
    // and the diffuse per-fragment color
    // 漫反射纹理
    gAlbedoSpec.rgb = texture(texture_diffuse1, TexCoords).rgb;
    // gAlbedoSpec.rgb = vec3(0.5, 0.5, 0.5).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    // 高光纹理
    gAlbedoSpec.a = texture(texture_specular1, TexCoords).r;
    // gAlbedoSpec.a = 1.0;
}