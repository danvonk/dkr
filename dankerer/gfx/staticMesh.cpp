//
// Created by dan on 27/10/18.
//
#include <unordered_map>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "staticMesh.h"
#include "renderer.h"
#include "commandBuffer.h"


using namespace dk::gfx;

StaticMesh::StaticMesh() {
}

void StaticMesh::loadFromFile(std::string const &fileName, Renderer& rend) {
    //ask renderer to create necessary gfx objects
    m_vbo = rend.createVertexBuffer();
    m_ebo = rend.createElementBuffer();

    Assimp::Importer importer;
    const aiScene *pScene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs);
    if (!pScene) {
        std::cerr << "Error: Could not load model.\n";
        return;
    }
    std::cout << "Info: Model has " << pScene->mNumMeshes << " meshes and " << pScene->mNumMaterials << " materials\n";

    auto verticesProcessed = 0u;
    auto indicesProcessed = 0u;

    for (auto i = 0u; i < pScene->mNumMeshes; i++) {
        const aiMesh *mesh = pScene->mMeshes[i];

        MeshComponent meshComponent;
        meshComponent.m_vbo = m_vbo;
        meshComponent.m_ebo = m_ebo;
        meshComponent.m_startElement = indicesProcessed;
        meshComponent.m_startVertex = verticesProcessed;

        for (auto j = 0u; j < mesh->mNumVertices; j++) {
            Vertex v;
            v.position.x = mesh->mVertices[j].x;
            v.position.y = mesh->mVertices[j].y;
            v.position.z = mesh->mVertices[j].z;

            v.normal.x = mesh->mNormals[j].x;
            v.normal.y = mesh->mNormals[j].y;
            v.normal.z = mesh->mNormals[j].z;

            if (mesh->HasTextureCoords(0)) {
                v.texCoord.x = mesh->mTextureCoords[0][j].x;
                v.texCoord.y = mesh->mTextureCoords[0][j].y;
            } else {
                v.texCoord.x = 0.0f;
                v.texCoord.y = 0.0f;
            }

            m_vertices.push_back(v);
        }

        for (size_t k = 0; k < mesh->mNumFaces; ++k) {
            if (mesh->mFaces->mNumIndices == 3) {
                // kth face!
                meshComponent.m_indices.push_back(mesh->mFaces[k].mIndices[0]);
                meshComponent.m_indices.push_back(mesh->mFaces[k].mIndices[1]);
                meshComponent.m_indices.push_back(mesh->mFaces[k].mIndices[2]);
                indicesProcessed += 3;
            } else {
                std::cout << "wierd number of indices to a face: " << mesh->mFaces->mNumIndices << std::endl;
            }
        }

        verticesProcessed += meshComponent.m_vertexCount;

        meshComponent.m_vertexCount = mesh->mNumVertices;
        meshComponent.m_elementCount = meshComponent.m_indices.size();

        m_indices.insert(m_indices.end(), std::make_move_iterator(meshComponent.m_indices.begin()), std::make_move_iterator(meshComponent.m_indices.end()));

        meshComponent.m_material = loadMaterial(pScene->mMaterials[mesh->mMaterialIndex], rend);
        m_subMeshes.push_back(meshComponent);
    }

    m_vertCount = m_vertices.size();

    rend.accessElementBuffer(m_ebo).bind(reinterpret_cast<u32*>(&m_indices[0]), m_indices.size() * sizeof(unsigned int));
    rend.accessVertexBuffer(m_vbo).bind(reinterpret_cast<float *>(&m_vertices[0]), m_vertices.size() * sizeof(GLfloat) * 8);
}

void StaticMesh::use() {
}

u64 StaticMesh::getVertCount() {
    return m_vertCount;
}

MaterialHandle StaticMesh::loadMaterial(aiMaterial *mat, Renderer& rend) {
    auto matHandle = rend.createMaterial();
    auto gameMat = rend.accessMaterial(matHandle);

    aiString m_name;
    if (mat->Get(AI_MATKEY_NAME, m_name) == AI_SUCCESS) {
        gameMat.setName(m_name.C_Str());
    }

    float specularExp;
    if (mat->Get(AI_MATKEY_SHININESS, specularExp) == AI_SUCCESS) {
        gameMat.setSpecularExponent(specularExp);
    }

    float refractiveIdx;
    if (mat->Get(AI_MATKEY_REFRACTI, refractiveIdx) == AI_SUCCESS) {
        gameMat.setRefractiveIndex(refractiveIdx);
    }

    float opacity;
    if (mat->Get(AI_MATKEY_OPACITY, opacity) == AI_SUCCESS) {
        gameMat.setOpacity(opacity);
    }

    aiVector3D transFilter;
    if (mat->Get(AI_MATKEY_COLOR_TRANSPARENT, transFilter) == AI_SUCCESS) {
        gameMat.setTransmissionFilter(glm::vec3(transFilter.x, transFilter.y, transFilter.z));
    }

    aiVector3D ambientColour;
    if (mat->Get(AI_MATKEY_COLOR_AMBIENT, ambientColour) == AI_SUCCESS) {
        gameMat.setAmbientColour(glm::vec3(ambientColour.x, ambientColour.y, ambientColour.z));
    }

    aiVector3D diffuseColour;
    if (mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColour) == AI_SUCCESS) {
        gameMat.setDiffuseColour(glm::vec3(diffuseColour.x, diffuseColour.y, diffuseColour.z));
    }

    aiVector3D specularColour;
    if (mat->Get(AI_MATKEY_COLOR_SPECULAR, specularColour) == AI_SUCCESS) {
        gameMat.setDiffuseColour(glm::vec3(specularColour.x, specularColour.y, specularColour.z));
    }

    for (auto i = 0u; i < mat->GetTextureCount(aiTextureType_AMBIENT); i++) {
        aiString path;
        if (mat->GetTexture(aiTextureType_AMBIENT, i, &path) == AI_SUCCESS) {
            gameMat.addTexture(path.C_Str(), TextureType::Ambient, &rend);
        }
    }

    for (auto i = 0u; i < mat->GetTextureCount(aiTextureType_DIFFUSE); i++) {
        aiString path;
        if (mat->GetTexture(aiTextureType_DIFFUSE, i, &path) == AI_SUCCESS) {
            gameMat.addTexture(path.C_Str(), TextureType::Diffuse, &rend);
        }
    }

    for (auto i = 0u; i < mat->GetTextureCount(aiTextureType_SPECULAR); i++) {
        aiString path;
        if (mat->GetTexture(aiTextureType_SPECULAR, i, &path) == AI_SUCCESS) {
            gameMat.addTexture(path.C_Str(), TextureType::Specular, &rend);
        }
    }

    return matHandle;
}


void StaticMesh::evaluateStack(std::unique_ptr<Material> mat, aiScene *pScene) {
//    auto stackItem = pScene->mTextures[0];
//
//    aiVector3D base = pScene->
//    for (auto i = 0; i < pScene->mNumTextures; i++) {
//
//    }
}

void StaticMesh::render(CommandBuffer *buffer) {
    for (const auto& mesh : m_subMeshes) {
        DrawIndexed draw;
        draw.m_eleBuffer = mesh.m_ebo;
        draw.m_vertexBuffer = mesh.m_vbo;
        draw.m_baseVertex = mesh.m_startVertex;
        draw.m_startIndex = mesh.m_startVertex;
        draw.m_indexCount = mesh.m_elementCount;

        buffer->addDrawCommand(generateMaterialKey(mesh.m_material), draw);
    }
}
