#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

uniform float heightScale;

//参考 https://www.cnblogs.com/jim-game-dev/p/5410529.html

// 根据当前纹理坐标，深度纹理，观察视角，计算出视差贴图
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
    // number of depth layers
    // 对深度值[0,1]分层（相当于采样），视线会和深度等分线产生交点
    const float minLayers = 1;
    const float maxLayers = 256;//32
    // 根据观察视角，动态的对深度纹理分层(提升性能，垂直于物体表面时，我们并不需要这么多的样本layer)
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
    // calculate the size of each layer
    // 计算每层的所表示的深度值
    float layerDepth = 1.0 / numLayers;
    // 初始化当前层的视差深度
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    // 每层（layer）对应在纹理坐标上的偏移量delta
    vec2 P = viewDir.xy / viewDir.z * heightScale; 
    vec2 deltaTexCoords = P / numLayers;
  
    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(depthMap, currentTexCoords).r;//根据纹理坐标获取视差贴图度值
      

    // 通常，视差贴图的深度会小于等于采样layer的深度（layer是从1～0的），
    // 当视差贴图深度大于采样layer的深度时，说明当前纹理坐标的视差深度介于当前采样层和上一采样层之间
    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        // 沿着p方向偏移当前层的纹理坐标
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        // 记录当前纹理位置的视差深度
        currentDepthMapValue = texture(depthMap, currentTexCoords).r;  
        // get depth of next layer
        // 遍历下一层
        currentLayerDepth += layerDepth;  
    }
    
    // 在前一个纹理坐标和当前纹理坐标之间做插值
    // get texture coordinates before collision (reverse operations)
    // 获取前一个纹理坐标
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    // 获取上一层和下一层的视差深度，准备做线性插值
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(depthMap, prevTexCoords).r - currentLayerDepth + layerDepth;
 
    // interpolation of texture coordinates
    // 
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}

void main()
{           
    // offset texture coordinates with Parallax Mapping
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec2 texCoords = fs_in.TexCoords;
    
    // 获取根据视差贴图偏移后的，人眼真正能够观察到的纹理贴图
    texCoords = ParallaxMapping(fs_in.TexCoords,  viewDir);  
    //如果超出纹理坐标范围了，直接return    
    if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
        discard;

    // 从法线贴图中获取当前坐标的法线
    vec3 normal = texture(normalMap, texCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);   
   
    // get diffuse color
    vec3 color = texture(diffuseMap, texCoords).rgb;
    // ambient
    vec3 ambient = 0.1 * color;
    // diffuse
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular    
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}