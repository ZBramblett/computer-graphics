#version 330 core
layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Color;
out vec3 Color;
void main(void)
{
    gl_Position = vec4(in_Position, 1.0);
    Color = in_Color;
}