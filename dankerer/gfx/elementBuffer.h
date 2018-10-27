//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_ELEMENTBUFFER_H
#define DANKERER_ELEMENTBUFFER_H

#include "common.h"

namespace dk {
    namespace gfx {
        class ElementBuffer {
        public:
            ElementBuffer();
            ~ElementBuffer();

            void bind(int* elements, unsigned long count);
        private:
            GLuint m_ebo;
        };
    }
}


#endif //DANKERER_ELEMENTBUFFER_H
