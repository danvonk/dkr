#version 450

in vec3 Colour;
in vec2 Texcoord;

out vec4 outColour;

uniform sampler2D tex;

void main() {
    outColour = vec4(Colour, 1.0) * texture(tex, Texcoord);
}