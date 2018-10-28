//
// Created by dan on 27/10/18.
//

#include "mesh.h"
#include "dankerer/gfx/mesh.h"
#include <unordered_map>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>

using dk::gfx::Mesh;
using dk::gfx::VertexBuffer;

Mesh::Mesh() {
    m_vbo = std::make_unique<VertexBuffer>();
    m_ebo = std::make_unique<ElementBuffer>();
}

void Mesh::loadOBJ(std::string const &fileName) {
    Assimp::Importer importer;
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    const aiScene* pScene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenNormals);
    if (!pScene) {
        std::cerr << "Err: Could not load model.\n";
    }

    for (auto i = 0; i < pScene->mNumMeshes; i++) {
        const aiMesh* mesh = pScene->mMeshes[i];

        for (auto j = 0; j < mesh->mNumVertices; j++) {
            Vertex v;
            v.position.x = mesh->mVertices[j].x;
            v.position.y = mesh->mVertices[j].y;
            v.position.z = mesh->mVertices[j].z;

            v.normal.x = mesh->mNormals[j].x;
            v.normal.y = mesh->mNormals[j].y;
            v.normal.z = mesh->mNormals[j].z;

            v.texCoord.x = 0;
            v.texCoord.y = 0;

            m_vertices.push_back(v);
        }

        for (auto j = 0; j < mesh->mNumFaces; j++) {
            const aiFace face = mesh->mFaces[j];
            for (auto k = 0; k < face.mNumIndices; k++) {
                m_indices.push_back(face.mIndices[k]);
            }
        }
    }
    std::cout << "Info: Loaded Model with " << pScene->mMeshes[0]->mNumVertices << " verts.\n";
    m_vertCount = m_vertices.size();
    m_vbo->bind(reinterpret_cast<float *>(&m_vertices[0]), m_vertices.size() * sizeof(GLfloat));
    m_ebo->bind(reinterpret_cast<int *>(&m_indices[0]), m_indices.size() * sizeof(int));
}

void Mesh::use() {
}

u64 Mesh::getVertCount() {
    return m_vertCount;
}


