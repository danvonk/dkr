#version 450

layout(location = 3) in vec3 Colour;
layout(location = 4) in vec2 Texcoord;

layout(binding = 0) uniform sampler2D tex;

void main() {
    outColour = vec4(Colour, 1.0);
}