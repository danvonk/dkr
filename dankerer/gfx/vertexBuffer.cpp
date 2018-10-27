//
// Created by dan on 25/10/18.
//

#include "vertexBuffer.h"
#include "dankerer/base/tiny_obj_loader.h"


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

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::map<std::string, GLuint> textures;
    std::string warnings;
    std::string errors;

    bool loaded = tinyobj::LoadObj(&attrib, &shapes, &materials, &warnings, &errors, fileName.c_str());

    if (!warnings.empty()) {
        std::cerr << "Warn: " << warnings << '\n';
    }

    if (!errors.empty()) {
        std::cerr << "Err: " << errors << '\n';
    }

    std::cout << "Info: Vertices: " << (int)(attrib.vertices.size()) / 3 << '\n';
    std::cout << "Info: Normals: " << (int)(attrib.normals.size()) / 3 << '\n';
    std::cout << "Info: Texcoords: " << (int)(attrib.texcoords.size()) / 3 << '\n';
    std::cout << "Info: Materials: " << materials.size() << '\n';
    std::cout << "Info: Shapes: " << shapes.size() << '\n';
}

void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);

}

void VertexBuffer::bind(float *vertices, u32 count) {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, count, vertices, GL_STATIC_DRAW);

}


