//
// Created by dan on 27/10/18.
//
#include <boost/filesystem.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "staticMesh.h"

#include "device.h"
#include "commandBuffer.h"
#include "material.h"


using namespace dk::gfx;

namespace renderFunctions {
    void setMeshState(CommandBuffer* q, const RenderQueueItem* d) {
        const StaticMeshInfo* info = static_cast<StaticMeshInfo*>(d->m_renderInfo);

        q->setShaderProgram(info->m_shp);

        glBindVertexArray(info->m_vao);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

        if (info->m_ebo) {
            q->setElementBuffer(info->m_ebo);
        }
		info->m_vbo->bind();
    }

    void renderStaticMesh(CommandBuffer *q, const RenderQueueItem *d, u32 instances) {
        const StaticMeshInfo *info = static_cast<StaticMeshInfo *>(d->m_renderInfo);
        setMeshState(q, d);

        q->setShaderProgram(info->m_shp);

        if (info->m_ebo) {
            q->drawElements(info->m_vertexCount, info->m_startElement);
        } else {
            q->draw(info->m_startVertex, info->m_vertexCount);
        }
    }
}

StaticMesh::StaticMesh() {
    glGenVertexArrays(1, &m_vao);
}

StaticMesh::~StaticMesh() {
    glDeleteVertexArrays(1, &m_vao);
}

void StaticMesh::loadFromFile(std::string const &fileName, Device& rend) {
    //ask renderer to create necessary gfx objects
    m_vbo = rend.createVertexBuffer();
    m_ebo = rend.createElementBuffer();

    m_vert = rend.createShader(GL_VERTEX_SHADER, "/home/dan/dev/dankerer/dankerer/resources/sh1.vert");
    m_frag = rend.createShader(GL_FRAGMENT_SHADER, "/home/dan/dev/dankerer/dankerer/resources/sh1.frag");

    Assimp::Importer importer;
    const aiScene *pScene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs);
    if (!pScene) {
		boost::filesystem::path full_path(boost::filesystem::current_path());
		std::cerr << "Error: Could not load model at " << fileName << '\n';
		std::cerr << "Error: Current path is " << full_path << '\n';
        return;
    }
    std::cout << "Info: Model has " << pScene->mNumMeshes << " meshes and " << pScene->mNumMaterials << " materials\n";

    auto verticesProcessed = 0u;
    auto indicesProcessed = 0u;

    std::unordered_map<int, MaterialHandle> m_cachedMaterials;

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
                std::cout << "weird number of indices to a face: " << mesh->mFaces->mNumIndices << std::endl;
            }
        }

        verticesProcessed += meshComponent.m_vertexCount;

        meshComponent.m_vertexCount = mesh->mNumVertices;
        meshComponent.m_elementCount = meshComponent.m_indices.size();

        m_indices.insert(m_indices.end(), std::make_move_iterator(meshComponent.m_indices.begin()), std::make_move_iterator(meshComponent.m_indices.end()));

        //TODO: Add an option to not automatically load a models .MTL/.FBX/... file
		auto it = m_cachedMaterials.find(mesh->mMaterialIndex);
        if (it != m_cachedMaterials.end()) {
            //material has already been loaded
            meshComponent.m_material = m_cachedMaterials[mesh->mMaterialIndex];
        } else {
            //load the material into the engine
            MaterialHandle h = loadMaterial(pScene->mMaterials[mesh->mMaterialIndex], rend);
            m_cachedMaterials[mesh->mMaterialIndex] = h;
            meshComponent.m_material = h;

            auto& mat = rend.accessMaterial(h);
            mat.addShader(m_vert);
            mat.addShader(m_frag);
        }

        m_subMeshes.push_back(meshComponent);
    }

    m_vertCount = m_vertices.size();

    rend.accessElementBuffer(m_ebo).bind(reinterpret_cast<u32*>(&m_indices[0]), m_indices.size() * sizeof(unsigned int));
    rend.accessVertexBuffer(m_vbo).bind(reinterpret_cast<float *>(&m_vertices[0]), m_vertices.size() * sizeof(GLfloat) * 8);
}

u64 StaticMesh::getVertCount() {
    return m_vertCount;
}

MaterialHandle StaticMesh::loadMaterial(aiMaterial *mat, Device& rend) {
    auto matHandle = rend.createMaterial();
    auto& gameMat = rend.accessMaterial(matHandle);

    aiString m_name;
    if (mat->Get(AI_MATKEY_NAME, m_name) == AI_SUCCESS) {
        gameMat.setName(m_name.C_Str());
    }

    std::cout << "Info: Loaded new material named: " << gameMat.getName() << '\n';

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

void StaticMesh::addToBuffer(CommandBuffer & q, Device& d) {
	for (const auto& subMesh : m_subMeshes) {
		StaticMeshInfo meshInfo{};
		meshInfo.m_startVertex = subMesh.m_startVertex;
		meshInfo.m_ebo = &(d.accessElementBuffer(subMesh.m_ebo));
		meshInfo.m_elementCount = subMesh.m_elementCount;
		meshInfo.m_shp = d.accessMaterial(subMesh.m_material).getShaderProgram();
		meshInfo.m_startElement = subMesh.m_startElement;
		meshInfo.m_vao = m_vao;
		meshInfo.m_vbo = &(d.accessVertexBuffer(m_vbo));
		meshInfo.m_vertexCount = subMesh.m_vertexCount;


		q.push(0, renderFunctions::renderStaticMesh, meshInfo);
	}
}
