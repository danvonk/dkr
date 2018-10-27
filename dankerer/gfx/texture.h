//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_TEXTURE_H
#define DANKERER_TEXTURE_H

#include "common.h"

namespace dk {
    namespace gfx {
        class Texture {
        public:
            Texture();
            ~Texture();

            void loadImage(std::string const& fileName);

        private:
            GLuint m_tex;
        };
    }
}


#endif //DANKERER_TEXTURE_H
