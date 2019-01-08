#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

out vec3 Position;
out vec3 Normal;
out vec2 Texcoord;

layout(std140, binding = 3) uniform mvp {
    mat4 view;
    mat4 proj;
};

void main() {
    Normal = normal;
    Texcoord = texcoord;
    Position = (proj * view * vec4(position, 1.0)).xyz;
}
