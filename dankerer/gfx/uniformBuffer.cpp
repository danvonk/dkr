//
// Created by dan on 26/10/18.
//

#include "uniformBuffer.h"
#include "dankerer/gfx/uniformBuffer.h"


using dk::gfx::UniformBuffer;

UniformBuffer::UniformBuffer() {
    glGenBuffers(1, &m_ubo);

}

UniformBuffer::~UniformBuffer() {
    glDeleteBuffers(1, &m_ubo);

}
