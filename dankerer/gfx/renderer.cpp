#include "renderer.h"

using namespace dk::gfx;

Renderer::Renderer(dk::gfx::Renderer::RendererType t, Device* d)
    : m_rendererType(t)
    , m_device(d)
    , m_cmdBuf(d)
{
}

RenderPass* Renderer::addRenderPass(std::unique_ptr<RenderPass> p) {
    m_renderPasses.push_back(std::move(p));
}
