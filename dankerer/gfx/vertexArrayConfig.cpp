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

	//auto pos = glGetAttribLocation(m_shp, "position");
	glEnableVertexAttribArray(0);
	//std::cout << "Val is " << pos << "\n";
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
	//auto norm = glGetAttribLocation(m_shp, "normal");
	//std::cout << "Val is " << norm << "\n";
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	//auto texc = glGetAttribLocation(m_shp, "texCoord");
	//std::cout << "Val is " << texc << "\n";
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));
}

VertexArrayConfig::~VertexArrayConfig() {
    for (auto& vao : m_vaoMap) {
        glDeleteVertexArrays(1, &vao.second);
    }
}

bool VertexArrayConfig::addLayout(VertexAttributeLayout l) {
	auto it = m_vaoMap.find(l);
    if (it != m_vaoMap.end()) {
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
	auto it = m_vaoMap.find(l);
    if (it != m_vaoMap.end()) {
        glBindVertexArray(m_vaoMap[l]);
        return true;
    } else {
        addLayout(l);
        return false;
    }
}

void VertexArrayConfig::deleteLayout(VertexAttributeLayout l) {
	auto it = m_vaoMap.find(l);
    if (it != m_vaoMap.end()) {
        glDeleteVertexArrays(1, &m_vaoMap[l]);
        m_vaoMap.erase(l);
    }
}
