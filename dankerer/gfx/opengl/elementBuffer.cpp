//
// Created by dan on 25/10/18.
//

#include "elementBuffer.h"


using dk::gfx::ElementBuffer;

ElementBuffer::ElementBuffer() {
    glCreateBuffers(1, &m_ebo);
}

ElementBuffer::~ElementBuffer() {
    glDeleteBuffers(1, &m_ebo);
}

void ElementBuffer::bind(u32 *elements, unsigned long count) {
    glNamedBufferData(m_ebo, count, elements, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}

void ElementBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}
