//
// Created by dan on 27/10/18.
//

#ifndef DANKERER_MESH_H
#define DANKERER_MESH_H

#include "common.h"
#include "aabb.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>

#include "device.h"
#include "vertexBuffer.h"
#include "elementBuffer.h"
#include "shaderProgram.h"




namespace dk {
    namespace gfx {
		class CommandBuffer;
		struct RenderQueueItem;

        //mesh fills out this struct and is passed along with the
        //RendererFunc to the CommandBuffer
        struct StaticMeshInfo {
            VertexBuffer* m_vbo;
            ElementBuffer* m_ebo;
            ShaderProgram* m_shp;
            GLuint m_vao;

            u32 m_elementCount;
            u32 m_vertexCount;

            u32 m_startElement;
            u32 m_startVertex;
        };


        struct MeshComponent {
            VertexBufferHandle m_vbo;
            ElementBufferHandle m_ebo;

            u32 m_startVertex = 0;
            u32 m_vertexCount = 0;

            u32 m_startElement = 0;
            u32 m_elementCount = 0;

            std::vector<u32> m_indices;
            MaterialHandle m_material;
			
            AABB m_boundingBox;
        };

		void setMeshState(CommandBuffer* q, const RenderQueueItem* d);
		void renderStaticMesh(CommandBuffer* q, const RenderQueueItem* d, u32 instances);

        class StaticMesh {
        public:
            StaticMesh();
            ~StaticMesh();

            void loadFromFile(std::string const &fileName, Device& rend);

            u64 getVertCount();

            MaterialHandle loadMaterial(aiMaterial* mat, Device& rend);

			void addToBuffer(CommandBuffer* q, Device* d);
            
			/*void evaluateStack(std::unique_ptr<Material> mat, aiScene* pScene);
            void addToQueue(CommandBuffer& q) const;*/

        private:
            std::vector<MeshComponent> m_subMeshes;
            //considering this mesh is static, one vbo/ebo per mesh
            //is probably enough...
            GLuint m_vao; //TODO: wasteful and not portable
            VertexBufferHandle m_vbo;
            ElementBufferHandle m_ebo;

            std::vector<Vertex> m_vertices;
            std::vector<u32> m_indices;
            u64 m_vertCount;

            //temporary shaders for phong lighting
            ShaderHandle m_vert;
            ShaderHandle m_frag;
        };
    }
}


#endif //DANKERER_MESH_H
