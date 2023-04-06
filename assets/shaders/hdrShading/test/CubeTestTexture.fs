#version 330 core
out vec4 FragColor;



in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D sjdakdja;

void main()
{

    vec3 texColor = texture(sjdakdja, fs_in.TexCoords).rgb;
    FragColor = vec4(texColor, 1.0);
    // FragColor = vec4(fs_in.FragPos, 1.0);
}


