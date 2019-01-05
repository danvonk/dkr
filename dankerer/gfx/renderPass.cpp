//
// Created by dan on 07/12/18.
//

#include "renderPass.h"
#include "opengl/device.h"

using namespace dk::gfx;

RenderPass::RenderPass(Device *d)
: m_device(d)
{
    m_frame = d->createFramebuffer();
}

RenderPass::~RenderPass() {

}

void RenderPass::setName(std::string const &name) {

}

std::string RenderPass::getName() const {
    return m_nameOfPass;
}

void RenderPass::addOutput(std::string const &name) {
    auto txHandle = m_device->createTexture();
    auto& fbo = m_device->accessFramebuffer(m_frame);

    fbo.attachTexture()
}

void RenderPass::setClearColour(glm::vec4 colour) {
    m_clearColour = colour;
}
