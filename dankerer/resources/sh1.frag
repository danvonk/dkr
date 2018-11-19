#version 450

in vec3 Normal;
in vec2 Texcoord;

out vec4 outColour;

uniform sampler2D tex;

void main() {
    outColour = texture(tex, Texcoord);
}