#version 450

layout(location = 3) in vec3 Colour;
layout(location = 4) in vec2 Texcoord;
layout(location = 5) out vec3 outColour;

layout(binding = 1) uniform sampler2D tex;

void main() {
    outColour = texture(tex, Texcoord);
}