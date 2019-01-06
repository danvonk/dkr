//
// Created by dan on 07/12/18.
//

#include "renderPass.h"
#include "opengl/framebuffer.h"
#include "opengl/device.h"

using namespace dk::gfx;

RenderPass::RenderPass(Device *d)
: m_device(d)
{
    m_frame = d->createFramebuffer();

	auto& fbo = d->accessFramebuffer(m_frame);
	fbo.setScreenWidth(d->getWindowWidth());
	fbo.setScreenHeight(d->getWindowHeight());
}

RenderPass::~RenderPass() {
	m_device->deleteFramebuffer(m_frame);
}

void RenderPass::setName(std::string const &name) {
	m_nameOfPass = name;
}

std::string RenderPass::getName() const {
    return m_nameOfPass;
}

void RenderPass::addInput(std::string const & name)
{
}

void RenderPass::addOutput(std::string const &name) {
    auto txHandle = m_device->createTexture();
    auto& fbo = m_device->accessFramebuffer(m_frame);
	
	auto tex = m_device->createTexture();
	fbo.addColourAttachment(&(m_device->accessTexture(tex)));
}

void RenderPass::setClearColour(glm::vec4 colour) {
    m_clearColour = colour;
}

void RenderPass::bind() {
	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
	glDrawBuffers(3, attachments);
}
