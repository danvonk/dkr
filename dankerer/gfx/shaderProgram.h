//
// Created by dan on 26/10/18.
//

#ifndef DANKERER_SHADERPROGRAM_H
#define DANKERER_SHADERPROGRAM_H

#include "common.h"

namespace dk {
    namespace gfx {
        class Shader;
        class ShaderProgram {
        public:
            ShaderProgram();
            ~ShaderProgram();

            void addShader(Shader* shader);
            bool link();

        private:
            GLuint m_shp;

        };
    }
}


#endif //DANKERER_SHADERPROGRAM_H
