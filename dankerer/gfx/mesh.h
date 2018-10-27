//
// Created by dan on 27/10/18.
//

#ifndef DANKERER_MESH_H
#define DANKERER_MESH_H

#include "common.h"
#include "vertexBuffer.h"
#include "elementBuffer.h"

namespace dk {
    namespace gfx {
        class Mesh {
        public:
            Mesh();
            ~Mesh() = default;

            void loadOBJ(std::string const& fileName);
            void use();
        private:
            std::unique_ptr<VertexBuffer> m_vbo;
            std::unique_ptr<ElementBuffer> m_ebo;

            std::vector<Vertex> m_vertices;
            std::vector<u32> m_indices;
            int m_vertCount;


        };
    }
}


#endif //DANKERER_MESH_H
