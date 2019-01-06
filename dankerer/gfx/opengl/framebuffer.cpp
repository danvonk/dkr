//
// Created by dan on 25/10/18.
//

#include "framebuffer.h"
#include "device.h"
#include "texture.h"

using namespace dk::gfx;

Framebuffer::Framebuffer(Device *d)
: m_device(d)
{
    glCreateFramebuffers(1, &m_fbo);
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_fbo);
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "NOTE: Bound framebuffer is not complete.\n";
    }
}

void Framebuffer::addColourAttachment(Texture *t) {
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_TEXTURE0 + m_colourAttachments.size(), GL_TEXTURE_2D, t->getID(), 0);
    m_colourAttachments.push_back(t);
}

void Framebuffer::addDepthAttachment(Texture * t) {
	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, t->getID(), 0);
}

void Framebuffer::addStencilAttachment(Texture * t)
{
}
