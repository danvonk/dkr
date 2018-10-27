//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_VERTEXBUFFER_H
#define DANKERER_VERTEXBUFFER_H

#include "common.h"

namespace dk {
    namespace gfx {
        class VertexBuffer {
        public:
            VertexBuffer();
            explicit VertexBuffer(std::string const& fileName);
            ~VertexBuffer();

            void bind(std::string const& fileName);
            void bind(float* vertices, u32 count);
            void bind();

        private:
            GLuint m_id;
            std::string m_fileName;
        };
    }
}


#endif //DANKERER_VERTEXBUFFER_H
