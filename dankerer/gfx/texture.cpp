//
// Created by dan on 25/10/18.
//

#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "base/stb_image.h"

using namespace dk::gfx;

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

    stbi_uc* pixels = stbi_load(fileName.c_str(), &width, &height, &channels, STBI_rgb);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::loadImageWithType(std::string const &fileName, TextureType tt) {
    m_ttype = tt;
    loadImage(fileName);
}

void Texture::bind(u32 samplerUnit) {
    //glActiveTexture(GL_TEXTURE + samplerUnit);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_tex);
}
