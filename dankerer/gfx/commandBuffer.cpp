//
// Created by dan on 21/12/18.
//

#include "commandBuffer.h"
#include "opengl/elementBuffer.h"
#include "renderPass.h"

using namespace dk::gfx;

CommandBuffer::CommandBuffer(Device *d)
    : m_device(d)
{

}

void CommandBuffer::draw(u32 startVertex, u32 count) {
    glDrawArrays(GL_TRIANGLES, startVertex, count);
}

void CommandBuffer::drawElements(u32 vertexCount, u32 indexOffset) {
    glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, (void*)indexOffset);
}

void CommandBuffer::setShaderProgram(ShaderProgram *p) {
    m_currentShp = p;
    p->link(m_device);
}

void CommandBuffer::setVao(GLuint vao) {

}

void CommandBuffer::setElementBuffer(ElementBuffer *e) {
    e->bind();
}

void dk::gfx::CommandBuffer::push(u64 sortKey, RendererFunc rendFunc, StaticMeshInfo smi) {
	RenderQueueItem i{};
	i.m_rendererFunction = rendFunc;
	i.m_renderInfo = smi;
	i.m_sortKey = sortKey;
	m_queueItems.push_back(i);
}

void CommandBuffer::sort() {

}

void CommandBuffer::flush() {
    m_queueItems.clear();
}

void CommandBuffer::beginRenderPass(RenderPass* rp) {
	rp->bind();
}

void CommandBuffer::endRenderPass() {
	//TODO: Reset the render pass settings to default.
}

void CommandBuffer::execute(){
	m_device->clear();
    for (auto i : m_queueItems) {
        i.m_rendererFunction(this, &i, 1); //call the render function, all states are set in the func
    }
}
