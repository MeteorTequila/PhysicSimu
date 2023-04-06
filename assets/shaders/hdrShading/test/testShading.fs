#version 330 core
out vec4 FragColor;


in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
} fs_in;

uniform sampler2D lightBuffer;


void main()
{             
    vec3 texColor = texture(lightBuffer, fs_in.TexCoords).rgb;
    FragColor = vec4(texColor, 1.0);
    // FragColor = vec4(Position, 1.0);
    // FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}