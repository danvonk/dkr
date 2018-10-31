//
// Created by dan on 25/10/18.
//

#include "elementBuffer.h"


using dk::gfx::ElementBuffer;

ElementBuffer::ElementBuffer() {
    glGenBuffers(1, &m_ebo);
}

ElementBuffer::~ElementBuffer() {
    glDeleteBuffers(1, &m_ebo);
}

void ElementBuffer::bind(int *elements, unsigned long count) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, elements, GL_STATIC_DRAW);
}
