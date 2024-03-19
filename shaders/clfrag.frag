#version 450 core

layout (location = 0) out vec4 color;

layout (set = 2, binding = 0) uniform ColorUBO {
    vec4 color;
} colors;

void main()
{
    color = colors.color;
}
