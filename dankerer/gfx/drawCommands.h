//
// Created by dan on 10/11/18.
//

#ifndef DANKERER_DRAWCOMMANDS_H
#define DANKERER_DRAWCOMMANDS_H

#include "common.h"

namespace dk {
    namespace gfx {
        class VertexBuffer;
        class ElementBuffer;

        struct Draw {
            u32 m_vertexCount;
            u32 m_startVertex;

            VertexBufferHandle m_vertexBuffer;
            ElementBufferHandle m_eleBuffer;
        };

        struct DrawIndexed {
            u32 m_indexCount;
            u32 m_startIndex;
            u32 m_baseVertex;

            VertexBufferHandle m_vertexBuffer;
            ElementBufferHandle m_eleBuffer;
        };

        static u64 generateMaterialKey(MaterialHandle h) {
            return static_cast<u64>(h.m_index); //this could be more complex in the future...
        }
    }
}

#endif //DANKERER_DRAWCOMMANDS_H
