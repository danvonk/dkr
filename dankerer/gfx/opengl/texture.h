//
// Created by dan on 25/10/18.
//

#ifndef DANKERER_TEXTURE_H
#define DANKERER_TEXTURE_H

#include "common.h"

namespace dk {
    namespace gfx {
        enum class TextureType {
            Ambient,
            Diffuse,
            Specular
        };

        class Texture {
        public:
            Texture();
            ~Texture();

            void loadImage(std::string const& fileName);
            void loadImageWithType(std::string const& fileName, TextureType tt);

            void bind(u32 samplerUnit = 0);
        private:
            GLuint m_tex;
            TextureType m_ttype;
        };
    }
}


#endif //DANKERER_TEXTURE_H
