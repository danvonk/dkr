//
// Created by dan on 31/10/18.
//

#include "commandBuffer.h"

using namespace dk::gfx;


void CommandBuffer::sort() {

}

void CommandBuffer::addDrawCommand(u64 materialKey, DrawIndexed di) {
    m_commands.emplace_back(std::pair<u64, DrawIndexed>{materialKey, di});
}

void CommandBuffer::clear() {
    m_commands.clear();
}
