#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

layout (location = 0) out vec4 col;

void main()
{
    gl_Position = vec4(position, 1.0);

    col = vec4(normal.x, normal.y, 1.0, 1.0);
}
