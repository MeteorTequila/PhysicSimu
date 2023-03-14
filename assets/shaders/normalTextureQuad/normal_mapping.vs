#version 330 core
layout (location = 0) in vec3 aPos;//载入顶点空间坐标
layout (location = 1) in vec3 aNormal;//这个是从VAO中载入的顶点法线
layout (location = 2) in vec2 aTexCoords;//载入顶点纹理坐标
layout (location = 3) in vec3 aTangent;//载入切线空间中的基向量T（通过assimp中计算得来）
layout (location = 4) in vec3 aBitangent;//载入切线空间中的基向量B

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 Normal;
    vec3 TangentLightPos;//光源位置转换为切线空间
    vec3 TangentViewPos;//摄像机位置转换为切线空间
    vec3 TangentFragPos;//片元位置转换为切线空间
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPos;
uniform vec3 viewPos;

void TBNtransform();

void main()
{
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));   
    vs_out.TexCoords = aTexCoords;
    vs_out.Normal=transpose(inverse(mat3(model)))*aNormal;
    
    //切线空间转换
    TBNtransform();
        
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

void TBNtransform(){

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    //获取切线空间变换矩阵
    mat3 TBN = transpose(mat3(T, B, N));    


    //将光源位置，视角位置，片元位置映射到切线空间
    vs_out.TangentLightPos = TBN * lightPos;
    vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;
}