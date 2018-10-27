#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colour;
layout(location = 2) in vec2 texCoord;

layout(location = 3) out vec3 Colour;
layout(location = 4) out vec2 Texcoord;

layout(std140, binding = 0) uniform mvp {
    mat4 model;
    mat4 view;
    mat4 proj;
};

void main() {
    Colour = colour;
    Texcoord = texCoord;
    gl_Position = proj * view * vec4(position, 1.0);
}