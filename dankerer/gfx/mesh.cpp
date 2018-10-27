//
// Created by dan on 27/10/18.
//

#include "mesh.h"
#include "dankerer/gfx/mesh.h"
#include <unordered_map>
#define TINYOBJLOADER_IMPLEMENTATION
#include "dankerer/base/tiny_obj_loader.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.position) ^
                     (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^
                   (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}

using dk::gfx::Mesh;
using dk::gfx::VertexBuffer;

Mesh::Mesh() {
    m_vbo = std::make_unique<VertexBuffer>();
}

void Mesh::loadOBJ(std::string const &fileName) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string errors;
    std::string warnings;

    bool loaded = tinyobj::LoadObj(&attrib, &shapes, &materials, &warnings, &errors, fileName.c_str());

    if (!errors.empty()) {
        std::cerr << "Err: " << errors << '\n';
    }

    std::cout << "Info: Vertices: " << (int) (attrib.vertices.size()) / 3 << '\n';
    std::cout << "Info: Normals: " << (int) (attrib.normals.size()) / 3 << '\n';
    std::cout << "Info: Texcoords: " << (int) (attrib.texcoords.size()) / 3 << '\n';
    std::cout << "Info: Materials: " << materials.size() << '\n';
    std::cout << "Info: Shapes: " << shapes.size() << '\n';

    std::unordered_map<Vertex, u32> uniqueVertices;
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex v;

            v.position = glm::vec3 {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            v.normal = glm::vec3 {
                attrib.normals[3 * index.normal_index + 0],
                attrib.normals[3 * index.normal_index + 1],
                attrib.normals[3 * index.normal_index + 2]
            };

            v.texCoord = glm::vec2 {
                attrib.texcoords[2 * index.texcoord_index + 0],
                attrib.texcoords[2 * index.texcoord_index + 1]
            };

            if (uniqueVertices.count(v) == 0) {
                uniqueVertices[v] = static_cast<u32>(m_vertices.size());
                m_vertices.push_back(v);
            }
            m_indices.push_back(uniqueVertices[v]);
        }
    }
    m_vbo->bind(reinterpret_cast<float *>(&m_vertices[0]), m_vertices.size() * sizeof(GLfloat));
    m_ebo->bind(reinterpret_cast<int *>(&m_indices[0]), m_indices.size() * sizeof(int));
}
void Mesh::use() {
}


