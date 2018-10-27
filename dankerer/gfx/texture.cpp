//
// Created by dan on 25/10/18.
//

#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "dankerer/base/stb_image.h"
#include "dankerer/gfx/texture.h"


using dk::gfx::Texture;

Texture::Texture() {
    glGenTextures(1, &m_tex);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_tex);
}

void Texture::loadImage(std::string const &fileName) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_tex);

    int width = 0;
    int height = 0;
    int channels = 0;

    stbi_uc* pixels = stbi_load(fileName.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);


}
