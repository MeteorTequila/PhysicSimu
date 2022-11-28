#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform bool inv;
uniform float offset;
out vec3 ourColor;

void main()
{
    vec4 tempPos;
    if(inv == true)
    {
        tempPos = vec4(aPos.x - offset, -aPos.y, aPos.z, 1.0);
    }
    else{
        tempPos = vec4(aPos.x - offset, aPos.y, aPos.z, 1.0);
    }
    
    gl_Position=tempPos;
    ourColor = aColor;
}