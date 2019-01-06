//
// Created by dan on 21/12/18.
//

#include "commandBuffer.h"
#include "opengl/elementBuffer.h"

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

void dk::gfx::CommandBuffer::push(u64 sortKey, RendererFunc rendFunc, StaticMeshInfo smi)
{
}

void CommandBuffer::sort() {

}

void CommandBuffer::reset() {
    m_queueItems.clear();
}

void CommandBuffer::beginRenderPass(RenderPass* rp) {
	rp->bind();
}

void CommandBuffer::execute(){
    for (auto i : m_queueItems) {
        i.m_rendererFunction(this, &i, 1); //call the render function, all states are set in the func
    }
}

template<typename T>
void CommandBuffer::push() {

}
