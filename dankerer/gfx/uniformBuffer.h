//
// Created by dan on 26/10/18.
//

#ifndef DANKERER_UNIFORMBUFFER_H
#define DANKERER_UNIFORMBUFFER_H

#include "common.h"

namespace dk {
    namespace gfx {
        class UniformBuffer {
        public:
            UniformBuffer();
            ~UniformBuffer();

        private:
            GLuint m_ubo;
        };
    }
}


#endif //DANKERER_UNIFORMBUFFER_H
