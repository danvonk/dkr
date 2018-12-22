//
// Created by dan on 21/12/18.
//

#include "renderQueue.h"

using namespace dk::gfx;

RenderQueue::RenderQueue(Device *d)
    : m_device(d)
{

}

void RenderQueue::draw(u32 startVertex, u32 count) {
    glDrawArrays(GL_TRIANGLES, startVertex, count);
}

void RenderQueue::drawElements(u32 vertexCount, u32 indexOffset) {
    glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, (void*)indexOffset);
}