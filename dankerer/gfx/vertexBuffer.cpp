//
// Created by dan on 25/10/18.
//

#include "vertexBuffer.h"
#include "dankerer/base/tiny_obj_loader.h"
#include "dankerer/gfx/vertexBuffer.h"


using dk::gfx::VertexBuffer;

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &m_id);
}

VertexBuffer::VertexBuffer(std::string const &fileName) {
    glGenBuffers(1, &m_id);
    m_fileName = fileName;

}

VertexBuffer::~VertexBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind buffer first?
    glDeleteBuffers(1, &m_id);

}

void VertexBuffer::bind(std::string const &fileName) {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);

}

void VertexBuffer::bind(float *vertices, u32 count) {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, count, vertices, GL_STATIC_DRAW);

}


