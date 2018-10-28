#version 450

in vec3 position;
in vec3 colour;
in vec2 texCoord;

out vec3 Colour;
out vec2 Texcoord;

// layout(std140, binding = 0) uniform mvp {
//     mat4 view;
//     mat4 proj;
// };
uniform mat4 view;
uniform mat4 proj;

void main() {
    Colour = colour;
    Texcoord = texCoord;
    gl_Position = proj * view * vec4(position, 1.0);
}