#version 330 core

layout(location=0) out vec4 fragmentColor;
in vec3 Color;
void main(void)
{
    fragmentColor = vec4(Color, 1);
}