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

void UniformBuffer::bind(void *data, u32 count) {
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, count, data, GL_STATIC_DRAW);
}

void UniformBuffer::connectToShader(GLuint bindingPoint) {
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, m_ubo);
}
