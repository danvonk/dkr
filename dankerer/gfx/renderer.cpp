#include "renderer.h"

using namespace dk::gfx;

Renderer::Renderer(dk::gfx::Renderer::RendererType t, Device* d)
    : m_rendererType(t)
    , m_device(d)
    , m_cmdBuf(d)
{
}

void Renderer::addRenderPass(RenderPass* p) {
	m_renderPasses.emplace_back(std::unique_ptr<RenderPass>(p));
}
