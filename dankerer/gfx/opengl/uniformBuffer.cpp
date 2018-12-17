//
// Created by dan on 26/10/18.
//

#include "uniformBuffer.h"


using dk::gfx::UniformBuffer;

UniformBuffer::UniformBuffer() {
    glCreateBuffers(1, &m_ubo);
}

UniformBuffer::~UniformBuffer() {
    glDeleteBuffers(1, &m_ubo);
}

void UniformBuffer::bind(void *data, u32 count) {
    glNamedBufferData(m_ubo, count, data, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
}

void UniformBuffer::connectToShader(GLuint bindingPoint) {
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, m_ubo);
}
