#version 450 core

layout (location = 0) in vec4 col;
layout (location = 0) out vec4 color;

void main()
{
    color = col;
}
