#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

layout (set = 0, binding = 0) uniform CameraUBO {
    mat4 projection;
    mat4 view;
} camera;

layout (set = 1, binding = 0) uniform ModelUBO {
    mat4 model;
} model;

void main()
{
    gl_Position = camera.projection * camera.view *
        model.model * vec4(position, 1.0);
    //gl_Position = model.model * vec4(position, 1.0);
}
