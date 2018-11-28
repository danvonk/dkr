//
// Created by dan on 25/10/18.
//

#include "vertexArrayConfig.h"

using namespace dk::gfx;

VertexArrayConfig::VertexArrayConfig() {
    //bind the default vao
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    m_vaoMap[VertexAttributeLayout::Default] = vao;
}

VertexArrayConfig::~VertexArrayConfig() {
    for (auto& vao : m_vaoMap) {
        glDeleteVertexArrays(1, &vao.second);
    }
}

bool VertexArrayConfig::addLayout(VertexAttributeLayout l) {
    if (m_vaoMap.contains(l)) {
        glBindVertexArray(m_vaoMap[l]);
        return false;
    } else {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        m_vaoMap[l] = vao;
        return true;
    }
}

bool VertexArrayConfig::bindLayout(VertexAttributeLayout l) {
    if (m_vaoMap.contains(l)) {
        glBindVertexArray(m_vaoMap[l]);
        return true;
    } else {
        addLayout(l);
        return false;
    }
}

void VertexArrayConfig::deleteLayout(VertexAttributeLayout l) {
    if (m_vaoMap.contains(l)) {
        glDeleteVertexArrays(1, &m_vaoMap[l]);
        m_vaoMap.erase(l);
    }
}
