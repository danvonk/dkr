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
            ~VertexBuffer();

            void bind(float* vertices, unsigned long count);
			void bind();

        private:
            GLuint m_id;
        };
    }
}


#endif //DANKERER_VERTEXBUFFER_H
