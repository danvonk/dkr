#version 450

in vec3 Position;
in vec3 Normal;
in vec2 Texcoord;

out vec3 gPosition;
out vec3 gNormal;
out vec3 gAlbedoSpecular;

uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular;

void main () {
    gPosition = Position;
    gNormal = normalize(Normal);
    gAlbedoSpecular.rgb = texture(textureDiffuse, Texcoord).rgb;
    gAlbedoSpecular.a = texture(textureSpecular, Texcoord).r;
}