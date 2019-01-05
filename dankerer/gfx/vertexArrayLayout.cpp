//
// Created by dan on 25/10/18.
//

#include "vertexArrayLayout.h"
#include <boost/container_hash/hash.hpp>

using namespace dk::gfx;

VertexArrayLayout::VertexArrayLayout(Device *d)
: m_device(d)
, m_previouslyBound(false)
{
    glGenVertexArrays(1, &m_vao);
}

VertexArrayLayout::~VertexArrayLayout() {
    glDeleteVertexArrays(1, &m_vao);

}

void VertexArrayLayout::addAttribute(int index, int numComponents, GLenum type) {
    VertexArrayLayoutEntry entry{};

    entry.m_layoutLocation = index;
    entry.m_numComponents = numComponents;
    entry.m_type = type;

    if (m_entries.empty()) {
        entry.m_offset = 0;
    } else {
        entry.m_offset = m_entries.back().m_offset += (numComponents * sizeof(type));
    }
    m_entries.push_back(entry);
}


void VertexArrayLayout::bindAttribute() {
    glBindVertexArray(m_vao);
    if (!m_previouslyBound) {
        size_t sizeOfEntry = 0;
        for (auto entry : m_entries) {
            sizeOfEntry += entry.m_numComponents * sizeof(entry.m_type);
        }
        for (auto entry : m_entries) {
            entry.m_stride = sizeOfEntry;
            glEnableVertexAttribArray(entry.m_layoutLocation);
            glVertexAttribPointer(entry.m_layoutLocation, entry.m_numComponents, entry.m_type, GL_FALSE,
                                  sizeOfEntry, (void *) entry.m_offset);
        }
    }

}


