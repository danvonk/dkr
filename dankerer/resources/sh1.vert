#version 450

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec3 Normal;
out vec2 Texcoord;

layout(std140, binding = 0) uniform mvp {
    mat4 view;
    mat4 proj;
};

void main() {
    Normal = normal;
    Texcoord = texCoord;
    gl_Position = proj * view * vec4(position, 1.0);
}