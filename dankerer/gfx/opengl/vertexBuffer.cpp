//
// Created by dan on 25/10/18.
//

#include "vertexBuffer.h"


using dk::gfx::VertexBuffer;

VertexBuffer::VertexBuffer() {
    glCreateBuffers(1, &m_id);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_id);

}

void VertexBuffer::bind(float *vertices, unsigned long count) {
    glNamedBufferData(m_id, count, vertices, GL_STATIC_DRAW); //separate this!
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}


