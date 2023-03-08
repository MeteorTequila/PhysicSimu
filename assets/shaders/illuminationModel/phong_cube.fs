#version 330 core


out vec4 FragColor;
in vec3 Normal;  
in vec3 FragPos;

// 定义材质
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

uniform Material material;

// 为环境光，漫反射，镜面反射定义不同的光照强度
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;



uniform vec3 viewPos; 


void main() {
    // 环境光
    vec3 ambient =light.ambient * material.ambient;
  	
    // 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // 镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
    
    // 总体
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
