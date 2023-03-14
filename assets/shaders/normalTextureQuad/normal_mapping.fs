#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 Normal;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool s1;

void worldSpaceShader1();
void worldSpaceShader2();
void tangentSpaceShader1();
void tangentSpaceShader2();

void main()
{
    
    if(!s1){
        worldSpaceShader2();
    }
    else{
        tangentSpaceShader1();
    }
    
}

void tangentSpaceShader1(){

    // 获取每个纹理坐标对应的法线，法线范围是[0, 1]
    vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;

    // 将法向量映射到[-1, 1]区间内
    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
   
    // 获取漫反射颜色
    vec3 color = texture(diffuseMap, fs_in.TexCoords).rgb;
    // 环境光
    vec3 ambient = 0.1 * color;
    // 漫反射
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);//使用切线空间计算
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // 镜面反射
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}

void tangentSpaceShader2(){

    // 获取每个纹理坐标对应的法线，法线范围是[0, 1]
    vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;

    // 将法向量映射到[-1, 1]区间内
    // normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
    normal = normalize(normal);
   
    // 获取漫反射颜色
    vec3 color = texture(diffuseMap, fs_in.TexCoords).rgb;
    // 环境光
    vec3 ambient = 0.1 * color;
    // 漫反射
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);//使用切线空间计算
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // 镜面反射
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
    // FragColor = vec4(normal, 1.0);
}

void worldSpaceShader1(){
    // 从法线贴图中获取法线
    vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;
    // 将法向量映射到[-1, 1]区间内
    normal = normalize(normal * 2.0 - 1.0);
    // 获取漫反射颜色
    vec3 color = texture(diffuseMap, fs_in.TexCoords).rgb;
    // 环境光
    vec3 ambient = 0.1 * color;
    // 漫反射
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);//使用切线空间计算
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // 镜面反射
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0);

}

void worldSpaceShader2(){

    // 获取漫反射颜色
    vec3 color = texture(diffuseMap, fs_in.TexCoords).rgb;
    // 环境光
    vec3 ambient = 0.1 * color;
    // 漫反射
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);//使用切线空间计算
    float diff = max(dot(lightDir, fs_in.Normal), 0.0);
    vec3 diffuse = diff * color;
    // 镜面反射
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, fs_in.Normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(fs_in.Normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
    // FragColor = vec4(fs_in.Normal, 1.0);

}