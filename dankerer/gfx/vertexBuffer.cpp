//
// Created by dan on 25/10/18.
//

#include "vertexBuffer.h"
#include "dankerer/base/tiny_obj_loader.h"


using dk::gfx::VertexBuffer;

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &m_id);
}

VertexBuffer::~VertexBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind buffer first?
    glDeleteBuffers(1, &m_id);

}

void VertexBuffer::bind(float *vertices, unsigned long count) {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, count, vertices, GL_STATIC_DRAW);
}


