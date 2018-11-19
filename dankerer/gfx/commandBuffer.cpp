//
// Created by dan on 31/10/18.
//

#include "commandBuffer.h"
#include "dankerer/gfx/commandBuffer.h"

using namespace dk::gfx;


void CommandBuffer::sort() {

}

void CommandBuffer::addDrawCommand(u64 materialKey, Draw d) {
    m_commands.emplace_back(std::pair<u64, Draw>{materialKey, d});

}

void CommandBuffer::addDrawCommand(u64 materialKey, DrawIndexed di) {
    m_commands.emplace_back(std::pair<u64, DrawIndexed>{materialKey, di});
}
